#include <iterator>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "link-extractor.h"

using namespace testing;
using namespace kraal;

class ALinkExtractor : public Test {
public:
  static const std::string valid_html_document;
  std::unique_ptr<LinkExtractor> extractor;

  void SetUp() {
    extractor = std::make_unique<LinkExtractor>(valid_html_document);
  }
};

const std::string ALinkExtractor::valid_html_document(R"(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>title</title>
    <link rel="stylesheet" href="style.css">
    <script src="script.js"></script>
  </head>
  <body>
    <!-- page content -->
    <a name="foo" href="example-url-string"> 
    link text
    </a>
  </body>
</html>
)");

TEST_F(ALinkExtractor, ExtractsOneURLFromHTMLDocumentWithOneURL) {
  std::vector<std::string> links{};
  extractor->extract(std::back_inserter(links));

  ASSERT_THAT(links.size(), Eq(1));
}

TEST_F(ALinkExtractor, ExtractsCorrectURLFromHTMLDocument) {
  std::vector<std::string> links{};
  extractor->extract(std::back_inserter(links));

  ASSERT_THAT(links.at(0), Eq(std::string("example-url-string")));
}
