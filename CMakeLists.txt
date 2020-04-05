cmake_minimum_required(VERSION 3.16.2)

option(crawler_BUILD_TESTS "Build the crawl tests." ON)


project(paracrawler
  VERSION 0.1
  DESCRIPTION "A parallel web crawler"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# CURL and gumbo
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)
find_package(CURL REQUIRED)

# find_package(tl-expected REQUIRED)

include(cmake/FindSkyr.cmake)


# Library
add_library(para STATIC
  src/page-getter.cpp
  src/crawler.cpp
  )

target_include_directories(para
  PUBLIC
  "./include"
  "${GUMBO_INCLUDE_DIRS}"
  "${CURL_INCLUDE_DIRS}"
  )

target_link_libraries(para
  PRIVATE # PUBLIC
  "${GUMBO_LDFLAGS}"
  "${CURL_LIBRARIES}"
  )


# Executable
add_executable(parax paracrawler.cpp)

target_link_libraries(parax PRIVATE para)

if (crawler_BUILD_TESTS)
  message(STATUS "Configuring tests")
  enable_testing()
  add_subdirectory(test)
endif()
