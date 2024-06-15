#include "ExchangeRate.hpp"
#include "network/network.hpp"

#include <boost/json.hpp>

std::string ExchangeRate::get_currency() {
    return currency_;
}

void ExchangeRate::set_currency(const std::string& valute) {
    currency_ = valute;
}

bool ExchangeRate::check_currency() const {
    try {
        boost::json::value_to<std::string>(
            parsed_data_.at("Valute").at(currency_).at("ID"));
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void ExchangeRate::refresh() {
    curl_data_ = get_request(url_);
    parsed_data_ = boost::json::parse(curl_data_);
}

float ExchangeRate::get_exchange_rate() const {
    return boost::json::value_to<float>(
        parsed_data_.at("Valute").at(currency_).at("Value"));
}
