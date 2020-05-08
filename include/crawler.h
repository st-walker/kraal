#ifndef CRAWLER_H
#define CRAWLER_H

#include <queue>
#include <string>
#include <memory>

#include "gumbo.h"

#include "http.h"
#include "page-getter.h"
#include "curl-http.h"


namespace kraal {

class Crawler {
public:
  Crawler(std::unique_ptr<Http> http = std::make_unique<CurlHttp>())
      : http_(std::move(http)){};

  std::string crawl();

  inline int url_count() const { return urls_.size(); }
  void add_url(std::string url) { urls_.push(url);};
  void pop_url(){urls_.pop();};

  // Crawler() = default;

private:
  std::queue<std::string> urls_;
  std::unique_ptr<Http> http_;

  // PageGetter page_getter_;

  // void push_links(GumboNode *node);
  // std::string parse_link(const std::string &);
  // void search_for_links(GumboNode *node);
};

} // namespace kraal
#endif /* CRAWLER_H */
