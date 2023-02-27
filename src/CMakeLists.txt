cmake_minimum_required(VERSION 3.10)

project(ip_catalog C)

add_executable(ip_catalog main.c commons.c IP.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
