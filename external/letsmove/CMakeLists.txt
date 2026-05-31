set_source_files_properties(PFMoveApplication.m PROPERTIES COMPILE_FLAGS -fno-objc-arc)
add_library(letsmove STATIC PFMoveApplication.m PFMoveApplication.h)
std_target_properties(letsmove)
target_include_directories(letsmove PUBLIC .)
