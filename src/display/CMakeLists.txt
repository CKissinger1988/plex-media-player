add_library(display STATIC
  DisplayComponent.cpp DisplayComponent.h
  DisplayManager.cpp DisplayManager.h
)

if(APPLE)
  target_sources(display PRIVATE osx/Display.mm osx/Display.h)
elseif(BUILD_TARGET STREQUAL "RPI")
  target_sources(display PRIVATE rpi/Display.cpp rpi/Display.h)
elseif(X11XRANDR_FOUND)
  target_sources(display PRIVATE x11/Display.cpp x11/Display.h)
elseif(WIN32)
  target_sources(display PRIVATE win/Display.cpp win/Display.h)
else()
  target_sources(display PRIVATE dummy/Display.cpp dummy/Display.h)
endif()

target_include_directories(display PUBLIC .)
std_target_properties(display)
clang_tidy(display)