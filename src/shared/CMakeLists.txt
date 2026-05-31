add_library(shared STATIC
  Paths.cpp Paths.h
  LocalJsonClient.cpp LocalJsonClient.h
  LocalJsonServer.cpp LocalJsonServer.h
  UniqueApplication.h
  ${CMAKE_BINARY_DIR}/src/core/Version.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/Names.cpp Names.h
)

std_target_properties(shared)
target_include_directories(shared PUBLIC ${PROJECT_SOURCE_DIR}/src)

clang_tidy(shared)
