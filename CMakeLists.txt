cmake_minimum_required(VERSION 3.0)

project(
    tgbot
    DESCRIPTION "Telegram bot showing currency exchange rates and weather forecast written in C++"
    HOMEPAGE_URL "https://github.com/dan4ik605743/tgbot_cpp"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(Boost_USE_MULTITHREADED ON)
set(CMAKE_CXX_FLAGS "-Wno-dangling-reference")
add_subdirectory(modules)
add_subdirectory(tgbot_cpp)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
