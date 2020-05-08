#ifndef CURL_HTTP_H
#define CURL_HTTP_H

#include "http.h"

class CurlHttp : public Http {
public:
  CurlHttp() = default;
  virtual ~CurlHttp(){};
  
  std::string get(std::string const &) const override {return std::string("");};
};


#endif /* CURL-HTTP_H */

