#ifndef LINK_EXTRACTOR_H
#define LINK_EXTRACTOR_H

#include <iterator>
#include <string>
#include <vector>

#include "gumbo.h"

namespace kraal {

class LinkExtractor {
public:
  LinkExtractor(std::string const &html) : output_(gumbo_parse(html.c_str())){};
  ~LinkExtractor() { gumbo_destroy_output(&kGumboDefaultOptions, output_); };

  using url_collection_type = std::vector<std::string>;

  template <typename InsertIt> void extract(InsertIt it) const {
    find_links(output_->root, it);
  }

private:
  GumboOutput *output_;

  template <typename InsertIt>
  void find_links(GumboNode *node, InsertIt it) const {
    if (node->type != GUMBO_NODE_ELEMENT) {
      return;
    }
    GumboAttribute *href;
    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
      it = href->value;
    }

    GumboVector *children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      find_links(static_cast<GumboNode *>(children->data[i]), it);
    }
  }
};
} // namespace kraal

#endif /* LINK-EXTRACTOR_H */
