#include <prerequisites.hpp>
#include <game.hpp>

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <fmt/core.h>

#include <string>
#include <exception>
#include <iostream>

int main() {
    std::string const pattern = "(%e) [%L] %v";
    spdlog::set_pattern(pattern);
    spdlog::set_level(spdlog::level::debug);
    try {
        nn::Game* game = new nn::Game();
        game->run();
    } catch (std::exception const &e) {
        fmt::print(stderr, "{}", e.what());
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
