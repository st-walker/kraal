#include <regex>

#include <skyr/url.hpp>

#include "url.h"

namespace kraal {

static const std::regex absolute_uri_regex{"^(?:[a-z]+:)?//"};

URLType get_url_type(std::string const &url) {
  if (url.starts_with("//"))
    return URLType::PROTOCOL_RELATIVE;
  else if (url.front() == '/')
    return URLType::ROOT_RELATIVE;
  else if (regex_search(url, absolute_uri_regex))
    return URLType::ABSOLUTE;
  else
    return URLType::RELATIVE;
}

std::string expand_protocol_relative_url(std::string const &protocol,
                                         std::string const &url) {
  assert(get_url_type(url) == URLType::PROTOCOL_RELATIVE);
  std::string result = url;
  return protocol + ":" + url;
}

std::string expand_relative_url(std::string const &base,
                                std::string const &url) {
  return skyr::url(url, skyr::url(base)).href();
}

std::string get_protocol(std::string const &url) {
  auto result = skyr::url(url).protocol();
  assert(!result.empty());
  result.pop_back(); // Remove ':'.
  return result;
}

std::string get_hostname(std::string const &url) {
  return skyr::url(url).hostname();
}

} // namespace kraal
