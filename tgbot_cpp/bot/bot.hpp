#ifndef BOT_HPP
#define BOT_HPP

#include "exchange_rate/ExchangeRate.hpp"
#include "tgbot/Bot.h"
#include "tgbot/net/TgLongPoll.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "weather_forecast/WeatherForecast.hpp"

#include <string>

class bot {
   public:
    bot(const std::string& bot_token_str, const std::string& weather_api_str);

    virtual void start();

   protected:
    void start_command();
    void help_command();
    virtual void weather_command();
    virtual void course_command();
    void check_input();

    TgBot::Bot bot_;
    TgBot::TgLongPoll long_poll_;
    bool get_weather_city_;
    bool get_course_valute_;
    std::vector<std::string> bot_commands_;
    std::vector<std::string> bot_commands_description_;
    WeatherForecast weather_;
    ExchangeRate course_;
};

#endif
