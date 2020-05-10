#include <cstring>
#include <memory>

#include <curl/curl.h>

#include "curl-http.h"

namespace {

size_t writer(char *ptr, size_t size, size_t nmemb, std::string *data) {

  if (data == NULL)
    return 0;

  data->append(ptr, size * nmemb);
  return size * nmemb;
}
} // namespace

namespace kraal {

std::unique_ptr<Response> CurlHttp::get(std::string const &url) const {
  long response_code = 0;
  CURLcode res;
  std::string header;
  std::string body;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuff);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1l);
    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    } else {
      size_t len = strlen(errbuff);
      fprintf(stderr, "\nlibcurl: (%d) ", res);
      if (len)
        fprintf(stderr, "%s%s", errbuff,
                ((errbuff[len - 1] != '\n') ? "\n" : ""));
      else
        fprintf(stderr, "%s\n", curl_easy_strerror(res));
    }
  }
  return std::make_unique<Response>(response_code, header, body);
}
} // namespace kraal
