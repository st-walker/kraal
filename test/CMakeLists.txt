
add_executable(
    unit_tests
    CrawlerTest.cpp
    LinkExtractorTest.cpp
    url-test.cpp
    )

target_link_libraries(
    unit_tests
    gtest
    gmock_main
    kraal
    )

include(GoogleTest)
gtest_discover_tests(unit_tests)
