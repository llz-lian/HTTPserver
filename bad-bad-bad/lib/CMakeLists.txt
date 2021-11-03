cmake_minimum_required(VERSION 3.16)

aux_source_directory(./src SRC_LIST)

include_directories(
    /usr/include/mysql
    ./include
)

link_directories(/usr/lib/x86_64-linux-gnu)

add_library(sql_static STATIC "./src/db.cpp")

target_link_libraries (sql_static /usr/lib/x86_64-linux-gnu/libmysqlclient.so)


SET_TARGET_PROPERTIES (sql_static PROPERTIES OUTPUT_NAME "sql1")
set(
    LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib
)