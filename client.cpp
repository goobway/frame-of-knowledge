#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback function to write the response data to a string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// Function to send data to the server
void send_data_to_database(int studentId, const std::string &prompt, const std::string &classification, double confidence, unsigned char drawing[32][32])
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Convert the 2D matrix into a nested JSON array
        json matrix_json = json::array();
        for (int i = 0; i < 32; i++)
        {
            json row = json::array();
            for (int j = 0; j < 32; j++)
            {
                row.push_back(drawing[i][j]);
            }
            matrix_json.push_back(row);
        }
        // Create a JSON payload with the data
        json payload = {
            {"studentId", studentId},
            {"prompt", prompt},
            {"classification", classification},
            {"confidence", confidence},
            {"matrix", matrix_json}};
        std::string payload_str = payload.dump();

        // Set the server URL
        std::string serverUrl = "http://172.31.70.84:3000/add";

        // Set curl options
        curl_easy_setopt(curl, CURLOPT_URL, serverUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set the content type header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the JSON payload as the request body
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());

        // Send the request and display the response
        std::cout << "Sending request..." << std::endl;
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            std::cout << "Response: " << readBuffer << std::endl;
        }

        // Clean up curl resources
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
}

// int main()
// {
//     // Get the data from the user
//     std::cout << "Enter a student ID: ";
//     int studentId;
//     std::cin >> studentId;

//     std::cout << "Enter a prompt: ";
//     std::string prompt;
//     std::cin.ignore();
//     std::getline(std::cin, prompt);

//     std::cout << "Enter a classification label: ";
//     std::string classification;
//     std::getline(std::cin, classification);

//     std::cout << "Enter a confidence percentage: ";
//     double confidence;
//     std::cin >> confidence;

//     // Call the function to send the data to the server
//     send_data_to_database(studentId, prompt, classification, confidence);

//     return 0;
// }
