set(HELPER_TARGET SAMHelper)
set(MAIN_TARGET SpartanAIMedia)

# Name of the output binary, defaults are only used on Linux
set(HELPER_NAME samhelper)
set(MAIN_NAME plexmediaplayer)

if(APPLE)
  set(HELPER_NAME "SAM Helper")
  set(MAIN_NAME "SpartanAI-Media")
elseif(WIN32)
  set(HELPER_NAME "SAMHelper")
  set(MAIN_NAME "SpartanAIMedia")
endif(APPLE)

configure_file(src/shared/Names.cpp.in src/shared/Names.cpp @ONLY)