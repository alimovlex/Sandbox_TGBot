#include "bot/bot.hpp"
#include "fmt/core.h"
#include "tgbot/TgException.h"
#include "tgbot/types/BotCommand.h"

#include <boost/locale.hpp>
#include <cstdio>

bot::bot(const std::string& bot_token_str, const std::string& weather_api_str)
    : bot_(bot_token_str), long_poll_(bot_), weather_(weather_api_str) {
    get_weather_city_ = false;
    get_course_valute_ = false;

    bot_commands_ = {"start", "help", "weather", "currency"};
    bot_commands_description_ = {"Initialize bot",
                                 "Look what this bot can do",
                                 "Weather forecast by OpenWeatherMap",
                                 "Currency exchange rates"};

    std::vector<TgBot::BotCommand::Ptr> commands;
    std::vector<TgBot::BotCommand::Ptr> vectCmd;

    for (std::size_t x = 0; x != bot_commands_.size(); x++) {
        TgBot::BotCommand::Ptr cmdArray(new TgBot::BotCommand);
        cmdArray->command = bot_commands_[x];
        cmdArray->description = bot_commands_description_[x];
        commands.push_back(cmdArray);
    }

    bot_.getApi().setMyCommands(commands);
    vectCmd = bot_.getApi().getMyCommands();

    for (const auto& cmd : bot_.getApi().getMyCommands()) {
        fmt::print("cmd: {} -> {}\r", cmd->command.c_str(),
                   cmd->description.c_str());
    }
}

void bot::start() {
    start_command();
    help_command();
    weather_command();
    course_command();
    check_input();

    fmt::print("Bot username: {}\n", bot_.getApi().getMe()->username.c_str());
    bot_.getApi().deleteWebhook();
    while (true) {
        fmt::print("Long poll started\n");
        long_poll_.start();
    }
}

void bot::start_command() {
    bot_.getEvents().onCommand("start", [&](TgBot::Message::Ptr message) {
        bot_.getApi().sendMessage(message->chat->id,"Hi! Call /help for more info about commands.");
    });
}

void bot::help_command() {
    bot_.getEvents().onCommand("help", [&](TgBot::Message::Ptr message) {
        bot_.getApi().sendMessage(
            message->chat->id,
            "I can show weather forecast for your city. Just write /weather"
            "\nI can show the currency exchange rate. Just type /currency");
    });
}

void bot::weather_command() {
    bot_.getEvents().onCommand("weather", [&](TgBot::Message::Ptr message) {
        bot_.getApi().sendMessage(message->chat->id, "Please enter a city name");

        get_weather_city_ = true;
        long_poll_.start();
        weather_.refresh();

        if (weather_.check_city()) {
            bot_.getApi().sendMessage(
                message->chat->id,
                "Weather in the following town: " + weather_.get_city() + '\n' +
                    weather_.get_weather() + "\nTemperature " +
                    std::to_string(weather_.get_temp()) + "°C\nWind speed: " +
                    std::to_string(weather_.get_wind()) + " m/h");
            get_weather_city_ = false;
        } else {
            bot_.getApi().sendMessage(message->chat->id,"Invalid city name entered");
            get_weather_city_ = false;
        }
    });
}

void bot::course_command() {
    bot_.getEvents().onCommand("currency", [&](TgBot::Message::Ptr message) {
        bot_.getApi().sendMessage(message->chat->id,"Please enter currency code.\nFor example: usd");

        get_course_valute_ = true;
        long_poll_.start();
        course_.refresh();

        if (course_.check_currency()) {
            bot_.getApi().sendMessage(message->chat->id,
                                      course_.get_currency() + ": " +
                                      std::to_string(course_.get_exchange_rate()) +
                                      " ₽");
            get_course_valute_ = false;
        } else {
            bot_.getApi().sendMessage(message->chat->id, "Invalid currency code entered");
            get_course_valute_ = false;
        }
    });
}

void bot::check_input() {
    bot_.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
        if (get_weather_city_) {
            weather_.set_city(message->text);
            return;
        }

        if (get_course_valute_) {
            course_.set_currency(boost::locale::to_upper(message->text));
            return;
        }

        for (const auto& command : bot_commands_) {
            if ("/" + command == message->text) {
                return;
            }
        }

        bot_.getApi().sendMessage(message->chat->id,"Invalid command provided. Please enter /help for more info.");
    });
}
