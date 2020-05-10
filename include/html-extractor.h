#ifndef HTML_EXTRACTOR_H
#define HTML_EXTRACTOR_H

#include <string>

namespace kraal {

class HtmlExtractor {
public:
  virtual ~HtmlExtractor(){};
  virtual std::vector<std::string> extract(std::string const &html) const = 0;
};

}

#endif /* HTML-EXTRACTOR_H */
