#include "link-extractor.h"
#include "url.h"

namespace kraal {

void LinkExtractor::parse_base(GumboNode *node) {}

std::string LinkExtractor::expand_url(std::string const &url) const {
  auto url_type = get_url_type(url);

  switch (url_type) {
  case (URLType::PROTOCOL_RELATIVE):
    return expand_protocol_relative_url(protocol_, url);
  case (URLType::ABSOLUTE):
    return url;
  case (URLType::RELATIVE):
    return expand_relative_url(get_relative_url(), url);
  case (URLType::ROOT_RELATIVE):
    return expand_relative_url(root_url_, url);
  default:
    throw std::runtime_error("Unkown URL type.");
  }
}

bool LinkExtractor::is_internal_link(std::string const &url) const {
  auto url_hostname = get_hostname(url);
  return url_hostname.find(root_hostname_) != std::string::npos;
}

} // namespace kraal
