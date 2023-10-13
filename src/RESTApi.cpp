#include "../include/RESTApi.hpp"


std::future<std::string> RESTApi::PerformAsyncPostRequest(const std::string &url, const std::string &data) {
    return std::async(std::launch::async, [this, url, data]() {  // Capture 'this' explicitly
        CURL* curl = curl_easy_init();
        if (curl) {
            CURLcode res;
            std::string response_data;

            std::string new_url = this->url_base + url;  // Access 'url_base' using 'this'

            // Set the URL
            curl_easy_setopt(curl, CURLOPT_URL, new_url.c_str());

            // Set the POST data
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

            FILE *out = stdout;

            // Set the callback function to handle the response
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

            // Perform the request
            res = curl_easy_perform(curl);

            // Clean up and return the response
            curl_easy_cleanup(curl);

            if (res == CURLE_OK) {
                return response_data;
            } else {
                return std::string("Error: ") + curl_easy_strerror(res);
            }
        } else {
            return std::string("Error initializing CURL");
        }
    });
}
