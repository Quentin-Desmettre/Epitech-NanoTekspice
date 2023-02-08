/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** TestClockComponent.cpp
*/

#include "doctest.h"
#include "ClockComponent.hpp"

TEST_CASE("ClockComponent")
{
    // Base test
    nts::ClockComponent clocks[4] = {
        nts::ClockComponent("clock1"),
        nts::ClockComponent("clock2"),
        nts::ClockComponent("clock3"),
        nts::ClockComponent("clock4")
    };
    for (int i = 0; i < 4; i++) {
        REQUIRE(clocks[i].getName() == "clock" + std::to_string(i + 1));
        REQUIRE(clocks[i].getValue() == nts::Undefined);
    }

    // Switch clocks
    for (int i = 0; i < 4; i++) {
        clocks[i].simulate(0);
        REQUIRE(clocks[i].getName() == "clock" + std::to_string(i + 1));
        REQUIRE(clocks[i].getValue() == nts::Undefined);
    }

    // Set their value
    for (int i = 0; i < 4; i++) {
        clocks[i].setValue((i % 2) == 0 ? nts::False : nts::True);
        REQUIRE(clocks[i].getValue() == nts::Undefined);
        clocks[i].simulate(0);
        CHECK(clocks[i].compute() == ((i % 2) == 0 ? nts::False : nts::True));
        REQUIRE(clocks[i].getValue() == ((i % 2) == 0 ? nts::False : nts::True));
    }

    // Switch clocks
    for (int i = 0; i < 4; i++) {
        clocks[i].simulate(0);
        CHECK(clocks[i].getValue() == ((i % 2) == 0 ? nts::True : nts::False));
    }
}
