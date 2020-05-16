#ifndef CURL_HTTP_H
#define CURL_HTTP_H

#include <curl/curl.h>

#include "http.h"
#include "response.h"

namespace kraal {

class CurlHttp : public Http {
public:
  CurlHttp() { curl = curl_easy_init(); }
  virtual ~CurlHttp() { curl_easy_cleanup(curl); }

  Response get(std::string const &) const override;

private:
  CURL *curl;
  char errbuff[CURL_ERROR_SIZE];
};
} // namespace kraal

#endif /* CURL-HTTP_H */
