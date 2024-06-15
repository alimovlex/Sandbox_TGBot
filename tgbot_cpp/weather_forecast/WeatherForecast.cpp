#include "WeatherForecast.hpp"
#include "network/network.hpp"

#include <boost/json.hpp>

WeatherForecast::WeatherForecast(const std::string& api) {
    api_ = api;
}

std::string WeatherForecast::get_city() const {
    return boost::json::value_to<std::string>(parsed_data_.at("name"));
}

void WeatherForecast::set_city(const std::string& city) {
    city_ = city;

    url_ =
        "http://api.openweathermap.org/data/2.5/"
        "weather?q=" +
        city_ + "&appid=" + api_ + "&lang=en";
}

bool WeatherForecast::check_city() const {
    if (parsed_data_.at("cod").is_int64()) {
        return true;
    } else {
        return false;
    }
}

void WeatherForecast::refresh() {
    curl_data_ = get_request(url_);
    parsed_data_ = boost::json::parse(curl_data_);
}

std::string WeatherForecast::get_forecast() const {
    return boost::json::value_to<std::string>(
        parsed_data_.at("weather").at(0).at("description"));
}

int WeatherForecast::get_temp() const {
    // kelvin_to_celsius
    return (boost::json::value_to<float>(parsed_data_.at("main").at("temp"))) -
           273;
}

float WeatherForecast::get_wind() const {
    return boost::json::value_to<float>(parsed_data_.at("wind").at("speed"));
}
