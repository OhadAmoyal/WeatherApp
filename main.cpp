#include "lib/httplib/httplib.h"
#include "lib/json/single_include/nlohmann/json.hpp"
#include <iostream>
#include "weather.h"
#include <string>
#include "UI.h"

using json = nlohmann::json;

// Function to get valid input for a field
std::string getFieldInput(const std::vector<std::string>& fields) {
    std::string data_field;
    std::cin >> data_field;
    while (std::find(fields.begin(), fields.end(), data_field) == fields.end()) {
        std::cout << "Error: there is no such value.\nPlease choose one of the following:\n"
                     "temp, feels_like, pressure, humidity, sea_level, ground_level, wind_speed, "
                     "weather_description\n";
        std::cin >> data_field;
    }
    return data_field;
}

// Function to get weather information for a city with error handling
void getWeatherForCity(const std::string& city, const std::string& data_field) {
    std::string weatherData = getWeatherData(city);  // Fetch weather data
    if (weatherData.empty()) {  // Check if data was fetched successfully
        std::cout << "Failed to fetch weather data for " << city << ". Please check the city name and try again.\n";
        return;
    }

    try {
        std::map<std::string, std::string> res = processWeatherData(weatherData);  // Process weather data
        std::cout << "======================================\n"
                  << "The " << data_field << " in " << city << " is " << res[data_field]
                  << "\n======================================\n";
    } catch (const json::parse_error& e) {  // Catch JSON parsing errors
        std::cout << "Error parsing weather data: " << e.what() << "\n";
    } catch (const std::exception& e) {  // Catch other exceptions
        std::cout << "An error occurred: " << e.what() << "\n";
    }
}

// Function to handle the "new" action
void handleNewAction(const std::vector<std::string>& fields) {
    std::string city;
    std::cout << "Type a city name: ";
    std::cin >> city;
    std::cout << "What would you like to know about " << city << " ?\n";
    std::string data_field = getFieldInput(fields);
    getWeatherForCity(city, data_field);
}

// Function to handle the "popular" action
void handlePopularAction(const std::vector<std::string>& fields, const std::vector<std::string>& cities) {
    std::string city;
    std::cout << "Currently, the popular cities in our site are:\n"
                 "Haifa, Eilat, London, Barcelona, Bangkok, Cairo\n"
                 "Which one of the popular cities would you like to explore?\n";
    std::cin >> city;
    while (std::find(cities.begin(), cities.end(), city) == cities.end()) {
        std::cout << "Error: there is no such city in the popular cities.\nPlease choose one of the above\n";
        std::cin >> city;
    }
    std::cout << "What would you like to know about " << city << " ?\n";
    std::string data_field = getFieldInput(fields);
    getWeatherForCity(city, data_field);
}

// Function to handle the "favourite" action
void handleFavouriteAction(const std::vector<std::string>& fields, std::vector<std::string>& favourite) {
    std::cout << "Your current favourite cities list is:\n";
    for (const auto& fav_city : favourite) {
        std::cout << fav_city << " ";
    }
    std::cout << "\nType the city name you want or 'add' for a new city\n";

    std::string action2;
    std::cin >> action2;

    std::string city;
    if (action2 == "add") {
        std::cout << "Type the name of the new city: \n";
        std::cin >> city;
        favourite.push_back(city);
    } else {
        city = action2;
    }

    while (std::find(favourite.begin(), favourite.end(), city) == favourite.end()) {
        std::cout << "Error: there is no such city in your favourite list, please type again: \n";
        std::cin >> city;
    }

    std::cout << "What would you like to know about " << city << " ?\n";
    std::string data_field = getFieldInput(fields);
    getWeatherForCity(city, data_field);
}

// Main function
int main() {
    std::string action;
    std::vector<std::string> fields = {"temp", "feels_like", "pressure", "humidity",
                                       "sea_level", "ground_level", "wind_speed", "weather_description"};
    std::vector<std::string> cities = {"Haifa", "Eilat", "London", "Barcelona", "Bangkok", "Cairo",
                                       "haifa", "eilat", "london", "barcelona", "bangkok", "cairo"};
    std::vector<std::string> favourite;

    std::cout << "==================================\n"
                 "====  WELCOME TO WEATHER APP  ====\n"
                 "==================================\n\n";

    while (action != "terminate") {
        std::cout << "Choose your desired action: (options: new, popular, favourite, terminate)\n";
        std::cin >> action;

        if (action == "new") {
            handleNewAction(fields);
        } else if (action == "popular") {
            handlePopularAction(fields, cities);
        } else if (action == "favourite") {
            handleFavouriteAction(fields, favourite);
        } else if (action != "terminate") {
            std::cout << "Error: Invalid action\n";
        }
    }

    std::cout << "========================================\n"
                 "====  Thanks for using WEATHER APP  ====\n"
                 "====   Hope to see you again soon   ====\n"
                 "====            ^    ^              ====\n"
                 "====            ------              ====\n"
                 "========================================\n\n";
    return 0;
}
