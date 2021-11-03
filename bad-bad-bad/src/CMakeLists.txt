cmake_minimum_required(VERSION 3.16)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

find_package (Threads)

INCLUDE_DIRECTORIES(
../include
../include/aux
../include/server
../include/log
)

link_directories(../lib/libsql1.a)

ADD_EXECUTABLE(mywebserver ${SRC_LIST})

target_link_libraries (${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libmysqlclient.so)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

SET(
    EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin
)