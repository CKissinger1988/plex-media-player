add_library(remote STATIC
  GDMManager.cpp GDMManager.h
  RemoteComponent.cpp RemoteComponent.h
  RemoteSubscriber.cpp RemoteSubscriber.h
)

target_include_directories(remote PUBLIC .)
std_target_properties(remote)
clang_tidy(remote)

