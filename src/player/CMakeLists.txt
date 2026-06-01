add_library(player STATIC
  PlayerComponent.cpp PlayerComponent.h
  PlayerQuickItem.cpp PlayerQuickItem.h
  CodecsComponent.cpp CodecsComponent.h
  OpenGLDetect.cpp OpenGLDetect.h
  QtHelper.h
  AudioDeviceManager.cpp AudioDeviceManager.h
  CodecManager.cpp CodecManager.h
  SubtitleManager.cpp SubtitleManager.h
)

std_target_properties(player)
target_include_directories(player PUBLIC .)
clang_tidy(player)
