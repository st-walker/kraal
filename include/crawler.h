#ifndef CRAWLER_H
#define CRAWLER_H

#include <deque>
#include <string>
#include <memory>
#include<unordered_set>

#include "gumbo.h"

#include "http.h"
#include "curl-http.h"


namespace kraal {

class Crawler {

protected:
  using UrlType = std::string;
public:
  Crawler(std::string root_url,
          std::unique_ptr<Http> http = std::make_unique<CurlHttp>())
      : root_url_(root_url), http_(std::move(http)) {
    push_url(root_url);
  };

  void crawl();

  inline int url_count() const { return urls_.size(); }
  void push_url(UrlType url) { urls_.push_back(url);};
  void pop_url(){urls_.pop_front();};

  bool has_crawled_url(UrlType);

  // Crawler() = default;

private:


  UrlType root_url_;
  std::deque<UrlType> urls_;
  std::unordered_set<UrlType> seen_urls_;
  std::unique_ptr<Http> http_;

  // PageGetter page_getter_;

  // void push_links(GumboNode *node);
  // UrlType parse_link(const UrlTypex &);
  // void search_for_links(GumboNode *node);
};

} // namespace kraal
#endif /* CRAWLER_H */
