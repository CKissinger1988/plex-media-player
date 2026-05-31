add_executable(${HELPER_TARGET} WIN32
  HelperMain.cpp
  HelperSocket.cpp
  HelperSocket.h
)

if(ENABLE_CRASHDUMP)
  target_sources(${HELPER_TARGET} PRIVATE CrashUploader.cpp CrashUploader.h)
  target_compile_definitions(${HELPER_TARGET} PRIVATE ENABLE_CRASHDUMP CRASHDUMP_SECRET="${CRASHDUMP_SECRET}")
endif()

target_link_libraries(${HELPER_TARGET} PRIVATE Qt6::Core Qt6::Network qslog shared)
target_include_directories(${HELPER_TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/src)

std_target_properties(${HELPER_TARGET})
set_target_properties(${HELPER_TARGET} PROPERTIES
  INSTALL_RPATH "${QTROOT}/lib"
  OUTPUT_NAME ${HELPER_NAME}
)

if(APPLE)
  set(PLATFORM_RESOURCE_SUFFIX /../Resources)
endif()

add_custom_command(
  TARGET ${HELPER_TARGET}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${HELPER_TARGET}> $<TARGET_FILE_DIR:${MAIN_TARGET}>${PLATFORM_RESOURCE_SUFFIX}
)

if(NOT APPLE)
  install(TARGETS ${HELPER_TARGET} DESTINATION ${INSTALL_BIN_DIR})
endif()

clang_tidy(${HELPER_TARGET})
