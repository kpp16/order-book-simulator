#pragma once

#include <iostream>
#include <future>
#include <curl/curl.h>

class RESTApi {
public:
    std::string url_base;
    RESTApi(std::string &url_base) : url_base(url_base) {}

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
        size_t total_size = size * nmemb;
        output->append(static_cast<char*>(contents), total_size);
        return total_size;
    }
    std::future<std::string> PerformAsyncPostRequest(const std::string& url, const std::string& data);

};
