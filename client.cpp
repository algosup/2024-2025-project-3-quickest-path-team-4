#include <iostream>
#include <string>
#include <curl/curl.h>

void send_numbers(int number1, int number2) {
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;

        // Construct the URL with query parameters
        std::string url = "http://192.168.15.254:8080/numbers?num1=" + std::to_string(number1) + "&num2=" + std::to_string(number2);

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the HTTP method to GET (default, so no need to explicitly set it)

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "GET request sent successfully!" << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
}



int main() {
    int num1, num2;
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;

    send_numbers(num1, num2);
    return 0;
}
