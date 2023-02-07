/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_FlipFlop.cpp
*/

#include "../include/FlipFlopComponent.hpp"
#include "doctest.h"
#include "../include/InputComponent.hpp"
#include <iostream>


static void setInputVal(nts::InputComponent &component, nts::Tristate value)
{
    component.setValue(value);
    component.simulate(0);
}

TEST_CASE("single FlipFlop")
{
    nts::FlipFlopComponent flipFlop("flipFlop");

    REQUIRE(flipFlop.getName() == "flipFlop");
    REQUIRE(flipFlop.compute(5) == nts::Undefined);
    REQUIRE(flipFlop.compute(6) == nts::Undefined);
    flipFlop.simulate(0);

    nts::InputComponent clock("in1");
    nts::InputComponent data("in2");
    nts::InputComponent set("in3");
    nts::InputComponent reset("in4");

    REQUIRE_THROWS(flipFlop.setLink(0, clock, 1));
    REQUIRE_THROWS(flipFlop.setLink(7, clock, 1));
    REQUIRE_THROWS(flipFlop.setLink(-1, clock, 1));
    REQUIRE_NOTHROW(flipFlop.setLink(1, clock, 1));
    REQUIRE_NOTHROW(flipFlop.setLink(2, data, 1));
    REQUIRE_NOTHROW(flipFlop.setLink(3, set, 1));
    REQUIRE_NOTHROW(flipFlop.setLink(4, reset, 1));

    REQUIRE(flipFlop.compute(5) == nts::Undefined);
    REQUIRE(flipFlop.compute(6) == nts::Undefined);
    flipFlop.simulate(0);

    // Reset clock
    setInputVal(clock, nts::False);
    setInputVal(set, nts::False);
    setInputVal(reset, nts::True);
    REQUIRE(flipFlop.compute(5) == nts::False);
    REQUIRE(flipFlop.compute(6) == nts::True);
    flipFlop.simulate(0);
    setInputVal(reset, nts::False);

    SUBCASE("Positive going edge")
    {
        // Low to high -> change data
        setInputVal(clock, nts::True);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);

        // High to low -> don't change data
        setInputVal(clock, nts::False);
        setInputVal(data, nts::False);
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);

        // Low to high -> change data
        setInputVal(clock, nts::True);
        setInputVal(data, nts::False);
        REQUIRE(flipFlop.compute(5) == nts::False);
        REQUIRE(flipFlop.compute(6) == nts::True);
        flipFlop.simulate(0);

        // High to low -> dont change data
        setInputVal(clock, nts::False);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::False);
        REQUIRE(flipFlop.compute(6) == nts::True);
        flipFlop.simulate(0);

        // Low to high -> change data
        setInputVal(clock, nts::True);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);

        // High to low
        setInputVal(clock, nts::False);
        setInputVal(data, nts::False);
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);

        // Low to high
        setInputVal(clock, nts::True);
        setInputVal(data, nts::Undefined);
        REQUIRE(flipFlop.compute(5) == nts::Undefined);
        REQUIRE(flipFlop.compute(6) == nts::Undefined);
        flipFlop.simulate(0);
    }

        // If clock goes from undefined to high  => data is undefined, except if the new data is same as before
        // If Clock goes from undefined to undef => data is undefined, except is the new data is same as before

    SUBCASE("Undefined clocks - low")
    {
        // Low to undefined -> data is not changed in this case
        setInputVal(clock, nts::Undefined);
        setInputVal(data, nts::False);
        REQUIRE(flipFlop.compute(5) == nts::False);
        REQUIRE(flipFlop.compute(6) == nts::True);
        flipFlop.simulate(0);

        // Undefined to low -> data is never changed
        setInputVal(clock, nts::False);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::False);
        REQUIRE(flipFlop.compute(6) == nts::True);
        flipFlop.simulate(0);

        // Low to undefined -> data is undefined in this case
        setInputVal(clock, nts::Undefined);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::Undefined);
        REQUIRE(flipFlop.compute(6) == nts::Undefined);
        flipFlop.simulate(0);

        // Undefined to low -> data is never changed
        setInputVal(clock, nts::False);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::Undefined);
        REQUIRE(flipFlop.compute(6) == nts::Undefined);
        flipFlop.simulate(0);
    }

    SUBCASE("Clocks - no changes")
    {
        // low to low -> data is not changed
        setInputVal(clock, nts::False);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::False);
        REQUIRE(flipFlop.compute(6) == nts::True);
        flipFlop.simulate(0);

        // low to high -> data is changed
        setInputVal(clock, nts::True);
        setInputVal(data, nts::True);
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);

        // High to high -> data is not changed
        setInputVal(clock, nts::True);
        setInputVal(data, nts::False);
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);

        // High to undefined -> data is not changed
        setInputVal(clock, nts::Undefined);
        setInputVal(data, nts::False);
        std::cout << flipFlop.compute(5) << " " << flipFlop.compute(6) << std::endl;
        REQUIRE(flipFlop.compute(5) == nts::True);
        REQUIRE(flipFlop.compute(6) == nts::False);
        flipFlop.simulate(0);
    }

    SUBCASE("UNDEFINED")
    {

    }
}
