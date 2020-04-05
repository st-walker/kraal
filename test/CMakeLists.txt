
set(SOURCES
  main.cpp
  page-test.cpp)

add_executable(testRunner ${SOURCES})
find_package(GTest REQUIRED)
target_link_libraries(testRunner PRIVATE GTest::GTest)

# add_test(NAME myGTestCases COMMAND myGTestCases)

# gtest_add_tests(
#   TARGET testRunner
#   )

gtest_discover_tests(
  testRunner
  )
