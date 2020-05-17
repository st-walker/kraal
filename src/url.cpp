// #include <regexp>

#include <skyr/url.hpp>

namespace kraal {

bool is_protocol_relative(std::string const &url) {
  return url.starts_with("//");
}

bool is_absolute_url(std::string const &url) {
  return url.starts_with("http://") || url.starts_with("https://") ||
         is_protocol_relative(url);
}

std::string expand_protocol_relative_url(std::string const &protocol,
                                         std::string const &url) {
  assert(is_protocol_relative(url));
  return url;
  // index == std::string::npos return u
}

std::string expand_url(std::string const &base, std::string const &url) {
  return skyr::url(url, skyr::url(base)).href();
}

} // namespace kraal
