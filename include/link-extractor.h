#ifndef LINK_EXTRACTOR_H
#define LINK_EXTRACTOR_H

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "gumbo.h"

#include "url.h"

namespace kraal {

class LinkExtractor {
public:
  LinkExtractor(std::string const &html, std::string const &root_url,
                std::string const &page_url)
      : output_(gumbo_parse(html.c_str())),
	root_url_(root_url),
        page_url_(page_url), base_url_(""),
	protocol_(get_protocol(page_url_)),
        root_hostname_(get_hostname(root_url)){};

  ~LinkExtractor() { gumbo_destroy_output(&kGumboDefaultOptions, output_); };

  using url_collection_type = std::vector<std::string>;

  template <typename InsertIt> void extract(InsertIt it) {
    find_links(output_->root, it);
  }

  inline std::string base_tag_url() const { return base_url_; }

private:
  GumboOutput *output_;

  std::string root_url_; // Root URL of the webpage
  std::string page_url_; // URL of the current page
  std::string base_url_; // any base url provided by the base tag.
  std::string protocol_; // http:, https:..
  std::string root_hostname_;

  inline std::string get_relative_url() const {
    return base_url_.empty() ? page_url_ : base_url_;
  }

  bool is_internal_link(std::string const &url) const;
  
  void parse_base(GumboNode *node);
  std::string expand_url(std::string const &) const;

  template <typename InsertIt>
  void find_links(GumboNode *node, InsertIt it) {
    if (node->type != GUMBO_NODE_ELEMENT) {
      return;
    }

    GumboAttribute *href;
    if (node->v.element.tag == GUMBO_TAG_BASE &&
	(href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
      assert(base_url_ == "");
      base_url_ = href->value;
    }

    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
      auto expanded_url =  expand_url(href->value);
      if (is_internal_link(expanded_url)) {
	it = expanded_url;
      }
    }
    GumboVector *children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      find_links(static_cast<GumboNode *>(children->data[i]), it);
    }
  }
};
} // namespace kraal

#endif /* LINK-EXTRACTOR_H */
