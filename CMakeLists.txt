cmake_minimum_required(VERSION 3.10)

project(mon_projet C)

add_executable(mon_projet main.c commons.c IP.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
