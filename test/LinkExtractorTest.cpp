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
  static const std::string html_root_url;
  static const std::string html_document_url;
  static const std::string valid_html_document;
  std::unique_ptr<LinkExtractor> extractor;

  void SetUp() {
    extractor = std::make_unique<LinkExtractor>(
        valid_html_document, html_root_url, html_document_url);
  }
};

const std::string ALinkExtractor::html_root_url("https://www.example.com");
const std::string
    ALinkExtractor::html_document_url("https://www.example.com/foo/");

const std::string ALinkExtractor::valid_html_document(R"(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>title</title>
    <link rel="stylesheet" href="style.css">
    <script src="script.js"></script>
    <base href="https://www.example.org" target="_blank">
  </head>
  <body>
    <!-- page content -->
    <a name="foo" href="https://www.example.com"> absolute url </a>
  </body>
</html>
)");

TEST_F(ALinkExtractor, ExtractsOneURLFromHTMLDocumentWithOneURL) {
  std::vector<std::string> links{};
  extractor->extract(std::back_inserter(links));

  ASSERT_THAT(links.size(), Eq(1));
}

TEST_F(ALinkExtractor, ExtractsBaseFromHTMLDocument) {
  std::vector<std::string> links{};
  extractor->extract(std::back_inserter(links));
  ASSERT_THAT(extractor->base_tag_url(),
	      Eq(std::string("https://www.example.org")));
}

// TEST_F(ALinkExtractor, ExtractsAbsoluteURLFromHTMLDocument) {
//   std::vector<std::string> links{};
//   extractor->extract(std::back_inserter(links));

//   ASSERT_THAT(links.at(0), Eq(std::string("https://www.example.com")));
// }

// // https://stackoverflow.com/questions/2005079/absolute-vs-relative-urls

// TEST_F(ALinkExtractor, ExtractsExpandedRelativeURLFromHTMLDocument) {
//   std::set<std::string> links{};
//   extractor->extract(std::inserter(links, std::begin(links)));

//   ASSERT_THAT(links, Contains("https://www.example.com/foo/bar"));
// }

// TEST_F(ALinkExtractor, ExpandsProtocolRelativeURLToAbsolute) {
//   std::set<std::string> links{};
//   extractor->extract(std::inserter(links, std::begin(links)));

//   ASSERT_THAT(links, Contains("https://www.example.org/"));
// }

// TEST_F(ALinkExtractor, ExpandsRootRelativeURLToAbsolute) {
//   std::set<std::string> links{};
//   extractor->extract(std::inserter(links, std::begin(links)));

//   ASSERT_THAT(links, Contains("https://www.example.com/qux"));  
// }

// TEST_F(ALinkExtractor, ExpandsBaseRelativeURLToAbsolute) {
//   FAIL();
// }
