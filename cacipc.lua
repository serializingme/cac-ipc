--
-- Wireshark dissector for the CAC IPC protocol
-- Copyright (C) 2022 Duarte Silva <duarte.silva@serializing.me>
--
-- This work is licensed under the terms of GPLv3 (or any later version).
--

-- Protocol header size. The size of the header is a fixed 26 bytes, a pretty safe assumption as it is hardcoded all
-- over CAC's code.
local CACIPC_HDR_LEN = 26

-- The port number associated with CAC IPC protocol.
local CACIPC_PROTO_PORT = 65332

-- Error constants used when parsing IPC messages and respective TLVs (or TVs).
local CACIPC_ERR = {
  NONE = 0x00,
  INSUFICIENT_DATA = 0x01,
  INVALID_ID_TAG = 0x02,
  HEADER_LEN = 0x04,
  DATA_LEN = 0x08
}

-- Functions to create the various protocol fields that are used in the TLVs (or TVs).
local function field_bool(abbr, name)
  return ProtoField.new(name, abbr, ftypes.BOOLEAN, nill, base.NONE)
end
local function field_int32(abbr, name)
  return ProtoField.new(name, abbr, ftypes.INT32, nill, base.DEC)
end
local function field_int64(abbr, name)
  return ProtoField.new(name, abbr, ftypes.INT64, nill, base.DEC)
end
local function field_uint8(abbr, name)
  return ProtoField.new(name, abbr, ftypes.UINT8, nill, base.HEX)
end
local function field_uint16(abbr, name)
  return ProtoField.new(name, abbr, ftypes.UINT16, nill, base.HEX)
end
local function field_uint32(abbr, name)
  return ProtoField.new(name, abbr, ftypes.UINT32, nill, base.HEX)
end
local function field_uint64(abbr, name)
  return ProtoField.new(name, abbr, ftypes.UINT64, nill, base.HEX)
end
local function field_bytes(abbr, name)
  return ProtoField.new(name, abbr, ftypes.BYTES, nil, base.SPACE)
end
local function field_string(abbr, name)
  return ProtoField.new(name, abbr, ftypes.STRING, nill, base.STRING)
end

-- Create the various fields that are common to all the various IPC messages or that don't have a specific IPC message
-- associated with.
-- Message header fields.
local field_id_tag = field_uint32("cacipc.id_tag", "Identifier Tag")
local field_header_length = field_uint16("cacipc.header_length", "Header Length")
local field_data_length = field_uint16("cacipc.data_length", "Data Length")
local field_ipc_response_cb = field_uint32("cacipc.ipc_response_cb", "IPC Response CB")
local field_msg_user_context = field_uint32("cacipc.msg_user_context", "User Context")
local field_req_msg_id = field_uint32("cacipc.request_msg_id", "Request Identifier")
local field_ret_ipc_index = field_uint32("cacipc.return_ipc_index", "Return IPC Index")
local field_message_type = field_uint8("cacipc.message_type", "Message Type")
local field_message_id = field_uint8("cacipc.message_id", "Message Identifer")
local field_message_class = field_string("cacipc.message_class", "Message Class")

-- Fields for TLV (or TV) entries.
local field_type = field_uint16("cacipc.tlv_type", "Type")
local field_length = field_uint16("cacipc.tlv_length", "Length")
local field_value = field_bytes("cacipc.tlv_value", "Value")

-- Fields for a specific type of non-TLV data that holds statistics.
local field_stat_entry = field_bytes("cacipc.statistic.entry", "Statistic Entry")
local field_stat_type = field_uint32("cacipc.statistic.type", "Type")
local field_stat_unknown = field_bytes("cacipc.statistic.unknown", "Unknown")
local field_stat_value = field_uint64("cacipc.statistic.value", "Value")

-- Create the expert fields used to report errors or warnings.
-- Errors.
local ef_invalid_hdr_len = ProtoExpert.new("cacipc.invalid_hdr_len.expert", "IPC header length is invalid",
  expert.group.MALFORMED, expert.severity.ERROR)

local ef_invalid_data_len = ProtoExpert.new("cacipc.ef_invalid_data_len.expert", "IPC data length is invalid",
  expert.group.MALFORMED, expert.severity.ERROR)

local ef_invalid_tlv_len = ProtoExpert.new("cacipc.ef_invalid_tlv_len.expert", "TLV length is invalid",
    expert.group.MALFORMED, expert.severity.ERROR)
-- Warnings.
local ef_unsupported_msg = ProtoExpert.new("cacipc.ef_unsupported_msg.expert", "Unsupported CAC IPC message",
  expert.group.UNDECODED, expert.severity.WARN)

local ef_unsupported_tlv = ProtoExpert.new("cacipc.ef_unsupported_tlv.expert", "Unsupported TLV (or TV) entry",
  expert.group.UNDECODED, expert.severity.WARN)


-- Functions to handle basic TLV values.
local function handle_boolean(tree, tlv_field, tlv_type, tlv_value)
  return tree:add_packet_field(tlv_field, tlv_value, ENC_BIG_ENDIAN)
end
local function handle_numeric(tree, tlv_field, tlv_type, tlv_value)
  -- It is a TV instead of a TLV. The value is little endian (16 bits unsigned integer).
  if bit.band(tlv_type:uint(), 0x8000) == 0x8000 then
    return tree:add_packet_field(tlv_field, tlv_value, ENC_BIG_ENDIAN)
  else
    return tree:add_packet_field(tlv_field, tlv_value, ENC_LITTLE_ENDIAN)
  end
end
local function handle_string8(tree, tlv_field, tlv_type, tlv_value)
  return tree:add_packet_field(tlv_field, tlv_value, ENC_UTF_8)
end
local function handle_string16(tree, tlv_field, tlv_type, tlv_value)
  return tree:add_packet_field(tlv_field, tlv_value, ENC_LITTLE_ENDIAN + ENC_UTF_16)
end
local function handle_buffer(tree, tlv_field, tlv_type, tlv_value)
  return tree:add_packet_field(tlv_field, tlv_value, ENC_NA)
end

-- Function to handle a sequence of TLVs. It returns the number of bytes consumed/visited during the execution.
local function handle_sequence(tree, handler, tvbuf)
  local index = 0

  while index < tvbuf:len() do
    local tlv_type = tvbuf(index + 0, 2)

    local tlv_length = nil
    local tlv_value = nil
    local tlv_entry = nil

    if bit.band(tlv_type:uint(), 0x8000) == 0x8000 then
      -- Entry is a TV.
      tlv_value = tvbuf(index + 2, 2)
    else
      -- Entry is a TLV.
      tlv_length = tvbuf(index + 2, 2)

      if (index + 4 + tlv_length:uint()) > tvbuf:len() then
        -- Report that the TLV entry's length is invalid.
        tree:add_tvb_expert_info(ef_invalid_tlv_len, tlv_length)

        -- Exit from the loop, since the specified TLV length exceeds the length of the buffer, there is no way
        -- to figure out where the next TLV starts (if at all). So the best is to bail.
        break
      end

      tlv_value = tvbuf(index + 4, tlv_length:uint())
    end

    -- Get the field for the TLV (or TV) if known by the handler.
    local tlv_field = handler.fields[bit.band(tlv_type:uint(), 0x1fff)]

    if tlv_field ~= nil then
      tlv_entry = tlv_field.handle(tree, tlv_field.field, tlv_type, tlv_value)

      -- Add the TLV (or TV) packet data information.
      tlv_entry:add(field_type, tlv_type)

      if tlv_length ~= nil then
        tlv_entry:add(field_length, tlv_length)
      end

      tlv_entry:add(field_value, tlv_value)
    else
      -- Calculate the entire TLV entry length so that we can reference all its bytes in the expert info that
      -- will be added.
      local tlv_entry_len = 4

      if tlv_length ~= nil then
        tlv_entry_len = tlv_entry_len + tlv_length:uint()
      end

      -- Report that the TLV entry's type is not supported.
      tree:add_tvb_expert_info(ef_unsupported_tlv, tvbuf(index, tlv_entry_len))
    end

    if tlv_length ~= nil then
      index = index + 4 + tlv_length:uint()
    else
      index = index + 4
    end
  end

  return index
end

