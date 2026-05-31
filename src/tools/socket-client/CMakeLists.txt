add_executable(socket-client
  SocketClient.cpp
)

target_link_libraries(socket-client PRIVATE Qt6::Network Qt6::Core qslog shared)
target_include_directories(socket-client PRIVATE ${PROJECT_SOURCE_DIR}/src)
std_target_properties(socket-client)
clang_tidy(socket-client)
