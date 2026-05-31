add_library(input STATIC
  InputComponent.cpp InputComponent.h
  InputMapping.cpp InputMapping.h
  InputKeyboard.h
  InputSocket.h
  InputSocket.cpp
  InputRoku.cpp
  InputRoku.h
)

if(APPLE)
  target_sources(input PRIVATE apple/InputApple.cpp apple/InputApple.h)
endif()

if(SDL2_FOUND)
  target_sources(input PRIVATE InputSDL.cpp InputSDL.h)
endif()

if(ENABLE_LIRC)
  target_sources(input PRIVATE InputLIRC.cpp InputLIRC.h)
endif()

if(CEC_FOUND)
  target_sources(input PRIVATE InputCEC.cpp InputCEC.h)
endif()

target_include_directories(input PUBLIC .)
std_target_properties(input)
clang_tidy(input)

