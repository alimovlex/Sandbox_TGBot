#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <boost/json/value.hpp>
#include <string>

class ExchangeRate {
   public:
    std::string get_currency();
    void set_currency(const std::string& valute);
    bool check_currency() const;

    void refresh();

    float get_exchange_rate() const;

   private:
    std::string curl_data_;
    boost::json::value parsed_data_;

    inline const static std::string url_ =
        "https://www.cbr-xml-daily.ru/daily_json.js";
    std::string currency_;
};

#endif
