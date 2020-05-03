#ifndef CRAWLER_H
#define CRAWLER_H

#include <queue>
#include <string>

#include "gumbo.h"

#include "page-getter.h"

namespace kraal {

class Crawler {
public:
  Crawler() = default;
  void crawl();

  inline int url_count() const { return urls_.size(); }
  void add_url(std::string url) { urls_.push(url);};
  void pop_url(){urls_.pop();};

private:
  std::queue<std::string> urls_;

  // PageGetter page_getter_;

  // void push_links(GumboNode *node);
  // std::string parse_link(const std::string &);
  // void search_for_links(GumboNode *node);
};

} // namespace kraal
#endif /* CRAWLER_H */
