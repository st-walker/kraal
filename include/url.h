#ifndef URL_H
#define URL_H

namespace kraal {
bool is_protocol_relative(std::string const &url);
bool is_absolute_url(std::string const &url);
std::string expand_protocol_relative_url(std::string const &protocol,
                                         std::string const &url);
std::string expand_url(std::string const &base, std::string const &url);
} // namespace kraal

#endif /* URL_H */
