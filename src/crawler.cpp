#include <string>
#include <iostream>
#include <queue>

#include "gumbo.h"

#include "crawler.h"
// #include "LUrlParser.h"

namespace kraal {

void Crawler::crawl() {
  auto url = urls_.front();
  auto result = http_->get(url);
  urls_.pop();
}

} // namespace kraal

// void kraal::Crawler::crawl() {
//   auto url = urls_.front();
//   auto page = page_getter_.get(url);

//   GumboOutput* output = gumbo_parse(page.c_str());
//   search_for_links(output->root);
//   gumbo_destroy_output(&kGumboDefaultOptions, output);  

//   urls_.pop();
//   if (!urls_.empty()) {
//     crawl();
//   }
// }

// void kraal::Crawler::search_for_links(GumboNode* node) {
//   if (node->type != GUMBO_NODE_ELEMENT) {
//     return;
//   }
//   GumboAttribute* href;
//   if (node->v.element.tag == GUMBO_TAG_A &&
//       (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
//     urls_.push(std::string(href->value));
//     parse_link(std::string(href->value));
//   }

//   GumboVector* children = &node->v.element.children;
//   for (unsigned int i = 0; i < children->length; ++i) {
//     search_for_links(static_cast<GumboNode*>(children->data[i]));
//   }
// }

// std::string kraal::Crawler::parse_link(std::string const &link) {
//   std::cout << link << "\n";

//   // auto url = LUrlParser::ParseURL::parseURL(link);

//   // std::cout << "Scheme = " << url.scheme_ << "\n";
//   // std::cout << "Content = " << url.host_  << "\n";
//   // std::cout << "Path = " << url.path_ << "\n";    
//   return std::string();
// }
