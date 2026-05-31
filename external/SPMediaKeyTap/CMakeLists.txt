
add_library(spmediakeytap STATIC
  SPMediaKeyTap.h SPMediaKeyTap.m
  SPInvocationGrabbing/NSObject+SPInvocationGrabbing.m
  SPInvocationGrabbing/NSObject+SPInvocationGrabbing.h
)
std_target_properties(spmediakeytap)
target_compile_options(spmediakeytap PRIVATE -Wno-deprecated-declarations)
target_include_directories(spmediakeytap PUBLIC .)