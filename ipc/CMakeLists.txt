# Add source to this project's library.
add_library (ipc STATIC "ccertificateinfotlv.cpp" "ccertificateinfotlv.h" "caknowledge.cpp" "caknowledge.h" "capicommandtlv.cpp" "capicommandtlv.h" "cconnectfailuretlv.cpp" "cconnectfailuretlv.h" "cdnldrargstlv.cpp" "cdnldrargstlv.h" "cipcclosingtlv.cpp" "cipcclosingtlv.h" "clocallan.cpp" "clocallan.h" "cmessagetypebitmaptlv.cpp" "cmessagetypebitmaptlv.h" "credirecttlv.cpp" "credirecttlv.h" "csessioninfotlv.cpp" "csessioninfotlv.h" "cstatisticstlv.cpp" "cstatisticstlv.h" "cterminatetlv.cpp" "cterminatetlv.h" "cusermessagetlv.cpp" "cusermessagetlv.h" "cextensiblestats.cpp" "cextensiblestats.h" "ccertificateauthtlv.cpp" "ccertificateauthtlv.h" "crequestdnldrargstlv.cpp" "crequestdnldrargstlv.h" "cconnectifcdatatlv.cpp" "cconnectifcdatatlv.h"   "ckeyexchangetlv.cpp" "ckeyexchangetlv.h" "claunchclientapptlv.cpp" "claunchclienttapptlv.h" "cnotifyagentpretunneltlv.cpp" "cnotifyagentpretunneltlv.h" "csessioncommandtlv.cpp" "csessioncommandtlv.h" "cstartparameters.cpp" "cstartparameters.h" "cstatetlv.cpp" "cstatetlv.h" "cpreferenceupdatetlv.cpp" "cpreferenceupdatetlv.h" "notifyagenttlv.cpp" "notifyagenttlv.h" "cproxyauthentication.cpp" "cproxyauthentication.h" "sceptlv.cpp" "sceptlv.h" "userauthenticationtlv.cpp" "userauthenticationtlv.h")

target_include_directories(ipc PUBLIC "../base")
target_link_libraries(ipc PUBLIC base)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ipc PROPERTY CXX_STANDARD 20)
endif()
