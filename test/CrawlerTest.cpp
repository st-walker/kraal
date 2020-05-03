#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "crawler.h"

using namespace testing;
using namespace kraal;

class ACrawler: public Test {
public:
  static const std::string url;
  Crawler crawler;
};

const std::string ACrawler::url("something");

TEST_F(ACrawler, CrawlerHasNoURLsOnDefaultConstruction) {
  ASSERT_THAT(0, Eq(crawler.url_count()));
}

TEST_F(ACrawler, CrawlerHasOneURLAfterAddingOne) {
  crawler.add_url(url);
  ASSERT_THAT(crawler.url_count(), Eq(1));
};

TEST_F(ACrawler, CrawlerHasNoURLsAfterRemovingOne) {
  crawler.add_url(url);
  crawler.pop_url();
  ASSERT_THAT(crawler.url_count(), Eq(0));
};

