#ifndef URL_H
#define URL_H

namespace kraal {

enum class URLType { ABSOLUTE, RELATIVE, PROTOCOL_RELATIVE, ROOT_RELATIVE };

URLType get_url_type(std::string const &);

// bool is_protocol_relative(std::string const &url);
// bool is_absolute_url(std::string const &url);
std::string expand_protocol_relative_url(std::string const &protocol,
                                         std::string const &url);
std::string expand_relative_url(std::string const &base,
                                std::string const &url);

bool is_internal_url(std::string const &root_url, std::string const &other_url);

std::string get_protocol(std::string const &url);

std::string get_hostname(std::string const &url);

} // namespace kraal

#endif /* URL_H */
