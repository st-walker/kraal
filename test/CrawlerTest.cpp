#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "crawler.h"
#include "http.h"

using namespace testing;
using namespace kraal;

class MockHttp : public Http {
public:
  MOCK_METHOD(Response, get, (std::string const &), (const override));
};

class ACrawler : public Test {
public:
  static const std::string valid_url;
  Crawler crawler;
};

const std::string ACrawler::valid_url("https://www.example.com/");

TEST_F(ACrawler, HasNoURLsOnDefaultConstruction) {
  ASSERT_THAT(0, Eq(crawler.url_count()));
}

TEST_F(ACrawler, HasOneURLIfInstantiatedWithOne) {
  crawler = Crawler(valid_url);
  ASSERT_THAT(1, Eq(crawler.url_count()));
}

TEST_F(ACrawler, HasOneURLAfterAddingOne) {
  crawler.push_url(valid_url);

  ASSERT_THAT(crawler.url_count(), Eq(1));
};

TEST_F(ACrawler, HasNoURLsAfterRemovingOne) {
  crawler.push_url(valid_url);
  crawler.pop_url();

  ASSERT_THAT(crawler.url_count(), Eq(0));
};

TEST_F(ACrawler, MakesHTTPRequestToPage) {
  auto mock_http = std::make_unique<MockHttp>();
  EXPECT_CALL(*mock_http, get(valid_url)).Times(1);
  crawler = Crawler(valid_url, std::move(mock_http));

  crawler.push_url(valid_url);
  crawler.crawl();
}

TEST_F(ACrawler, RemovesURLAfterGettingIt) {
  auto mock_http = std::make_unique<NiceMock<MockHttp>>();
  crawler = Crawler(valid_url, std::move(mock_http));

  crawler.crawl();

  ASSERT_THAT(crawler.url_count(), Eq(0));
}

TEST_F(ACrawler, ReturnsURLAsCrawledAfterCrawlingIt) {
  auto mock_http = std::make_unique<NiceMock<MockHttp>>();
  crawler = Crawler(valid_url, std::move(mock_http));

  crawler.push_url(valid_url);
  crawler.crawl();

  ASSERT_TRUE(crawler.has_crawled_url(valid_url));
}

TEST_F(ACrawler, ReturnsURLAsNotCrawledIfNotCrawled) {
  auto mock_http = std::make_unique<NiceMock<MockHttp>>();
  crawler = Crawler(valid_url, std::move(mock_http));

  ASSERT_FALSE(crawler.has_crawled_url(valid_url));
}

TEST_F(ACrawler, DoesntCrawlSameURLTwice) {
  auto mock_http = std::make_unique<MockHttp>();
  EXPECT_CALL(*mock_http, get(valid_url)).Times(1);
  crawler = Crawler(valid_url, std::move(mock_http));

  crawler.crawl();
  crawler.push_url(valid_url);
  crawler.crawl();
}
