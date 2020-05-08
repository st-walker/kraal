#ifndef HTTP_H
#define HTTP_H

#include <string>

class Http {
public:
  virtual ~Http(){};
  virtual std::string get(std::string const &) const = 0;
};


#endif /* HTTP_H */
