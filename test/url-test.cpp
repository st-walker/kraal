#include <iterator>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "url.h"

using namespace testing;
using namespace kraal;

static const std::string absolute("https://www.example.com/bar/baz");
static const std::string root_url("https://www.example.com/");
static const std::string relative_fragment("bar/baz");
static const std::string protocol_relative("//example.com/bar/baz");
static const std::string root_relative_fragment("/bar/baz");

TEST(URLQuerying, IsProtocolRelativeReturnsTrueForProtocolRelativeURL) {
  ASSERT_TRUE(is_protocol_relative(protocol_relative));
}

TEST(URLQuerying, IsProtocolRelativeReturnsFalseForNonProtocolRelativeURL) {
  ASSERT_FALSE(is_protocol_relative(absolute));
}

TEST(URLQuerying, IsAbsoluteReturnsTrueForAbsoluteURL) {
  ASSERT_TRUE(is_absolute_url(absolute));
}

TEST(URLQuerying, IsAbsoluteReturnsFalseForRelativeURL) {
  ASSERT_FALSE(is_absolute_url(relative_fragment));
}


TEST(URLExpansion, RelativeToAbsolute) {
  auto url = expand_url(root_url, relative_fragment);

  ASSERT_THAT(url, StrEq(absolute));
}

TEST(URLExpansion, DISABLED_ProtocolRelativeToAbsolute) {
  auto url = expand_protocol_relative_url(root_url, protocol_relative);

  ASSERT_THAT(url, StrEq(absolute));
}

TEST(URLExpansion, RootRelativeToAbsolute) {
  auto url = expand_url(root_url, root_relative_fragment);

  ASSERT_THAT(url, StrEq(absolute));
}
