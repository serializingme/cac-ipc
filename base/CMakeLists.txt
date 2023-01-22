# Add source to this project's library.
add_library (base STATIC "common.cpp" "common.h" "socket.cpp" "socket.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET base PROPERTY CXX_STANDARD 20)
endif()
