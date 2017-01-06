cmake_minimum_required(VERSION 3.5)
project(xredis_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        example/RedisServer.cpp
    src/sds.c
    src/sds.h
    src/sdsalloc.h
        src/RedisServerLib.cpp
        src/RedisServerLib.h)

add_executable(redis_server ${SOURCE_FILES})
target_link_libraries(redis_server event pthread)