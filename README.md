# Sandbox_TGBot

A telegram bot written in C++ using the <a href="https://github.com/reo7sp/tgbot-cpp">tgbot-cpp</a> telegram API library. Able to send data about the <a href="https://openweathermap.org/">weather</a> and <a href="https://www.cbr.ru/currency_base/daily/">exchange rates</a>.

## Dependencies
* boost(>=1.75) 
* cmake 
* openssl 
* curl 
* zlib 

## Bot compilation
```
git clone https://github.com/dan4ik605743/tgbot_cpp
cd tgbot_cpp
mkdir build && cd build
cmake ../
cmake --build .
```

### Build options
```
-DTGBOT_ENABLE_INLINE_KEYBOARD  # Enable support inline keyboard in bot
```

## Usage
In main.cpp, you need to enter 2 parameters, the api key from openweathermap and the bot token itself.
```
./tgbot
```
