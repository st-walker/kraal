#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

struct Response {
  long status;
  std::string header;
  std::string body;
};

#endif /* RESPONSE_H */
