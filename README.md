# CAC IPC
## Introduction

This utility allows one to generate the various Cisco AnyConnect (CAC) Inter-Process Communication (IPC) messages. This is useful in the understanding of the IPC protocol as used by CAC and to validate the Wireshark dissector. This utility only supports 32 bit versions as CAC is 32 bits only.

### Base

Static library containing common code used by generator component.

### IPC

Static library containing the various IPC wrapper classes that can be used to generate the various messages. This code is used by generator component.

### Generator

Executable that generates the various messages, it starts a UDP listener at `127.0.0.2:62522`, and then it connects with a UDP client to the the listener and sends the various IPC messages.

### Dissector

The Wireshark dissector, `cacipc.lua`, can be installed in the plugins directory and is ready to use. There is also a sample packet capture (PCAP) called `cacipc.pcapng` that can be used to test the dissector.

## Requirements

To use the IPC message generator, one needs to have CAC installed as the utility makes use of the `vpncommon.dll` library to generate the messages. This DLL (or any other that may be needed) is not distributed in the repository for obvious reasons.

## Build it Yourself

All code is written in C++ and can be compiled in Windows using Visual Studio 2022. The project makes use of CMake so it is conceivable that it can be (cross-)compiled using other tools.

## Licensing

All code is licensed under GNU/GPL version 3.
