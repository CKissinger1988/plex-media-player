add_library(system STATIC
  SystemComponent.cpp SystemComponent.h
  UpdateManager.cpp UpdateManager.h
  UpdateManagerWin32.cpp UpdateManagerWin32.h
  UpdaterComponent.cpp UpdaterComponent.h
  OEUpdateManager.cpp OEUpdateManager.h
)

if(OPENELEC)
  target_sources(system PRIVATE openelec/OEUpdateManager.cpp openelec/OEUpdateManager.h)
endif()

target_include_directories(system PUBLIC .)
std_target_properties(system)
clang_tidy(system)