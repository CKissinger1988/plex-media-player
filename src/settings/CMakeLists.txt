add_library(settings STATIC
  AudioSettingsController.cpp AudioSettingsController.h
  SettingsComponent.cpp SettingsComponent.h
  SettingsSection.cpp SettingsSection.h
  SettingsValue.h
)

target_include_directories(settings PUBLIC .)
std_target_properties(settings)
clang_tidy(settings)