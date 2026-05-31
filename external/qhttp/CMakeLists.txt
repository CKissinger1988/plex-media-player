aux_source_directory(src HTTP_SRC)

set(CMAKE_AUTOMOC ON)

add_library(qhttp STATIC ${HTTP_SRC} 3rdparty/http-parser/http_parser.c)
target_compile_definitions(qhttp PUBLIC QHTTP_EXPORT)
target_include_directories(qhttp PUBLIC src 3rdparty)
std_target_properties(qhttp)
