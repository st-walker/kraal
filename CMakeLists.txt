cmake_minimum_required(VERSION 3.16.2)

option(kraal_BUILD_TESTS "Build the crawl tests." ON)


project(kraal
  VERSION 0.1
  DESCRIPTION "A parallelised web crawler"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# CURL and gumbo
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)
find_package(CURL REQUIRED)

# find_package(tl-expected REQUIRED)

include(cmake/FindSkyr.cmake)

# Library
add_library(kraal STATIC
  src/crawler.cpp
  src/curl-http.cpp
  src/link-extractor.cpp
  )

target_include_directories(kraal
  PRIVATE
  "${GUMBO_INCLUDE_DIRS}"
  "${CURL_INCLUDE_DIRS}"
  PUBLIC
  "./include"
  "${Skyr_INCLUDE_DIRS}"
  )

target_link_libraries(kraal
  PRIVATE
  "${GUMBO_LDFLAGS}"
  "${CURL_LIBRARIES}"
  PUBLIC
  "${Skyr_LIBRARIES}"
  )


# Executable
add_executable(crawl crawl.cpp)

target_link_libraries(crawl PRIVATE kraal)

if (kraal_BUILD_TESTS)
  message(STATUS "Configuring tests")
  include(cmake/googletest.cmake)
  fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )
  enable_testing()
  add_subdirectory(test)
endif()
