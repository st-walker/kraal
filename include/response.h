#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response {
public:
  Response() = default;
  Response(std::string status, std::string header, std::string body)
      : status_(status), header_(header), body_(body){};

private:
  std::string status_;
  std::string header_;
  std::string body_;
};

#endif /* RESPONSE_H */
