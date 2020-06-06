#include <iostream>
#include <iterator>
#include <queue>
#include <string>

#include "crawler.h"
#include "link-extractor.h"
#include "response.h"
#include "url.h"

namespace kraal {

void Crawler::crawl() {
  while (!urls_.empty()) {

    auto page_url = urls_.front();

    if (has_crawled_url(page_url)) {
      urls_.pop_front();
      continue;
    }

    std::cout << "Crawling: " << page_url << "\n";
    auto response = http_->get(page_url);
    if (response.status != 200) {
      std::cout << "BAD STATUS: " << response.status << "\n";
    }
    urls_.pop_front();

    // std::cout << "NEW KRAAL: " << root_url_ << "\n\n\n" << response.body;
    LinkExtractor extractor{response.body, root_url_, page_url};
    extractor.extract(std::back_inserter(urls_));

    seen_urls_.insert(std::string(page_url));
  }
}

bool Crawler::has_crawled_url(Crawler::UrlType url) {
  return seen_urls_.find(url) != seen_urls_.end();
}

} // namespace kraal
