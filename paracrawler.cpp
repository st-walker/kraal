#include <stdio.h>

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>


#include "crawler.h"


int main(void)
{

  auto url = std::string("https://www.bbcgoodfood.com");
  auto pg =  para::PageGetter();
  // auto page = pg.get(url);
  // std::cout << page;

  auto crawler = para::Crawler(url);
  crawler.crawl();

  // std::ifstream in(filename, std::ios::in | std::ios::binary);
  // if (!in) {
  //   std::cout << "File " << filename << " not found!\n";
  //   exit(EXIT_FAILURE);
  // }
  

  // std::string contents;
  // in.seekg(0, std::ios::end);
  // contents.resize(in.tellg());
  // in.seekg(0, std::ios::beg);
  // in.read(&contents[0], contents.size());
  // in.close();

  // GumboOutput* output = gumbo_parse(contents.c_str());
  // search_for_links(output->root);
  // gumbo_destroy_output(&kGumboDefaultOptions, output);
  
}
