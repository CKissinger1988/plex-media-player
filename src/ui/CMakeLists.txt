add_library(ui STATIC
  ErrorMessage.cpp ErrorMessage.h
  EventFilter.cpp EventFilter.h
  KonvergoWindow.cpp KonvergoWindow.h
)

target_include_directories(ui PUBLIC .)
std_target_properties(ui)
clang_tidy(ui)
