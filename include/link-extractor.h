#ifndef LINK_EXTRACTOR_H
#define LINK_EXTRACTOR_H

#include <string>
#include <vector>

#include "gumbo.h"

#include "html-extractor.h"

namespace kraal {

class LinkExtractor : public HtmlExtractor {
public:
  virtual ~LinkExtractor(){};

  using url_collection_type = std::vector<std::string>;

  url_collection_type extract(std::string const &html) const override;

private:
  void find_links(GumboNode *node, url_collection_type &links) const;
};
} // namespace kraal

#endif /* LINK-EXTRACTOR_H */
