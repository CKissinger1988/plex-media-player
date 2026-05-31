add_library(ai STATIC
  AIComponent.cpp AIComponent.h
  MediaScraper.cpp MediaScraper.h
)

target_include_directories(ai PUBLIC .)
std_target_properties(ai)
clang_tidy(ai)
