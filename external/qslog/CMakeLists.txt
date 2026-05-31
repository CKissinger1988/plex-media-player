set(CMAKE_AUTOMOC ON)
aux_source_directory(. QSLOG_SRC)

add_library(qslog STATIC ${QSLOG_SRC})
std_target_properties(qslog)

# Modern target-based include directory configuration
target_include_directories(qslog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
