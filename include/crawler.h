#ifndef CRAWLER_H
#define CRAWLER_H

#include <deque>
#include <memory>
#include <string>
#include <unordered_set>

#include "gumbo.h"
#include <skyr/url.hpp>

#include "curl-http.h"
#include "http.h"

namespace kraal {

class Crawler {
public:
  using UrlType = std::string;
  Crawler() = default;
  Crawler(std::string root_url,
          std::unique_ptr<Http> http = std::make_unique<CurlHttp>())
      : root_url_(root_url), http_(std::move(http)) {
    push_url(root_url);
  }

  void crawl();

  inline int url_count() const { return urls_.size(); }
  void push_url(UrlType url) { urls_.push_back(url); };
  void pop_url() { urls_.pop_front(); };

  bool has_crawled_url(UrlType);

private:
  skyr::url root_url_;
  std::deque<UrlType> urls_;
  std::unordered_set<UrlType> seen_urls_;
  std::unique_ptr<Http> http_;
};

} // namespace kraal
#endif /* CRAWLER_H */