-- Handling the various supported messages.
-- CAcknowledge message.
local handler_acknowledge = {
  fields = {
    [0x0001] = {
      field = field_int32("cacipc.acknowledge.ack_value", "Acknowledge Value"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_uint32("cacipc.aknowledge.system_error_value", "System Error Value"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (
      msg_type == 0x00
    )
    and (
      msg_id == 0x03 or msg_id == 0x09 or msg_id == 0x0c or msg_id == 0x12 or msg_id == 0x24
    )
  end,
  name = "CAcknowledge"
}

-- CApiCommandTlv message.
local handler_api_command = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.apicommand.string_param", "String Parameter"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (
      msg_type == 0x0c
    )
    and (
      msg_id == 0x14 or msg_id == 0x16 or msg_id == 0x22
    )
  end,
  name = "CApiCommandTlv"
}

-- CCertificateAuthTlv message.
local handler_certificate_auth = {
  fields = {
    [0x0001] = {
      field = field_bytes("cacipc.certificateauth.en_password", "Encrypted Password"),
      handle = handle_buffer
    },
    [0x0002] = {
      field = field_string("cacipc.certificateauth.client_cert_thumbprint", "Client Certificate Thumbprint"),
      handle = handle_string8
    },
    [0x0003] = {
      field = field_string("cacipc.certificateauth.server_cert_thumbprint", "Server Certificate Thumbprint"),
      handle = handle_string8
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x0e)
  end,
  name = "CCertificateAuthTlv"
}

-- CCertificateInfoTlv handler, since it isn't a IPC message.
local handler_certificate_info = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.certificateinfo.thumbprint", "Thumbprint"),
      handle = handle_string16
    },
    [0x0002] = {
      field = field_uint32("cacipc.certificateinfo.cert_store", "Certificate Store"),
      handle = handle_numeric
    },
    [0x0003] = {
      field = field_bytes("cacipc.certificateinfo.cert_pkcs7", "Certificate PKCS7"),
      handle = handle_buffer
    },
    [0x0004] = {
      field = field_string("cacipc.certificateinfo.container_name", "Container Name"),
      handle = handle_string16
    },
    [0x0005] = {
      field = field_string("cacipc.certificateinfo.provider_name", "Provider Name"),
      handle = handle_string16
    },
    [0x0006] = {
      field = field_uint32("cacipc.certificateinfo.provider_type", "Provider Type"),
      handle = handle_numeric
    },
    [0x0007] = {
      field = field_bool("cacipc.certificateinfo.from_smartcard", "From Smartcard"),
      handle = handle_boolean
    },
    [0x0009] = {
      field = field_string("cacipc.certificateinfo.reader_name", "Reader Name"),
      handle = handle_string16
    },
    [0x000a] = {
      field = field_string("cacipc.certificateinfo.cert_store_multi_cert_auth", "Store Multi-Certificate Authentication"),
      handle = handle_string16
    },
    [0x000b] = {
      field = field_string("cacipc.certificateinfo.cert_base64", "Certificate Base64"),
      handle = handle_string16
    },
    [0x000c] = {
      field = field_string("cacipc.certificateinfo.cert_format", "Certificate Format"),
      handle = handle_string16
    },
    [0x000d] = {
      field = field_string("cacipc.certificateinfo.cert_auth_signature_base64", "Authentication Signature Base64"),
      handle = handle_string16
    },
    [0x000e] = {
      field = field_string("cacipc.certificateinfo.cert_auth_signature_hash_alg", "Authentication Signature Hash Algorithm"),
      handle = handle_string16
    },
    [0x000f] = {
      field = field_bool("cacipc.certificateinfo.cert_exchanged_via_protocol", "Exchanged Via Protocol"),
      handle = handle_boolean
    },
    [0x0010] = {
      field = field_string("cacipc.certificateinfo.ksp_name", "KSP Name"),
      handle = handle_string16
    },
  },
  -- This TLV is not a IPC TLV, so always return false.
  is_supported = function (msg_type, msg_id)
    return false
  end,
}

