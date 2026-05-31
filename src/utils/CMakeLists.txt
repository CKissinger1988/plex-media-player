
add_library(utils STATIC
  CachedRegexMatcher.cpp CachedRegexMatcher.h
  PlatformUtils.cpp PlatformUtils.h
  HelperLauncher.h HelperLauncher.cpp
  HelperLaunchd.h HelperLaunchd.cpp
  Utils.cpp Utils.h
  Log.cpp Log.h
)

if(APPLE)
  target_sources(utils PRIVATE osx/PlatformUtilsOSX.cpp osx/PlatformUtilsOSX.h)
endif()

if(WIN32)
  target_sources(utils PRIVATE win/PlatformUtilsWin.cpp win/PlatformUtilsWin.h)
endif()

target_include_directories(utils PUBLIC .)
std_target_properties(utils)
clang_tidy(utils)
