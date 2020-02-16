#include <stdio.h>
#include <string>

#include <curl/curl.h>

#include "page-getter.h"

para::PageGetter::PageGetter() { curl = curl_easy_init(); }

para::PageGetter::~PageGetter() { curl_easy_cleanup(curl); }

static size_t writer(char *ptr, size_t size, size_t nmemb, std::string *data) {

  if (data == NULL)
    return 0;

  data->append(ptr, size * nmemb);
  return size * nmemb;
}

std::string para::PageGetter::get(std::string address) {

  CURLcode res;
  std::string buffer;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1l);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      size_t len = strlen(errbuf);
      fprintf(stderr, "\nlibcurl: (%d) ", res);
      if (len)
        fprintf(stderr, "%s%s", errbuf,
                ((errbuf[len - 1] != '\n') ? "\n" : ""));
      else
        fprintf(stderr, "%s\n", curl_easy_strerror(res));
    }
  }
  return buffer;
}
