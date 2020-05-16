#include <iostream>
#include <iterator>
#include <queue>
#include <string>

#include "gumbo.h"

#include "crawler.h"
#include "link-extractor.h"
#include "response.h"

namespace kraal {

void Crawler::crawl() {
  auto url = urls_.front();
  if (has_crawled_url(url))
    return;
  auto response = http_->get(url);
  urls_.pop_front();

  LinkExtractor extractor{response.body};
  extractor.extract(std::back_inserter(urls_));

  seen_urls_.insert(url);
}

bool Crawler::has_crawled_url(Crawler::UrlType url) {
  return seen_urls_.find(url) != seen_urls_.end();
}

} // namespace kraal
