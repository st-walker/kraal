#ifndef CRAWLER_H
#define CRAWLER_H

#include <queue>
#include <string>

#include "gumbo.h"

#include "page-getter.h"

namespace para {

class Crawler {
public:
  Crawler(std::string seed);
  void crawl();
  void print();

private:
  std::string seed_;
  std::queue<std::string> urls_;

  PageGetter page_getter_;

  void push_links(GumboNode *node);
  std::string parse_link(const std::string &);
  void search_for_links(GumboNode *node);
};

} // namespace para
#endif /* CRAWLER_H */
