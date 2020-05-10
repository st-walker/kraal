#ifndef HTTP_H
#define HTTP_H

#include <string>

class Response;

class Http {
public:
  virtual ~Http(){};
  virtual std::unique_ptr<Response> get(std::string const &) const = 0;
};

#endif /* HTTP_H */
