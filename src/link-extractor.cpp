#include <vector>

#include "gumbo.h"

#include "link-extractor.h"

namespace kraal {

LinkExtractor::LinkExtractor(std::string const &html)
    : output_(gumbo_parse(html.c_str())) {}

LinkExtractor::~LinkExtractor() {
  gumbo_destroy_output(&kGumboDefaultOptions, output_);
}

LinkExtractor::url_collection_type
LinkExtractor::extract(std::string const &html) const {
  auto links = url_collection_type{};
  find_links(output_->root, links);
  return links;
}

void LinkExtractor::find_links(GumboNode *node,
                               url_collection_type &links) const {

  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute *href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    links.emplace_back(href->value);
  }

  GumboVector *children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    find_links(static_cast<GumboNode *>(children->data[i]), links);
  }
}

} // namespace kraal
