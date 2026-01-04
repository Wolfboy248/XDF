cmake_minimum_required(VERSION 3.28)

set(LIB_NAME XDF)

file(GLOB_RECURSE XDF_SOURCES CONFIGURE_DEPENDS
  src/*.cpp
)

add_library(${LIB_NAME} ${XDF_SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

