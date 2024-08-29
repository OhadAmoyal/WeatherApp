#ifndef FINALPROJECTCPP_WEATHER_H
#define FINALPROJECTCPP_WEATHER_H

#include <string>
#include <map>

std::string getWeatherData(const std::string& city);
std::map<std::string, std::string> processWeatherData(const std::string& data);

#endif //FINALPROJECTCPP_WEATHER_H