-- CConnectFailureTlv message.
local handler_connect_failure = {
  fields = {
    [0x0001] = {
      field = field_uint32("cacipc.connectfailure.failure_reason", "Failure Reason"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x03 and msg_id == 0x1e)
  end,
  name = "CConnectFailureTlv"
}

-- CConnectIfcDataTLV message.
local handler_connect_ifc_data = {
  fields = {
    [0x0001] = {
      field = field_uint16("cacipc.connectifcdata.connect_message_type", "Connect Message Type"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_uint32("cacipc.connectifcdata.connect_message_result", "Connect Message Result"),
      handle = handle_numeric
    },
    [0x0003] = {
      field = field_uint32("cacipc.connectifcdata.pid", "Process Identifier"),
      handle = handle_numeric
    },
    [0x0004] = {
      field = field_string("cacipc.connectifcdata.last_connect_error", "Last Connect Error"),
      handle = handle_string16
    },
    [0x0005] = {
      field = field_string("cacipc.connectifcdata.config_cookie", "Configuration Cookie"),
      handle = handle_string16
    },
    [0x0006] = {
      field = field_string("cacipc.connectifcdata.auh_cookie", "Auhentication Cookie"),
      handle = handle_string16
    },
    [0x0007] = {
      field = field_string("cacipc.connectifcdata.response_string", "Response String"),
      handle = handle_string8
    },
    [0x0008] = {
      field = field_string("cacipc.connectifcdata.cert_match_pattern", "Certificate Match Pattern"),
      handle = handle_string16
    },
    [0x0009] = {
      field = field_string("cacipc.connectifcdata.enrollment_cah_ref", "Enrollment CAH Reference"),
      handle = handle_string16
    },
    [0x000a] = {
      field = field_uint16("cacipc.connectifcdata.response_type", "Response Type"),
      handle = handle_numeric
    },
    [0x000b] = {
      field = field_uint16("cacipc.connectifcdata.op_code", "Operation Code"),
      handle = handle_numeric
    },
    [0x000c] = {
      field = field_string("cacipc.connectifcdata.server_cert_thumbprint", "Server Certificate Thumbprint"),
      handle = handle_string16
    },
    [0x000f] = {
      field = field_string("cacipc.connectifcdata.client_cert_thumbprint", "Client Certificate Thumbprint"),
      handle = handle_string16
    },
    [0x0010] = {
      field = field_string("cacipc.connectifcdata.proxy_host", "Proxy Host"),
      handle = handle_string16
    },
    [0x0011] = {
      field = field_string("cacipc.connectifcdata.proxy_port", "Proxy Port"),
      handle = handle_string16
    },
    [0x0012] = {
      field = field_string("cacipc.connectifcdata.proxy_realm", "Proxy Realm"),
      handle = handle_string16
    },
    [0x0013] = {
      field = field_string("cacipc.connectifcdata.proxy_message", "Proxy Message"),
      handle = handle_string16
    },
    [0x0014] = {
      field = field_uint16("cacipc.connectifcdata.proxy_type", "Proxy Type"),
      handle = handle_numeric
    },
    [0x0015] = {
      field = field_bytes("cacipc.connectifcdata.proxy_en_principal", "Proxy Encrypted Principal"),
      handle = handle_buffer
    },
    [0x0016] = {
      field = field_bytes("cacipc.connectifcdata.proxy_en_password", "Proxy Encrypted Password"),
      handle = handle_buffer
    },
    [0x0017] = {
      field = field_bytes("cacipc.connectifcdata.proxy_en_authority", "Proxy Encrypted Authority"),
      handle = handle_buffer
    },
    [0x0018] = {
      field = field_string("cacipc.connectifcdata.peer_url", "Peer URL"),
      handle = handle_string16
    },
    [0x0019] = {
      field = field_string("cacipc.connectifcdata.orig_peer_url", "Original Peer URL"),
      handle = handle_string16
    },
    [0x001a] = {
      field = field_string("cacipc.connectifcdata.credentials_name", "Credentials Name"),
      handle = handle_string16
    },
    [0x001b] = {
      field = field_string("cacipc.connectifcdata.credentials_value", "Credentials Value"),
      handle = handle_string16
    },
    [0x001c] = {
      field = field_uint16("cacipc.connectifcdata.credentials_count", "Credentials Count"),
      handle = handle_numeric
    },
    [0x001d] = {
      field = field_uint16("cacipc.connectifcdata.content_type", "Content Type"),
      handle = handle_numeric
    },
    [0x001e] = {
      field = field_bytes("cacipc.connectifcdata.data_blob_buffer", "Data Blob Buffer"),
      handle = handle_buffer
    },
    [0x001f] = {
      field = field_string("cacipc.connectifcdata.dest_file_path", "Destination File Path"),
      handle = handle_string16
    },
    [0x0020] = {
      field = field_string("cacipc.connectifcdata.csd_token", "CSD Token"),
      handle = handle_string16
    },
    [0x0021] = {
      field = field_string("cacipc.connectifcdata.csd_ticket", "CSD Ticket"),
      handle = handle_string16
    },
    [0x0022] = {
      field = field_string("cacipc.connectifcdata.csd_stub_url", "CSD Stub URL"),
      handle = handle_string16
    },
    [0x0023] = {
      field = field_string("cacipc.connectifcdata.csd_start_url", "CSD Start URL"),
      handle = handle_string16
    },
    [0x0024] = {
      field = field_int32("cacipc.connectifcdata.csd_token_verified", "CSD Token Verified"),
      handle = handle_numeric
    },
    [0x0025] = {
      field = field_int32("cacipc.connectifcdata.processed_csd_data", "Processed CSD Data"),
      handle = handle_numeric
    },
    [0x0026] = {
      field = field_int32("cacipc.connectifcdata.csd_event_fired", "CSD Event Fired"),
      handle = handle_numeric
    },
    [0x0027] = {
      field = field_int32("cacipc.connectifcdata.verify_csd_token_only", "Verify CSD Token Only"),
      handle = handle_numeric
    },
    [0x002a] = {
      field = field_string("cacipc.connectifcdata.group_url_cookie", "Group URL Cookie"),
      handle = handle_string16
    },
    [0x002b] = {
      field = field_uint16("cacipc.connectifcdata.protocol_type", "Protocol Type"),
      handle = handle_numeric
    },
    [0x002c] = {
      field = field_uint16("cacipc.connectifcdata.ike_auth_method", "IKE Authentication Method"),
      handle = handle_numeric
    },
    [0x002d] = {
      field = field_string("cacipc.connectifcdata.ike_identity", "IKE Identity"),
      handle = handle_string16
    },
    [0x002e] = {
      field = field_string("cacipc.connectifcdata.agg_auth_request", "Aggregated Authentication Request"),
      handle = handle_string16
    },
    [0x002f] = {
      field = field_string("cacipc.connectifcdata.agg_auth_flag", "Aggregated Authentication Flag"),
      handle = handle_string16
    },
    [0x0030] = {
      field = field_string("cacipc.connectifcdata.proxy_string", "Proxy String"),
      handle = handle_string16
    },
    [0x0031] = {
      field = field_bool("cacipc.connectifcdata.is_sbl", "Is SBL"),
      handle = handle_boolean
    },
    [0x0032] = {
      field = field_string("cacipc.connectifcdata.peer_primary_address", "Peer Primary Address"),
      handle = handle_string16
    },
    [0x0033] = {
      field = field_string("cacipc.connectifcdata.peer_secondary_address", "Peer Secondary Address"),
      handle = handle_string16
    },
    [0x0034] = {
      field = field_bool("cacipc.connectifcdata.client_auth_cert_needed", "Client Authentication Certificate Needed"),
      handle = handle_boolean
    },
    [0x0035] = {
      field = field_bool("cacipc.connectifcdata.use_peer_primary_ip_address", "Use Peer Primary IP Address"),
      handle = handle_boolean
    },
    [0x0036] = {
      field = field_uint16("cacipc.connectifcdata.protocol_version", "Protocol Version"),
      handle = handle_numeric
    },
    [0x0037] = {
      field = field_uint16("cacipc.connectifcdata.vpn_tunnel_scope", "VPN Tunnel Scope"),
      handle = handle_numeric
    },
    [0x0038] = {
      field = field_uint32("cacipc.connectifcdata.client_cert_store_type", "Client Certificate Store Type"),
      handle = handle_numeric
    },
    [0x0039] = {
      field = field_string("cacipc.connectifcdata.strap_pub_key", "Srap Public Key"),
      handle = handle_string16
    },
    [0x003a] = {
      field = field_string("cacipc.connectifcdata.strap_dh_pub_key", "Srap DH Public Key"),
      handle = handle_string16
    },
    [0x003b] = {
      field = field_string("cacipc.connectifcdata.sg_friendly_host_name", "Security Gateway Friendly Host Name"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x01 and msg_id == 0x13)
  end,
  name = "CConnectIfcDataTLV"
}

-- CDnldrArgsTlv message.
-- Helper function to handle embedded CCertificateInfoTlv in the message. Used by other messages as well.
local function handle_certificate(tree, tlv_field, tlv_type, tlv_value)
  local branch = tree:add_packet_field(tlv_field, tlv_value, ENC_NA)

  -- Pointer to the current value position.
  local index = 0

  -- Only go through if there is space for at least one TV pair.
  if tlv_value:len() >= 4 then
    handle_sequence(branch, handler_certificate_info, tlv_value)
  end

  return branch
end
-- The actual handler for CDnldrArgsTlv. 
local handler_dnldr_args = {
  -- TODO: Missing support for GetAggAuthCertificateInfo and GetCertificateInfo.
  fields = {
    [0x0001] = {
      field = field_string("cacipc.dnldrargs.config_xml", "Configuration XML"),
      handle = handle_string16
    },
    [0x0002] = {
      field = field_string("cacipc.dnldrargs.session_token", "Session Token"),
      handle = handle_string16
    },
    [0x0003] = {
      field = field_string("cacipc.dnldrargs.session_id", "Session Identifier"),
      handle = handle_string16
    },
    [0x0004] = {
      field = field_string("cacipc.dnldrargs.gateway_url", "Gateway URL"),
      handle = handle_string16
    },
    [0x0005] = {
      field = field_string("cacipc.dnldrargs.base_uri", "Base URI"),
      handle = handle_string16
    },
    [0x0006] = {
      field = field_string("cacipc.dnldrargs.server_certificate_hash", "Server Certificate Hash"),
      handle = handle_string16
    },
    [0x0007] = {
      field = field_string("cacipc.dnldrargs.client_cert_hash", "Client Certificate Hash"),
      handle = handle_string16
    },
    [0x0008] = {
      field = field_string("cacipc.dnldrargs.optinal_modules", "Optional Modules"),
      handle = handle_string16
    },
    [0x0009] = {
      field = field_string("cacipc.dnldrargs.profile_uri", "Profile URI"),
      handle = handle_string16
    },
    [0x000a] = {
      field = field_string("cacipc.dnldrargs.profile_hash", "Profile Hash"),
      handle = handle_string16
    },
    [0x000b] = {
      field = field_string("cacipc.dnldrargs.l10n_uri", "Localization URI"),
      handle = handle_string16
    },
    [0x000c] = {
      field = field_string("cacipc.dnldrargs.cfg_cookie", "Confguration Cookie"),
      handle = handle_string16
    },
    [0x000d] = {
      field = field_uint32("cacipc.dnldrargs.conection_type", "Connection Type"),
      handle = handle_numeric
    },
    [0x000e] = {
      field = field_uint32("cacipc.dnldrargs.tunnel_state", "Tunnel State"),
      handle = handle_numeric
    },
    [0x000f] = {
      field = field_uint32("cacipc.dnldrargs.operation_mode", "Operaton Mode"),
      handle = handle_numeric
    },
    [0x0011] = {
      field = field_bool("cacipc.dnldrargs.determine_proxy", "Determine Proxy"),
      handle = handle_boolean
    },
    [0x0012] = {
      field = field_string("cacipc.dnldrargs.proxy_string", "Proxy String"),
      handle = handle_string16
    },
    [0x0013] = {
      field = field_string("cacipc.dnldrargs.proxy_host", "Proxy Host"),
      handle = handle_string16
    },
    [0x0014] = {
      field = field_string("cacipc.dnldrargs.proxy_port", "Proxy Port"),
      handle = handle_string16
    },
    [0x0015] = {
      field = field_string("cacipc.dnldrargs.proxy_realm", "Proxy Realm"),
      handle = handle_string16
    },
    [0x0016] = {
      field = field_uint16("cacipc.dnldrargs.proxy_type", "Proxy Type"),
      handle = handle_numeric
    },
    [0x0017] = {
      field = field_string("cacipc.dnldrargs.proxy_message", "Proxy Message"),
      handle = handle_string16
    },
    [0x0018] = {
      field = field_string("cacipc.dnldrargs.proxy_user", "Proxy User"),
      handle = handle_string16
    },
    [0x0019] = {
      field = field_string("cacipc.dnldrargs.proxy_password", "Proxy Password"),
      handle = handle_string16
    },
    [0x001a] = {
      field = field_string("cacipc.dnldrargs.proxy_authority", "Proxy Authority"),
      handle = handle_string16
    },
    [0x001b] = {
      field = field_bool("cacipc.dnldrargs.using_smartcard", "Using Smartcard"),
      handle = handle_boolean
    },
    [0x001c] = {
      field = field_string("cacipc.dnldrargs.gateway_primary_ip_address", "Gateway Primary IP Address"),
      handle = handle_string16
    },
    [0x001d] = {
      field = field_string("cacipc.dnldrargs.gateway_secondary_ip_address", "Gateway Secondary IP Address"),
      handle = handle_string16
    },
    [0x001e] = {
      field = field_bytes("cacipc.dnldrargs.certificate_info", "Certificate Information"),
      handle = handle_certificate
    },
    [0x001f] = {
      field = field_bytes("cacipc.dnldrargs.agg_certificate_info", "Aggregated Certificate Information"),
      handle = handle_certificate
    },
    [0x0020] = {
      field = field_string("cacipc.dnldrargs.sg_friendly_host_name", "Security Gateway Friendly Host Name"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x09 and msg_id == 0x1a)
  end,
  name = "CDnldrArgsTlv"
}

-- CIpcClosingTlv message.
local handler_ipcclosing = {
  fields = {
    [0x0001] = {
      field = field_uint32("cacipc.ipcclosing.exit_status", "Exit Status"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x05 and msg_id == 0x0d)
  end,
  name = "CIpcClosingTlv"
}

-- CKeyExchangeTlv message.
local handler_keyexchange = {
  fields = {
    [0x0001] = {
      field = field_bytes("cacipc.keyexchange.public_key", "Public Key"),
      handle = handle_buffer
    },
    [0x0002] = {
      field = field_bytes("cacipc.keyexchange.encrypted_key", "Encrypted Key"),
      handle = handle_buffer
    },
    [0x0003] = {
      field = field_uint16("cacipc.keyexchange.vpn_tunnel_scope", "VPN Tunnel Scope"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x1d)
  end,
  name = "CKeyExchangeTlv"
}

-- CLaunchClientAppTlv message.
local handler_launchclientapp = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.launchclientapp.file_path", "File Path"),
      handle = handle_string8
    },
    [0x0002] = {
      field = field_string("cacipc.launchclientapp.cmd_line", "Command Line"),
      handle = handle_string8
    },
    [0x0004] = {
      field = field_string("cacipc.launchclientapp.gui_desktop", "GUI Desktop"),
      handle = handle_string8
    },
    [0x0005] = {
      field = field_bool("cacipc.launchclientapp.use_installed", "Used Installed"),
      handle = handle_boolean
    },
    [0x0006] = {
      field = field_string("cacipc.launchclientapp.relocatable_file_path", "Relocatable File Path"),
      handle = handle_string8
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x01 and msg_id == 0x02)
  end,
  name = "CLaunchClientAppTlv"
}

-- CLocalLan message.
local handler_local_lan = {
  fields = {
    [0x0001] = {
      field = field_bool("cacipc.locallan.local_lan_flag", "Local LAN Flag"),
      handle = handle_boolean
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x07)
  end,
  name = "CLocalLan"
}

-- CMessageTypeBitmapTlv message.
local handler_messagetypebitmap = {
  fields = {
    [0x0001] = {
      field = field_uint32("cacipc.messagetypebitmap.message_type_bitmap", "Message Type Bitmap"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_string("cacipc.messagetypebitmap.application_name", "Application Name"),
      handle = handle_string8
    },
    [0x0003] = {
      field = field_bool("cacipc.messagetypebitmap.notification_flag", "Notification Flag"),
      handle = handle_boolean
    },
    [0x0004] = {
      field = field_uint32("cacipc.messagetypebitmap.pid", "Process Identifier"),
      handle = handle_numeric
    },
    [0x0005] = {
      field = field_uint32("cacipc.messagetypebitmap.app_operation_mode", "Application Operation Mode"),
      handle = handle_numeric
    },
    [0x0006] = {
      field = field_uint32("cacipc.messagetypebitmap.active_client_policy", "Active Client Policy"),
      handle = handle_numeric
    },
    [0x0007] = {
      field = field_uint32("cacipc.messagetypebitmap.num_same_app_registration", "Same Application Registration"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x05 and msg_id == 0x00)
  end,
  name = "CMessageTypeBitmapTlv"
}

-- CNotifyAgentPreTunnelTlv message.
local handler_notify_agent_pre_tunnel = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.notifyagentpretunnel.host_address", "Host Address"),
      handle = handle_string16
    },
    [0x0002] = {
      field = field_string("cacipc.notifyagentpretunnel.host_protocol", "Host Protocol"),
      handle = handle_string16
    },
    [0x0003] = {
      field = field_uint32("cacipc.notifyagentpretunnel.ui_process_id", "User Interface Process Identifier"),
      handle = handle_numeric
    },
    [0x0004] = {
      field = field_bool("cacipc.notifyagentpretunnel.connect_continue", "Connect Continue"),
      handle = handle_boolean
    },
    [0x0005] = {
      field = field_string("cacipc.notifyagentpretunnel.profile_name", "Profile Name"),
      handle = handle_string16
    },
    [0x0006] = {
      field = field_string("cacipc.notifyagentpretunnel.primary_host_address", "Primary Host Address"),
      handle = handle_string16
    },
    [0x0007] = {
      field = field_string("cacipc.notifyagentpretunnel.secondary_host_ip_address", "Secondary Host IP Address"),
      handle = handle_string16
    },
    [0x0008] = {
      field = field_uint32("cacipc.notifyagentpretunnel.connect_stop_reason", "Connect Stop Reason"),
      handle = handle_numeric
    },
    [0x0009] = {
      field = field_bool("cacipc.notifyagentpretunnel.determine_proxy", "Determine Proxy"),
      handle = handle_boolean
    },
    [0x000d] = {
      field = field_string("cacipc.notifyagentpretunnel.proxy_string", "Proxy String"),
      handle = handle_string16
    },
    [0x000e] = {
      field = field_bool("cacipc.notifyagentpretunnel.host_requires_proxy_with_always_on", "Host Requires Proxy With Always On"),
      handle = handle_boolean
    },
    [0x000f] = {
      field = field_bool("cacipc.notifyagentpretunnel.host_might_require_proxy_with_always_on", "Host Might Require Proxy With Always On"),
      handle = handle_boolean
    },
    [0x0010] = {
      field = field_string("cacipc.notifyagentpretunnel.device_unique_id", "Device Unique Identifier"),
      handle = handle_string16
    },
    [0x0011] = {
      field = field_string("cacipc.notifyagentpretunnel.platform_version", "Platform Version"),
      handle = handle_string16
    },
    [0x0012] = {
      field = field_string("cacipc.notifyagentpretunnel.device_type", "Device Type"),
      handle = handle_string16
    },
    [0x0013] = {
      field = field_string("cacipc.notifyagentpretunnel.mac_address", "MAC Address"),
      handle = handle_string16
    },
    [0x0014] = {
      field = field_string("cacipc.notifyagentpretunnel.device_name", "Device Name"),
      handle = handle_string16
    },
    [0x0015] = {
      field = field_string("cacipc.notifyagentpretunnel.device_global_unique_id", "Device Global Unique Identifier"),
      handle = handle_string16
    },
    [0x0016] = {
      field = field_uint32("cacipc.notifyagentpretunnel.vpn_tunnel_scope", "VPN Tunnel Scope"),
      handle = handle_numeric
    },
    [0x0017] = {
      field = field_string("cacipc.notifyagentpretunnel.strap_public_key", "Strap Public Key"),
      handle = handle_string16
    },
    [0x0018] = {
      field = field_string("cacipc.notifyagentpretunnel.strap_dh_public_key", "Strap DH Public Key"),
      handle = handle_string16
    },
    [0x0019] = {
      field = field_string("cacipc.notifyagentpretunnel.encoded_sso_token", "Encoded SSO Token"),
      handle = handle_string16
    },
    [0x001a] = {
      field = field_string("cacipc.notifyagentpretunnel.decoded_sso_token", "Decoded SSO Token"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (
      msg_type == 0x01
    )
    and (
      msg_id == 0x15 or msg_id == 0x17 or msg_id == 0x20 or msg_id == 0x25 or msg_id == 0x2b or msg_id == 0x2c
    )
  end,
  name = "CNotifyAgentPreTunnelTlv"
}

-- CPreferenceUpdateTlv message.
local handler_preference_update = {
  fields = {
    [0x0001] = {
      field = field_uint32("cacipc.preferenceupdate.preference_count", "Preference Count"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_uint32("cacipc.preferenceupdate.preference_setting_id", "Preference Setting Identifier"),
      handle = handle_numeric
    },
    [0x0003] = {
      field = field_string("cacipc.preferenceupdate.preference_setting_value", "Preference Setting Value"),
      handle = handle_string16
    },
    [0x0004] = {
      field = field_uint32("cacipc.preferenceupdate.auto_preference_count", "Auto Preference Count"),
      handle = handle_numeric
    },
    [0x0005] = {
      field = field_uint32("cacipc.preferenceupdate.auto_preference_setting_id", "Auto Preference Setting Identifier"),
      handle = handle_numeric
    },
    [0x0006] = {
      field = field_string("cacipc.preferenceupdate.auto_preference_setting_value", "Auto Preference Setting Value"),
      handle = handle_string16
    },
    [0x0007] = {
      field = field_string("cacipc.preferenceupdate.profile_name", "Profile Name"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x07 and msg_id == 0x11)
  end,
  name = "CPreferenceUpdateTlv"
}

-- CProxyAuthentication message.
local handler_proxy_authentication = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.proxyauthentication.server_name", "Server Name"),
      handle = handle_string8
    },
    [0x0002] = {
      field = field_string("cacipc.proxyauthentication.realm", "Realm"),
      handle = handle_string8
    },
    [0x0003] = {
      field = field_string("cacipc.proxyauthentication.scheme", "Scheme"),
      handle = handle_string8
    },
    [0x0004] = {
      field = field_bytes("cacipc.proxyauthentication.en_principal", "Encrypted Principal"),
      handle = handle_buffer
    },
    [0x0005] = {
      field = field_bytes("cacipc.proxyauthentication.en_password", "Encrypted Password"),
      handle = handle_buffer
    },
    [0x0006] = {
      field = field_bytes("cacipc.proxyauthentication.en_authority", "Encrypted Authority"),
      handle = handle_buffer
    },
    [0x0007] = {
      field = field_string("cacipc.proxyauthentication.error_message", "Error Message"),
      handle = handle_string8
    },
    [0x0008] = {
      field = field_string("cacipc.proxyauthentication.sg_domain_name", "Security Gateway Domain Name"),
      handle = handle_string8
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x06)
  end,
  name = "CProxyAuthentication"
}

-- CRedirectTlv message.
local handler_redirect = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.redirect.redirect_address", "Redirect Address"),
      handle = handle_string16
    },
    [0x0002] = {
      field = field_string("cacipc.redirect.primary_ip_address", "Primary IP Address"),
      handle = handle_string16
    },
    [0x0003] = {
      field = field_string("cacipc.redirect.secondary_ip_address", "Secondary IP Address"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x1c)
  end,
  name = "CRedirectTlv"
}

-- CRequestDnldrArgsTlv message.
local handler_request_dnldr_args = {
  fields = {
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x02 and msg_id == 0x19) or (msg_type == 0x0b and msg_id == 0x26)
  end,
  name = "CRequestDnldrArgsTlv"
}

-- CSessionCommandTlv message.
local handler_session_command = {
  fields = {
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x06 and msg_id == 0x0b)
  end,
  name = "CSessionCommandTlv"
}

-- CSessionInfoTlv message.
local handler_session_info = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.sessioninfo.client_iv4_addr", "Client IPv4 Address"),
      handle = handle_string8
    },
    [0x0002] = {
      field = field_string("cacipc.sessioninfo.client_iv6_addr", "Client IPv6 Address"),
      handle = handle_string8
    },
    [0x0003] = {
      field = field_string("cacipc.sessioninfo.sg_address", "Security Gateway Address"),
      handle = handle_string8
    },
    [0x0004] = {
      field = field_string("cacipc.sessioninfo.sg_host_name", "Security Gateway Host Name"),
      handle = handle_string8
    },
    [0x0005] = {
      field = field_string("cacipc.sessioninfo.proxy_ip_address", "Proxy IP Address"),
      handle = handle_string8
    },
    [0x0006] = {
      field = field_string("cacipc.sessioninfo.proxy_host_name", "Proxy Host Name"),
      handle = handle_string8
    },
    [0x0007] = {
      field = ProtoField.uint16("cacipc.sessioninfo.proxy_port", "Proxy Port"),
      handle = handle_numeric
    },
    [0x0008 + 0x00] = {
      field = ProtoField.uint16("cacipc.sessioninfo.tuneling_mode_ipv4", "Tunneling Mode (IPv4)"),
      handle = handle_numeric
    },
    [0x0008 + 0x01] = {
      field = ProtoField.uint16("cacipc.sessioninfo.tuneling_mode_ipv6", "Tunneling Mode (IPv6)"),
      handle = handle_numeric
    },
    [0x000c + 0x00] = {
      field = ProtoField.bytes("cacipc.sessioninfo.dynamic_secure_routes_ipv4", "Dynamic Secure Routes (IPv4)"),
      handle = handle_buffer
    },
    [0x000c + 0x01] = {
      field = ProtoField.bytes("cacipc.sessioninfo.dynamic_secure_routes_ipv6", "Dynamic Secure Routes (IPv6)"),
      handle = handle_buffer
    },
    [0x000e] = {
      field = field_string("cacipc.sessioninfo.split_tun_domains_1", "Split Tunnel Domains (DYN_SPLIT_TUN_TYPE != 0)"),
      handle = handle_string8
    },
    [0x000f + 0x00] = {
      field = ProtoField.uint16("cacipc.sessioninfo.applied_secure_route_count_ipv4", "Applied Secure Route Count (IPv4)"),
      handle = handle_numeric
    },
    [0x000f + 0x01] = {
      field = ProtoField.uint16("cacipc.sessioninfo.applied_secure_route_count_ipv6", "Applied Secure Route Count (IPv6)"),
      handle = handle_numeric
    },
    [0x000a + 0x00] = {
      field = ProtoField.bytes("cacipc.sessioninfo.secure_routes_ipv4", "Secure Routes (IPv4)"),
      handle = handle_buffer
    },
    [0x000a + 0x01] = {
      field = ProtoField.bytes("cacipc.sessioninfo.secure_routes_ipv6", "Secure Routes (IPv6)"),
      handle = handle_buffer
    },
    [0x0011 + 0x00] = {
      field = ProtoField.bytes("cacipc.sessioninfo.non_secure_routes_ipv4", "Non-Secure Routes (IPv4)"),
      handle = handle_buffer
    },
    [0x0011 + 0x01] = {
      field = ProtoField.bytes("cacipc.sessioninfo.non_secure_routes_ipv6", "Non-Secure Routes (IPv6)"),
      handle = handle_buffer
    },
    [0x0013 + 0x00] = {
      field = ProtoField.bytes("cacipc.sessioninfo.dynamic_non_secure_routes_ipv4", "Dynamic Non-Secure Routes (IPv4)"),
      handle = handle_buffer
    },
    [0x0013 + 0x01] = {
      field = ProtoField.bytes("cacipc.sessioninfo.dynamic_non_secure_routes_ipv6", "Dynamic Non-Secure Routes (IPv6)"),
      handle = handle_buffer
    },
    [0x0015] = {
      field = field_string("cacipc.sessioninfo.split_tun_domains_2", "Split Tunnel Domains (DYN_SPLIT_TUN_TYPE == 0)"),
      handle = handle_string8
    },
    [0x0016 + 0x00] = {
      field = ProtoField.uint16("cacipc.sessioninfo.applied_non_secure_route_count_ipv4", "Applied Non-Secure Route Count (IPv4)"),
      handle = handle_numeric
    },
    [0x0016 + 0x01] = {
      field = ProtoField.uint16("cacipc.sessioninfo.applied_non_secure_route_count_ipv6", "Applied Non-Secure Route Count (IPv6)"),
      handle = handle_numeric
    },
    [0x0018] = {
      field = ProtoField.uint32("cacipc.sessioninfo.client_operation_mode", "Client Operation Mode"),
      handle = handle_numeric
    },
    [0x0019] = {
      field = field_string("cacipc.sessioninfo.invoked_by_code", "Invoked by Code"),
      handle = handle_string16
    },
    [0x001a] = {
      field = ProtoField.uint16("cacipc.sessioninfo.quarantine_state", "Quarantine State"),
      handle = handle_numeric
    },
    [0x001b] = {
      field = ProtoField.uint16("cacipc.sessioninfo.always_on_vpn", "Always On VPN"),
      handle = handle_numeric
    },
    [0x001c] = {
      field = field_string("cacipc.sessioninfo.dap_user_message", "DAP User Message"),
      handle = handle_string16
    },
    [0x001d] = {
      field = ProtoField.bytes("cacipc.sessioninfo.fw_rules", "Firewall Rules"),
      handle = handle_buffer
    },
    [0x001e] = {
      field = ProtoField.uint16("cacipc.sessioninfo.vpn_protocol", "VPN Protocol"),
      handle = handle_numeric
    },
    [0x001f] = {
      field = field_string("cacipc.sessioninfo.administrative_domain", "Administrative Domain"),
      handle = handle_string16
    },
    [0x0020] = {
      field = field_string("cacipc.sessioninfo.profile_name", "Profile Name"),
      handle = handle_string16
    },
    [0x0021] = {
      field = field_string("cacipc.sessioninfo.on_connect_script_name", "On Connect Script Name"),
      handle = handle_string16
    },
    [0x0022] = {
      field = field_string("cacipc.sessioninfo.on_disconnect_script_name", "On Disconnect Script Name"),
      handle = handle_string16
    },
    [0x0023] = {
      field = ProtoField.uint16("cacipc.sessioninfo.session_info_scope", "Session Information Scope", base.HEX),
      handle = handle_numeric
    },
    [0x0024] = {
      field = field_string("cacipc.sessioninfo.sg_friendly_host_name", "Security Gateway Friendly Host Name"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x08 and msg_id == 0x10)
  end,
  name = "CSessionInfoTlv"
}

-- CStartParameters message.
local handler_start_parameters = {
  fields = {
    [0x0001] = {
      field = field_string("cacipc.startparameters.sg_url", "Security Gateway URL"),
      handle = handle_string8
    },
    [0x0002] = {
      field = field_string("cacipc.startparameters.sg_cookie", "Security Gateway Cookie"),
      handle = handle_string8
    },
    [0x0003] = {
      field = field_uint32("cacipc.startparameters.initiator_pid", "Initiator PID"),
      handle = handle_numeric
    },
    [0x0004] = {
      field = field_string("cacipc.startparameters.gui_file_path", "GUI File Path"),
      handle = handle_string16
    },
    [0x0005] = {
      field = field_string("cacipc.startparameters.gui_cmd_line", "GUI Command Line"),
      handle = handle_string16
    },
    [0x0006] = {
      field = field_string("cacipc.startparameters.gui_desktop", "GUI Desktop"),
      handle = handle_string8
    },
    [0x0007] = {
      field = field_string("cacipc.startparameters.primary_sg_ip_addr", "Primary Security Gateway IP Address"),
      handle = handle_string8
    },
    [0x0008] = {
      field = field_string("cacipc.startparameters.cfg_protocol", "Configuration Protocol"),
      handle = handle_string8
    },
    [0x0009] = {
      field = field_string("cacipc.startparameters.cfg_modules", "Configuration Modules"),
      handle = handle_string8
    },
    [0x000a] = {
      field = field_string("cacipc.startparameters.cfg_client_cert_tp", "Configuration Client Certificate Thumbprint"),
      handle = handle_string8
    },
    [0x000b] = {
      field = field_string("cacipc.startparameters.cfg_server_cert_tp", "Configuration Server Certificate Thumbprint"),
      handle = handle_string8
    },
    [0x000c] = {
      field = field_uint32("cacipc.startparameters.invoked_by_code_num", "Invoked by Code (Numeric)"),
      handle = handle_numeric
    },
    [0x000d] = {
      field = field_string("cacipc.startparameters.profile_name", "Profile Name"),
      handle = handle_string16
    },
    [0x000e] = {
      field = field_bool("cacipc.startparameters.wait_for_gui", "Wait For GUI"),
      handle = handle_boolean
    },
    [0x000f] = {
      field = field_string("cacipc.startparameters.invoked_by_code", "Invoked by Code"),
      handle = handle_string16
    },
    [0x0010] = {
      field = field_string("cacipc.startparameters.gui_env", "GUI Environment"),
      handle = handle_string16
    },
    [0x0011] = {
      field = field_uint16("cacipc.startparameters.vpn_type", "VPN Type"),
      handle = handle_numeric
    },
    [0x0012] = {
      field = field_uint16("cacipc.startparameters.auth_method", "Authentication Method"),
      handle = handle_numeric
    },
    [0x0013] = {
      field = field_string("cacipc.startparameters.ike_identity", "IKE Identity"),
      handle = handle_string8
    },
    [0x0014] = {
      field = field_bool("cacipc.startparameters.determine_proxy", "Determine Proxy"),
      handle = handle_boolean
    },
    [0x0015] = {
      field = field_string("cacipc.startparameters.proxy_string", "Proxy String"),
      handle = handle_string16
    },
    [0x0016] = {
      field = field_string("cacipc.startparameters.proxy_host", "Proxy Host"),
      handle = handle_string16
    },
    [0x0017] = {
      field = field_string("cacipc.startparameters.proxy_port", "Proxy Port"),
      handle = handle_string16
    },
    [0x0018] = {
      field = field_uint16("cacipc.startparameters.proxy_type", "Proxy Type"),
      handle = handle_numeric
    },
    [0x0019] = {
      field = field_string("cacipc.startparameters.proxy_realm", "Proxy Realm"),
      handle = handle_string16
    },
    [0x001a] = {
      field = field_string("cacipc.startparameters.proxy_message", "Proxy Message"),
      handle = handle_string16
    },
    [0x001b] = {
      field = field_string("cacipc.startparameters.proxy_user", "Proxy User"),
      handle = handle_string16
    },
    [0x001c] = {
      field = field_string("cacipc.startparameters.proxy_pswd", "Proxy Password"),
      handle = handle_string16
    },
    [0x001d] = {
      field = field_string("cacipc.startparameters.proxy_authority", "Proxy Authority"),
      handle = handle_string16
    },
    [0x001e] = {
      field = field_bytes("cacipc.startparameters.proxy_en_user", "Proxy Encrypted User"),
      handle = handle_buffer
    },
    [0x001f] = {
      field = field_bytes("cacipc.startparameters.proxy_en_pswd", "Proxy Encrypted Password"),
      handle = handle_buffer
    },
    [0x0020] = {
      field = field_bytes("cacipc.startparameters.proxy_en_authority", "Proxy Encrypted Authority"),
      handle = handle_buffer
    },
    [0x0021] = {
      field = field_bool("cacipc.startparameters.using_smartcard", "Using Smartcard"),
      handle = handle_boolean
    },
    [0x0022] = {
      field = field_string("cacipc.startparameters.secondary_sg_ip_addr", "Secondary Security Gateway IP Address"),
      handle = handle_string8
    },
    [0x0023] = {
      field = field_bytes("cacipc.startparameters.certificate_info", "Certificate Information"),
      handle = handle_certificate
    },
    [0x0024] = {
      field = field_bytes("cacipc.startparameters.agg_auth_certificate_info", "Aggregated Certificate Information"),
      handle = handle_certificate
    },
    [0x0025] = {
      field = field_string("cacipc.startparameters.sg_friendly_host_name", "Security Gateway Friendly Host Name"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x01 and msg_id == 0x01)
  end,
  name = "CStartParameters"
}

-- CStateTlv message.
local handler_state = {
  fields = {
    [0x0001] = {
      field = field_uint32("cacipc.state.session_state", "Session Status"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_uint32("cacipc.state.tunnel_count", "Tunnel Count"),
      handle = handle_numeric
    },
    [0x0003] = {
      field = field_uint32("cacipc.state.active_tunnel_index", "Active Tunnel Index"),
      handle = handle_numeric
    },
    [0x0004] = {
      field = field_uint32("cacipc.state.tunnel_state", "Tunnel State"),
      handle = handle_numeric
    },
    [0x0005] = {
      field = field_uint32("cacipc.state.tunnel_protocol_version", "Tunnel Protocol Version"),
      handle = handle_numeric
    },
    [0x0006] = {
      field = field_uint32("cacipc.state.tunnel_protocol_cipher", "Tunnel Protocol Cipher"),
      handle = handle_numeric
    },
    [0x0007] = {
      field = field_uint32("cacipc.state.tunnel_compr_algorithm", "Tunnel Compression Algorithm"),
      handle = handle_numeric
    },
    [0x0008] = {
      field = field_uint32("cacipc.state.aggregate_tunnel_state", "Aggregate Tunnel State"),
      handle = handle_numeric
    },
    [0x0009] = {
      field = field_uint32("cacipc.state.net_env_state", "Network Environment State"),
      handle = handle_numeric
    },
    [0x000a] = {
      field = field_uint32("cacipc.state.net_ctrl_state", "Network Control State"),
      handle = handle_numeric
    },
    [0x000b] = {
      field = field_uint32("cacipc.state.net_type", "Network Type"),
      handle = handle_numeric
    },
    [0x000c] = {
      field = field_uint32("cacipc.state.mus_status", "MUS Status"),
      handle = handle_numeric
    },
    [0x000d] = {
      field = field_string("cacipc.state.mus_host_addr", "MUS Host Address"),
      handle = handle_string16
    },
    [0x000e] = {
      field = field_uint32("cacipc.state.session_sub_state", "Session Sub-State"),
      handle = handle_numeric
    },
    [0x000f] = {
      field = field_uint32("cacipc.state.mgmt_tun_session_state", "Management Tunnel Session State"),
      handle = handle_numeric
    },
    [0x0010] = {
      field = field_uint32("cacipc.state.mgmt_tun_session_sub_state", "Management Tunnel Session Sub-State"),
      handle = handle_numeric
    },
    [0x0011] = {
      field = field_bool("cacipc.state.user_tunnel_state_only", "User Tunnel State Only"),
      handle = handle_boolean
    },
    [0x0012] = {
      field = field_string("cacipc.state.mgmt_tun_sg_host_name", "Management Tunnel Security Gateway Host Name"),
      handle = handle_string16
    },
    [0x0013] = {
      field = field_bool("cacipc.state.ac_browser_for_cp_remediation", "AC Browser For CP Remediation"),
      handle = handle_boolean
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x04 and msg_id == 0x0f)
  end,
  name = "CStateTlv"
}

-- CStatisticsTlv message.
-- Helper function to parse the statistics.
local function handle_statistics(tree, tlv_field, tlv_type, tlv_value)
  local branch = tree:add_packet_field(tlv_field, tlv_value, ENC_NA)

  -- Pointer to the current value position.
  local index = 0

  -- Only go through the statistics if there is at least one entry.
  if tlv_value:len() >= 16 then
    -- While there is data to extract a statistic from.
    while index < tlv_value:len() do

      local leaf = branch:add_packet_field(field_stat_entry, tlv_value(index + 0, 16), ENC_NA)
      leaf:add_packet_field(field_stat_type, tlv_value(index + 0, 4), ENC_LITTLE_ENDIAN)
      leaf:add_packet_field(field_stat_unknown, tlv_value(index + 4, 4), ENC_NA)
      leaf:add_packet_field(field_stat_value, tlv_value(index + 8, 8), ENC_LITTLE_ENDIAN)

      index = index + 16
    end
  end

  return branch
end
-- The actual handler for CStatisticsTlv.
local handler_statistics = {
  fields = {
    [0x0001] = {
      field = field_bytes("cacipc.statistics.statistics_info", "Statistics Information"),
      handle = handle_statistics
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x08 and msg_id == 0x04)
  end,
  name = "CStatisticsTlv"
}

-- CTerminateTlv message.
local handler_terminate = {
  fields = {
    [0x0001] = {
      field = field_uint16("cacipc.terminate.reason_code", "Reason Code"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_uint32("cacipc.terminate.delay_limit", "Delay Limit"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x03 and msg_id == 0x08)
  end,
  name = "CTerminateTlv"
}

-- CUserMessageTlv message.
local handler_user_message = {
  fields = {
    [0x0001] = {
      field = field_uint16("cacipc.usermessage.message_type", "Message Type"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_string("cacipc.usermessage.message_text", "Message Text"),
      handle = handle_string8
    },
    [0x0003] = {
      field = field_string("cacipc.usermessage.message_arg", "Message Argument"),
      handle = handle_string8
    },
    [0x0004] = {
      field = field_uint16("cacipc.usermessage.argument_count", "Argument Count"),
      handle = handle_numeric
    },
    [0x0005] = {
      field = field_string("cacipc.usermessage.message_w", "Message W"),
      handle = handle_string8
    },
    [0x0006] = {
      field = field_uint16("cacipc.usermessage.message", "Message W"),
      handle = handle_numeric
    },
    [0x0007] = {
      field = field_uint16("cacipc.usermessage.message_count", "Message Count"),
      handle = handle_numeric
    },
    [0x0008] = {
      field = field_uint16("cacipc.usermessage.progress_percentage", "Progress Percentage"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x03 and msg_id == 0x05)
  end,
  name = "CUserMessageTlv"
}

-- NotifyAgentTlv message.
local handler_notify_agent = {
  fields = {
    [0x0002] = {
      field = field_string("cacipc.notify_agent.scep_host_url", "SCEP Host URL"),
      handle = handle_string16
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x07 and msg_id == 0x1f)
  end,
  name = "NotifyAgentTlv"
}

-- SCEPTlv message.
local handler_sceptlv = {
  fields = {
    [0x0001] = {
      field = field_uint16("cacipc.scep.message_type", "Message Type"),
      handle = handle_numeric
    },
    [0x0002] = {
      field = field_uint32("cacipc.scep.message_status", "Message Status"),
      handle = handle_numeric
    },
    [0x0003] = {
      field = field_uint16("cacipc.scep.info_request_type", "Information Request Type"),
      handle = handle_numeric
    },
    [0x0004] = {
      field = field_string("cacipc.scep.profile_name", "Profile Name"),
      handle = handle_string16
    },
    [0x0005] = {
      field = field_string("cacipc.scep.sg_host", "Security Gateway Host"),
      handle = handle_string16
    },
    [0x0006] = {
      field = field_uint16("cacipc.scep.notification_id", "Notification Identifier"),
      handle = handle_numeric
    },
    [0x0007] = {
      field = field_bytes("cacipc.scep.dist_name", "Dist Name"),
      handle = handle_buffer
    },
    [0x0008] = {
      field = field_string("cacipc.scep.ca_pass", "Certificate Authority Password"),
      handle = handle_string16
    },
    [0x0009] = {
      field = field_bytes("cacipc.scep.p12_data", "P12 Data"),
      handle = handle_buffer
    },
    [0x000a] = {
      field = field_string("cacipc.scep.p12_cookie", "P12 Cookie"),
      handle = handle_string16
    },
    [0x000b] = {
      field = field_string("cacipc.scep.cert_thumbprint", "Certificate Thumbprint"),
      handle = handle_string16
    },
    [0x000c] = {
      field = field_int64("cacipc.scep.cert_expiry", "Certificate Expiry"),
      handle = handle_numeric
    },
    [0x000d] = {
      field = field_int32("cacipc.scep.cert_access_control", "Certificate Access Control"),
      handle = handle_numeric
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x1b)
  end,
  name = "SCEPTlv"
}

-- UserAuthenticationTlv message.
local handler_user_authentication = {
  fields = {
    [0x0000] = {
      field = field_uint16("cacipc.userauthentication.user_auth_type", "User Authentication Type"),
      handle = handle_numeric
    },
    [0x0001] = {
      field = field_string("cacipc.userauthentication.agg_auth_message", "Aggregated Authentication Message"),
      handle = handle_string8
    },
    [0x0002] = {
      field = field_string("cacipc.userauthentication.credentials_message", "Credentials Message"),
      handle = handle_string16
    },
    [0x0003] = {
      field = field_string("cacipc.userauthentication.credentials_identity", "Credentials Identity"),
      handle = handle_string16
    },
    [0x0004] = {
      field = field_string("cacipc.userauthentication.credentials_verify_password", "Credentials Verify Password"),
      handle = handle_string16
    },
    [0x0005] = {
      field = field_string("cacipc.userauthentication.credentials_password", "Credentials Password"),
      handle = handle_string16
    },
    [0x0007] = {
      field = field_uint32("cacipc.userauthentication.cert_store_type", "Certificate Store Type"),
      handle = handle_numeric
    },
    [0x0008] = {
      field = field_uint32("cacipc.userauthentication.hash_alg", "Hash Algorithm"),
      handle = handle_numeric
    },
    [0x0009] = {
      field = field_bytes("cacipc.userauthentication.hash_data", "Hash Data"),
      handle = handle_buffer
    },
    [0x000a] = {
      field = field_string("cacipc.userauthentication.auth_token", "Authentication Token"),
      handle = handle_string16
    },
    [0x000b] = {
      field = field_string("cacipc.userauthentication.auth_id", "Authentication Identifier"),
      handle = handle_string16
    },
    [0x000c] = {
      field = field_bytes("cacipc.userauthentication.auth_data", "Authentication Data"),
      handle = handle_buffer
    },
    [0x000d] = {
      field = field_string("cacipc.userauthentication.profile_uri", "Profile URI"),
      handle = handle_string16
    },
    [0x000e] = {
      field = field_string("cacipc.userauthentication.profile_hash", "Profile Hash"),
      handle = handle_string16
    },
    [0x000f] = {
      field = field_bytes("cacipc.userauthentication.cert_der", "Certificate DER"),
      handle = handle_buffer
    },
    [0x0011] = {
      field = field_uint32("cacipc.userauthentication.status_code", "Status Code"),
      handle = handle_numeric
    },
    [0x0012] = {
      field = field_bool("cacipc.userauthentication.user_accepted_banner_result", "User Accepted Banner Result"),
      handle = handle_boolean
    },
    [0x0013] = {
      field = field_string("cacipc.userauthentication.primary_sg_ip_address", "Primary Security Gateway Address"),
      handle = handle_string16
    },
    [0x0014] = {
      field = field_string("cacipc.userauthentication.secondary_sg_ip_address", "Secondary Security Gateway Address"),
      handle = handle_string16
    },
    [0x0015] = {
      field = field_string("cacipc.userauthentication.cert_serrver_address", "Certificate Server Address"),
      handle = handle_string16
    },
    [0x0016] = {
      field = field_bytes("cacipc.userauthentication.certificate_info", "Certificate Information"),
      handle = handle_certificate
    },
    [0x0017] = {
      field = field_string("cacipc.userauthentication.banner", "Banner"),
      handle = handle_string16
    },
    [0x0018] = {
      field = field_uint16("cacipc.userauthentication.cert_type", "Certificate Type"),
      handle = handle_numeric
    },
    [0x0019] = {
      field = field_bytes("cacipc.userauthentication.agg_certificate_info", "Aggregated Certificate Information"),
      handle = handle_certificate
    },
  },
  is_supported = function (msg_type, msg_id)
    return (msg_type == 0x0c and msg_id == 0x18)
  end,
  name = "UserAuthenticationTlv"
}

-- Handlers for all the supported messages.
local handlers = {
  handler_acknowledge, handler_api_command, handler_certificate_auth, handler_certificate_info, handler_connect_failure,
  handler_connect_ifc_data, handler_dnldr_args, handler_ipcclosing, handler_keyexchange, handler_launchclientapp,
  handler_local_lan, handler_messagetypebitmap, handler_notify_agent_pre_tunnel, handler_preference_update,
  handler_proxy_authentication, handler_redirect, handler_request_dnldr_args, handler_session_command,
  handler_session_info, handler_start_parameters, handler_state, handler_statistics, handler_terminate,
  handler_user_message, handler_notify_agent, handler_sceptlv, handler_user_authentication
}

-- Create new instance of the protocol.
local cacipc_proto = Proto.new("CACIPC", "Cisco AnyConnect IPC Protocol")

-- Register the protocol's base fields.
cacipc_proto.fields = {
  -- Header fields.
  field_id_tag, field_header_length, field_data_length, field_ipc_response_cb, field_msg_user_context,
  field_req_msg_id, field_ret_ipc_index, field_message_type, field_message_id, field_mesage_class,
  -- TLV entry fields.
  field_type, field_length, field_value,
  -- Statistic entry fields.
  field_stat_entry, field_stat_type, field_stat_unknown, field_stat_value,
}

-- Register the various IPC messages specific fields to the protocol.
for _, msg_handler in pairs(handlers) do
  for _, msg_field in pairs(msg_handler.fields) do
    table.insert(cacipc_proto.fields, msg_field.field)
  end
end

-- Register the expert fields.
cacipc_proto.experts = {
  ef_invalid_hdr_len, ef_invalid_data_len, ef_invalid_tlv_len, ef_unsupported_msg, ef_unsupported_tlv
}

-- Validate that a packet is a CAC IPC packet. The packet is considered an CAC IPC message if the identifier tag and
-- minimum length (the header length) is meet.
local function validate(tvbuf)
  -- Get the reported (not captured) length of packet data to end of the tvbuf.
  local pkt_len = tvbuf:reported_length_remaining()

  -- The message needs to be at least the header length long.
  if pkt_len < CACIPC_HDR_LEN then
    return CACIPC_ERR.INSUFICIENT_DATA
  end

  -- The first 4 bytes of the packet are the message identifier tag, which is always "CSCO".
  if tvbuf(0, 4):le_uint() ~= 0x4353434f then
    return CACIPC_ERR.INVALID_ID_TAG
  end
  
  -- Get the header length as reported on the message and ensure it is 26 bytes.
  local hdr_len = tvbuf(4, 2):le_uint()

  if hdr_len ~= CACIPC_HDR_LEN then
    return CACIPC_ERR.HEADER_LEN
  end

  -- Calculate the complete message length as specified by the header fields.
  local total_len = hdr_len + tvbuf(6, 2):le_uint()

  -- The actual length of the message/packet needs to be the same as the calculated total length.
  if total_len ~= pkt_len then
    return CACIPC_ERR.DATA_LEN
  end

  return CACIPC_ERR.NONE
end


-- Wireshark goes brrrrrr.
function cacipc_proto.dissector(tvbuf, pktinfo, root)
  -- Used to keep how many bytes were dissected.
  local dissection_res = 0

  -- Validate the packet and report any errors in the data.
  local validation_res = validate(tvbuf)

  if validation_res ~= CACIPC_ERR.NONE then
    -- Check that the packet matches the minimum requirements for it to be considered a CAC IPC protocol: the identifier
    -- and the packet length being 26 or more bytes.
    if validation_res ~= CACIPC_ERR.INSUFICIENT_DATA and validation_res ~= CACIPC_ERR.INVALID_ID_TAG then
      -- Mark the protocol as CACIPC as the minimum requirements have still been meet when called from the TCP port
      -- match as the heuristic function fails if there is any validation error.
      pktinfo.columns.protocol = cacipc_proto.name

      -- Add the protocol to the dissection display tree.
      local proto_tree = root:add(cacipc_proto, tvbuf)

      -- Add the validation error.
      if validation_res == CACIPC_ERR.HEADER_LEN then
        proto_tree:add_tvb_expert_info(ef_invalid_hdr_len, tvbuf(4, 2))
      end
      if validation_res == CACIPC_ERR.DATA_LEN then
        proto_tree:add_tvb_expert_info(ef_invalid_data_len, tvbuf(6, 2))
      end
    end
  else
    -- Mark the protocol as CACIPC as the minimum requirements for it to be considered a CAC IPC protocol packet is the
    -- identifier and the packet length being 26 or more bytes.
    pktinfo.columns.protocol = cacipc_proto.name

    -- Get the packet data.
    local pkt_data = tvbuf:range(0, pktlen)

    -- Start by adding the protocol to the dissection display tree.
    local proto_tree = root:add(cacipc_proto, pkt_data)

    -- Get the reported header length.
    local hdr_len = pkt_data(4, 2)

    -- Get the reported data length.
    local body_len = pkt_data(6, 2)

    --- Add the header information to the tree.
    local hdr_tree = proto_tree:add(cacipc_proto, pkt_data(0, 26), "Header")
    hdr_tree:add_packet_field(field_id_tag, pkt_data(0, 4), ENC_LITTLE_ENDIAN)
    hdr_tree:add_packet_field(field_header_length, hdr_len, ENC_LITTLE_ENDIAN)
    hdr_tree:add_packet_field(field_data_length, body_len, ENC_LITTLE_ENDIAN)
    hdr_tree:add_packet_field(field_ipc_response_cb, pkt_data(8, 4), ENC_LITTLE_ENDIAN)
    hdr_tree:add_packet_field(field_msg_user_context, pkt_data(12, 4), ENC_LITTLE_ENDIAN)
    hdr_tree:add_packet_field(field_req_msg_id, pkt_data(16, 4), ENC_LITTLE_ENDIAN)
    hdr_tree:add_packet_field(field_ret_ipc_index, pkt_data(20, 4), ENC_LITTLE_ENDIAN)

    local msg_type = pkt_data(24, 1)
    hdr_tree:add_packet_field(field_message_type, msg_type, ENC_LITTLE_ENDIAN)

    local msg_id = pkt_data(25, 1)
    hdr_tree:add_packet_field(field_message_id, msg_id, ENC_LITTLE_ENDIAN)

    local hdr_class_tree = nil

    -- Dissected at least the header length
    dissection_res = hdr_len:le_uint()

    for _, handler in pairs(handlers) do
      if handler.is_supported(bit.band(msg_type:uint(), 0x1f), msg_id:uint()) then
        -- Add the message class to the tree, and even if associated with packet data, mark it as generated as it is
        -- created based on two other actual packet fields, message identifier and message type. The name for the class
        -- comes from the C++ class that CAC uses to handle the specific IPC message.
        hdr_class_tree = hdr_tree:add(field_message_class, pkt_data(24, 2), handler.name):set_generated()

        -- If the message has at least 4 bytes (the minimum size for the body to have at least one valid TV entry), then
        -- extract message's body. While the IPC messages use mostly TLV (Type, Length, and Value) entries, there is some
        -- messages that contain TV (Type, and Value) entries. Used for example, for some boolean values.
        if body_len:le_uint() >= 4 then
          -- Slice the buffer and extract the message's body.
          local body_data = pkt_data(hdr_len:le_uint(), body_len:le_uint())

          -- Start to add the messages body extracted data.
          local body_tree = proto_tree:add(cacipc_proto, body_data, "Body")

          -- Handle the TLVs contained in the message.
          dissection_res = dissection_res + handle_sequence(body_tree, handler, body_data)
        end

        -- Exit from the loop, since there is no need to go through all the handlers once one handler is found to
        -- support the message. From what I have seen in CAC's code there is only one class per different message type
        -- and identifier combination.
        break
      end
    end

    -- If the message class wasn't added to the tree, then the message is unsupported.
    if hdr_class_tree == nil then
      proto_tree:add_tvb_expert_info(ef_unsupported_msg, pkt_data(24, 2))
    end
  end

  return dissection_res
end

-- Making sure the protocol dissection is invoked for the specific CAC IPC TCP port, so get the TCP dissector table and
-- add the protocol to it.
local tcp_port_table = DissectorTable.get("tcp.port")
tcp_port_table:add(CACIPC_PROTO_PORT, cacipc_proto)


-- Heuristic function for detecting CAC IPC protocol when not on the default TCP port. This is very unlikely to happen,
-- was done more as an exercise to learn how to do it than anything else.
local function heuristic_cacipc(tvbuf, pktinfo, root)
  -- Check if the packet matches the expectations. For the heuristic to accept the packet as a CAC IPC there cannot be
  -- any validation errors. This is not the case in the dissector that is called from a match on the TCP port.
  if validate(tvbuf) ~= CACIPC_ERR.NONE then
    return false
  end

  -- Call the dissector.
  cacipc_proto.dissector:call(tvbuf, pktinfo, root)

  -- Since CAC IPC goes over a transport protocol, we can set the conversation to make it sticky for the dissector, so
  -- that all future packets to/from the same address:port pair will just call our dissector function directly instead
  -- of this heuristic function.
  pktinfo.conversation = cacipc_proto

  return true
end

-- Register the heuristic dissector into the TCP heuristic list.
cacipc_proto:register_heuristic("tcp", heuristic_cacipc)
