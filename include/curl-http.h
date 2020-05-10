#ifndef CURL_HTTP_H
#define CURL_HTTP_H

#include "http.h"
#include "response.h"


class CurlHttp : public Http {
public:
  CurlHttp() = default;
  virtual ~CurlHttp(){};

  std::unique_ptr<Response> get(std::string const &) const override {
    return std::make_unique<Response>();
  };
};


#endif /* CURL-HTTP_H */

