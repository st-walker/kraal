#include <iterator>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "url.h"

using namespace testing;
using namespace kraal;

static const std::string absolute_url("https://www.example.com/bar/baz");
static const std::string root_url("https://www.example.com/");
static const std::string relative_url("bar/baz");
static const std::string protocol_relative_url("//www.example.com/bar/baz");
static const std::string root_relative_url("/bar/baz");

std::string type_to_name(URLType t) {
  switch(t) {
  case(URLType::ABSOLUTE):
    return std::string("absolute");
    break;
  case(URLType::RELATIVE):
    return std::string("relative");
    break;
  case (URLType::PROTOCOL_RELATIVE):
    return std::string("protocol_relative");
    break;
  case(URLType::ROOT_RELATIVE):
    return std::string("root_relative");
    break;
  }
}
  

TEST(URLQuerying, ReturnsCorrectURLType) {
  ASSERT_THAT(get_url_type(absolute_url), URLType::ABSOLUTE) << "Ohdear000";
  ASSERT_THAT(get_url_type(relative_url), URLType::RELATIVE)
    << type_to_name(get_url_type(relative_url));
  ASSERT_THAT(get_url_type(protocol_relative_url), URLType::PROTOCOL_RELATIVE);
  ASSERT_THAT(get_url_type(root_relative_url), URLType::ROOT_RELATIVE);

}

TEST(URLExpansion, RelativeToAbsolute) {
  auto url = expand_relative_url(root_url, relative_url);

  ASSERT_THAT(url, StrEq(absolute_url));
}

TEST(URLExpansion, ProtocolRelativeToAbsolute) {
  auto url = expand_protocol_relative_url("https", protocol_relative_url);

  ASSERT_THAT(url, StrEq(absolute_url));
}

TEST(URLExpansion, RootRelativeToAbsolute) {
  auto url = expand_relative_url(root_url, root_relative_url);

  ASSERT_THAT(url, StrEq(absolute_url));
}

TEST(URLQuerying, ReturnsHostname) {
  ASSERT_THAT(get_hostname("https://www.example.com/"), Eq("www.example.com"));
  ASSERT_THAT(get_hostname("https://example.com/"), Eq("example.com"));
}
