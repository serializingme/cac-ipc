# Add source to this project's executable.
add_executable (generator "generator.cpp" "generator.h")

target_link_libraries(generator PUBLIC Ws2_32)

target_include_directories(generator PUBLIC "../base")
target_link_libraries(generator PUBLIC base)

target_include_directories(generator PUBLIC "../ipc")
target_link_libraries(generator PUBLIC ipc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET generator PROPERTY CXX_STANDARD 20)
endif()
