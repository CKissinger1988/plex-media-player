add_library(power STATIC
  PowerComponent.h PowerComponent.cpp
)

if(APPLE)
  target_sources(power PRIVATE PowerComponentMac.cpp PowerComponentMac.h)
endif()

if(LINUX_X11POWER)
  target_sources(power PRIVATE PowerComponentX11.cpp PowerComponentX11.h)
endif()

if(LINUX_DBUS)
  target_sources(power PRIVATE PowerComponentDBus.cpp PowerComponentDBus.h)
endif()

if(WIN32)
  target_sources(power PRIVATE PowerComponentWin.cpp PowerComponentWin.h)
endif()

target_include_directories(power PUBLIC .)
std_target_properties(power)
clang_tidy(power)
