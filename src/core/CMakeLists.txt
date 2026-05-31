add_library(core STATIC
  ComponentManager.cpp ComponentManager.h
  Globals.cpp Globals.h
  Version.h
)

if(UNIX)
  target_sources(core PRIVATE SignalManager.cpp SignalManager.h)
endif()

std_target_properties(core)
target_include_directories(core PUBLIC .)
clang_tidy(core)
