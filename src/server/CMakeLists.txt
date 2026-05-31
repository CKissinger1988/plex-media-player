add_library(server STATIC
  HTTPServer.cpp HTTPServer.h
)

target_include_directories(server PUBLIC .)
std_target_properties(server)
clang_tidy(server)