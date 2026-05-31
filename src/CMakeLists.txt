set(CMAKE_AUTOMOC ON)

add_definitions(-DPREFIX="${CMAKE_INSTALL_PREFIX}")

add_subdirectory(shared)
add_subdirectory(core)
add_subdirectory(display)
add_subdirectory(player)
add_subdirectory(utils)
add_subdirectory(server)
add_subdirectory(ui)
add_subdirectory(input)
add_subdirectory(system)
add_subdirectory(breakpad)
add_subdirectory(settings)
add_subdirectory(power)
add_subdirectory(remote)
add_subdirectory(ai)
add_subdirectory(tools)

file(GLOB_RECURSE RESOURCE_FILES ${CMAKE_SOURCE_DIR}/resources/*)

# generate resources.qrc from directory tree listings
add_custom_command(OUTPUT resources.qrc
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/build-qt-resources.py
          ${CMAKE_CURRENT_BINARY_DIR}/resources.qrc
          /=${CMAKE_SOURCE_DIR}/resources/
          ui/webview.qml=${CMAKE_SOURCE_DIR}/src/ui/webview.qml
  COMMENT "Creating resources.qrc"
  DEPENDS ${CMAKE_SOURCE_DIR}/scripts/build-qt-resources.py
    ${RESOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/src/ui/webview.qml
)
set_source_files_properties(resources.qrc PROPERTIES GENERATED TRUE)
add_custom_command(OUTPUT qrc_resources.cpp
  COMMAND ${Qt6Core_RCC_EXECUTABLE} -name resources -o qrc_resources.cpp resources.qrc
  DEPENDS resources.qrc ${CMAKE_SOURCE_DIR}/src/ui/webview.qml ${RESOURCE_FILES}
)
set_source_files_properties(qrc_resources.cpp PROPERTIES GENERATED TRUE)

list(APPEND RESOURCE_FILES qrc_resources.cpp)

set(MACOSX_BUNDLE_ICON_FILE Plex.icns)
set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION_STRING})
set(MACOSX_BUNDLE_BUNDLE_NAME "SpartanAI-Media")
set(MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION_STRING})
set(MACOSX_BUNDLE_GUI_IDENTIFIER tv.plex.player)

# [Placeholder for platform specific logic to remain as is]

if(WIN32)
  list(APPEND RESOURCE_FILES ${CMAKE_SOURCE_DIR}/bundle/win/iconres.rc)
endif()

add_executable(${MAIN_TARGET} WIN32 MACOSX_BUNDLE main.cpp ${RESOURCE_FILES})
std_target_properties(${MAIN_TARGET})
set_target_properties(${MAIN_TARGET} PROPERTIES
  MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/bundle/osx/Info.plist.in
  INSTALL_RPATH "${QTROOT}/lib"
  OUTPUT_NAME ${MAIN_NAME}
)
copy_resources(${MAIN_TARGET})
clang_tidy(${MAIN_TARGET})

# [Placeholder for dependencies logic to remain as is]

target_link_libraries(${MAIN_TARGET} PRIVATE
  ai
  breakpad
  core
  display
  input
  player
  power
  remote
  server
  settings
  shared
  system
  ui
  utils
  qhttp
  qslog
  ${MPV_LIBRARY}
  ${OPENGL_LIBS}
  ${QT5_LIBRARIES}
  ${OS_LIBS}
  ${EXTRA_LIBS}
  ${X11_LIBRARIES}
  ${X11_Xrandr_LIB}
  ${BREAKPAD_LIBRARIES}
  ${ICU_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${RPI_LIBS}
  ${MINIZIP_LIBS}
)

install(TARGETS ${MAIN_TARGET} DESTINATION ${INSTALL_BIN_DIR})
