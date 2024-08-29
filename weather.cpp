#include "weather.h"
#include "lib/httplib/httplib.h"
#include "lib/json/single_include/nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

// פונקציה שמבצעת בקשת HTTP ומביאה נתוני מזג האוויר
std::string getWeatherData(const std::string& city) {
    httplib::Client client("http://api.openweathermap.org");
    std::string url = "/data/2.5/weather?q=" + city + "&appid=c6fad0ab059d515ef7e834ff71852d1e";
    auto res = client.Get(url.c_str());

    if (res && res->status == 200) {
        return res->body;
    } else {
        std::cerr << "Failed to fetch weather data" << std::endl;
        return "";
    }
}

// פונקציה שמבצעת עיבוד של נתוני מזג האוויר
std::map <std::string, std::string> processWeatherData(const std::string& data) {
    auto weatherJson = json::parse(data);
    std::map <std::string, std::string> processed_data;

    //initialize the values map
    processed_data["temp"] = to_string(weatherJson["main"]["temp"]);
    processed_data["feels_like"] =to_string(weatherJson["main"]["feels_like"]);
    processed_data["pressure"] = to_string(weatherJson["main"]["pressure"]);
    processed_data["humidity"] = to_string(weatherJson["main"]["humidity"]);
    processed_data["sea_level"] = to_string(weatherJson["main"]["sea_level"]);
    processed_data["ground_level"] = to_string(weatherJson["main"]["grnd_level"]);
    processed_data["wind_speed"] = to_string(weatherJson["wind"]["speed"]);
    processed_data["weather_description"] = to_string(weatherJson["weather"][0]["description"]);

    return processed_data;
}
