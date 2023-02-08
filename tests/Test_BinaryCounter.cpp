/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_BinaryCounter.cpp
*/

#include "doctest.h"
#include "BinaryCounter.hpp"
#include "InputComponent.hpp"
#include "ClockComponent.hpp"
#include <iostream>

static int parseBinaryOutput(nts::BinaryCounter &counter)
{
    nts::Tristate bits[12] = {
        counter.compute(9),
        counter.compute(7),
        counter.compute(6),
        counter.compute(5),
        counter.compute(3),
        counter.compute(2),
        counter.compute(4),
        counter.compute(13),
        counter.compute(12),
        counter.compute(14),
        counter.compute(15),
        counter.compute(1)
    };
    int value = 0;
    for (int i = 0; i < 12; i++) {
        if (bits[i] == nts::Tristate::True) {
            value += 1 << i;
        }
        if (bits[i] == nts::Undefined)
            value += 1000000;
    }
    return value;
}

static void setInputValue(nts::InputComponent &input, nts::Tristate value)
{
    input.setValue(value);
    input.simulate(1);
}

TEST_CASE("BinaryCounter")
{
    nts::BinaryCounter counter("counter");

    REQUIRE(counter.getName() == "counter");

    // Reset clock
    nts::ClockComponent clock("clock");
    nts::InputComponent reset("reset");
    REQUIRE_NOTHROW(counter.setLink(10, clock, 1));
    REQUIRE_NOTHROW(counter.setLink(11, reset, 1));
    REQUIRE_THROWS(counter.setLink(10, clock, 1));
    REQUIRE_THROWS(counter.setLink(11, reset, 1));

    setInputValue(clock, nts::Tristate::True);
    setInputValue(reset, nts::Tristate::True);

    REQUIRE(parseBinaryOutput(counter) == 0);
    counter.simulate(0);
    setInputValue(reset, nts::Tristate::False);

    SUBCASE("Normal counting")
    {
        for (int i = 0; i < 4096; i++) {
            REQUIRE(parseBinaryOutput(counter) == i);
            counter.simulate(0);
            clock.simulate(0);
            if (i) {
                REQUIRE(parseBinaryOutput(counter) == i);
                counter.simulate(0);
                clock.simulate(0);
            }
        }
        // Overflow
        REQUIRE(parseBinaryOutput(counter) == 0);
        counter.simulate(0);
    }

    SUBCASE("Undefined reset/increase")
    {
        // Reset, but every bit is at 0, so result is 0
        setInputValue(reset, nts::Undefined);
        REQUIRE(parseBinaryOutput(counter) == 0);
        counter.simulate(0);

        // Increase counter by 1
        clock.simulate(0); // Clock low
        setInputValue(reset, nts::False);
        REQUIRE(parseBinaryOutput(counter) == 1);
        clock.simulate(0); // Clock high
        counter.simulate(0);

        // Undefined reset
        setInputValue(reset, nts::Undefined);
        REQUIRE(parseBinaryOutput(counter) == 1000000); // 1000000, because only 1 number is undefined here
        counter.simulate(0);
        clock.simulate(0); // Clock low

        // Increase counter by 1, but previous result is undefined, so new bit is undefined too
        setInputValue(reset, nts::False);
        REQUIRE(parseBinaryOutput(counter) == 2000000);
        counter.simulate(0);
        clock.simulate(0); // Clock high

        // Kepp increaseing the counter, and for each power of 2, increase the check value
        for (int i = 1; i < 11; i++) {
            // Increase counter
            parseBinaryOutput(counter);
            counter.simulate(0);
            clock.simulate(0); // Clock low

            REQUIRE(parseBinaryOutput(counter) == 2000000 + i * 1000000);
            counter.simulate(0);
            clock.simulate(0); // Clock high
        }
    }
}
