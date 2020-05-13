#ifndef CRAWLER_H
#define CRAWLER_H

#include <queue>
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
  Crawler(std::unique_ptr<Http> http = std::make_unique<CurlHttp>())
      : http_(std::move(http)){};

  void crawl();

  inline int url_count() const { return urls_.size(); }
  void add_url(UrlType url) { urls_.push(url);};
  void pop_url(){urls_.pop();};

  bool has_crawled_url(UrlType);

  // Crawler() = default;

private:


  std::queue<UrlType> urls_;
  std::unordered_set<UrlType> seen_urls_;
  std::unique_ptr<Http> http_;

  // PageGetter page_getter_;

  // void push_links(GumboNode *node);
  // UrlType parse_link(const UrlTypex &);
  // void search_for_links(GumboNode *node);
};

} // namespace kraal
#endif /* CRAWLER_H */
