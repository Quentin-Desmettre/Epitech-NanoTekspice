/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_BitsAdder.cpp
*/

#include "doctest.h"
#include "../include/BitsAdder.hpp"
#include "../include/SumComponent.hpp"
#include "../include/InputComponent.hpp"
#include <iostream>

static void setInputVal(nts::InputComponent &component, nts::Tristate value)
{
    component.setValue(value);
    component.simulate(0);
}

static void setBinaryValue(std::array<nts::InputComponent*, 4> component, int value)
{
    setInputVal(*(component[3]), (value & 0b1000) >> 3 ? nts::True : nts::False);
    setInputVal(*(component[2]), (value & 0b0100) >> 2 ? nts::True : nts::False);
    setInputVal(*(component[1]), (value & 0b0010) >> 1 ? nts::True : nts::False);
    setInputVal(*(component[0]), (value & 0b0001) >> 0 ? nts::True : nts::False);
}

static int getBinaryValue(std::array<nts::Tristate, 5> component)
{
    int value = 0;
    value += component[0] == nts::True ? 0b10000 : 0;
    value += component[1] == nts::True ? 0b01000 : 0;
    value += component[2] == nts::True ? 0b00100 : 0;
    value += component[3] == nts::True ? 0b00010 : 0;
    value += component[4] == nts::True ? 0b00001 : 0;
    return value;
}

TEST_CASE("BisAdder")
{
    // First, testing SumComponent
    nts::SumComponent sum("sum");

    // Basic
    REQUIRE(sum.getName() == "sum");
    REQUIRE(sum.compute(5) == nts::Undefined);
    REQUIRE(sum.compute(4) == nts::Undefined);

    // Linking
    nts::InputComponent a("in1");
    nts::InputComponent b("in2");
    nts::InputComponent carry("in3");
    REQUIRE_THROWS(sum.setLink(0, a, 1));
    REQUIRE_THROWS(sum.setLink(6, a, 1));
    REQUIRE_THROWS(sum.setLink(-1, a, 1));
    REQUIRE_NOTHROW(sum.setLink(1, a, 1));
    REQUIRE_NOTHROW(sum.setLink(2, b, 1));
    REQUIRE_NOTHROW(sum.setLink(3, carry, 1));
    REQUIRE(sum.compute(5) == nts::Undefined);
    REQUIRE(sum.compute(4) == nts::Undefined);

    // Check all truth table
    std::map<std::array<nts::Tristate, 3>, std::pair<nts::Tristate, nts::Tristate>> truthTable = {
        {{nts::False, nts::False, nts::False},     {nts::False, nts::False}},
        {{nts::False, nts::False, nts::True},      {nts::True, nts::False}},
        {{nts::False, nts::False, nts::Undefined}, {nts::Undefined, nts::False}},

        {{nts::False, nts::True, nts::False},     {nts::True, nts::False}},
        {{nts::False, nts::True, nts::True},      {nts::False, nts::True}},
        {{nts::False, nts::True, nts::Undefined}, {nts::Undefined, nts::Undefined}},

        {{nts::False, nts::Undefined, nts::False},     {nts::Undefined, nts::False}},
        {{nts::False, nts::Undefined, nts::True},      {nts::Undefined, nts::Undefined}},
        {{nts::False, nts::Undefined, nts::Undefined}, {nts::Undefined, nts::Undefined}},

        {{nts::True, nts::False, nts::False},     {nts::True, nts::False}},
        {{nts::True, nts::False, nts::True},      {nts::False, nts::True}},
        {{nts::True, nts::False, nts::Undefined}, {nts::Undefined, nts::Undefined}},

        {{nts::True, nts::True, nts::False},     {nts::False, nts::True}},
        {{nts::True, nts::True, nts::True},      {nts::True, nts::True}},
        {{nts::True, nts::True, nts::Undefined}, {nts::Undefined, nts::True}},

        {{nts::True, nts::Undefined, nts::False},     {nts::Undefined, nts::Undefined}},
        {{nts::True, nts::Undefined, nts::True},      {nts::Undefined, nts::True}},
        {{nts::True, nts::Undefined, nts::Undefined}, {nts::Undefined, nts::Undefined}},

        {{nts::Undefined, nts::False, nts::False}, {nts::Undefined, nts::False}},
        {{nts::Undefined, nts::False, nts::True}, {nts::Undefined, nts::Undefined}},
        {{nts::Undefined, nts::False, nts::Undefined}, {nts::Undefined, nts::Undefined}},

        {{nts::Undefined, nts::True, nts::False}, {nts::Undefined, nts::Undefined}},
        {{nts::Undefined, nts::True, nts::True}, {nts::Undefined, nts::True}},
        {{nts::Undefined, nts::True, nts::Undefined}, {nts::Undefined, nts::Undefined}},

        {{nts::Undefined, nts::Undefined, nts::False}, {nts::Undefined, nts::Undefined}},
        {{nts::Undefined, nts::Undefined, nts::True}, {nts::Undefined, nts::Undefined}},
        {{nts::Undefined, nts::Undefined, nts::Undefined}, {nts::Undefined, nts::Undefined}},
    };

    for (auto &entry : truthTable) {
        setInputVal(a, entry.first[0]);
        setInputVal(b, entry.first[1]);
        setInputVal(carry, entry.first[2]);
        REQUIRE(a.compute(1) == entry.first[0]);
        REQUIRE(b.compute(1) == entry.first[1]);
        REQUIRE(carry.compute(1) == entry.first[2]);
        REQUIRE(sum.compute(5) == entry.second.first);
        REQUIRE(sum.compute(4) == entry.second.second);
    }
    // Then, as SumComponent is good, testing BitsAdder
    nts::BitsAdder adder("adder");
    REQUIRE(adder.getName() == "adder");
    REQUIRE_THROWS(adder.setLink(0, a, 1));
    REQUIRE_THROWS(adder.setLink(17, a, 1));
    REQUIRE_THROWS(adder.setLink(-1, a, 1));
    REQUIRE(adder.compute(-1) == nts::Undefined);
    REQUIRE(adder.compute(14) == nts::Undefined);
    REQUIRE(adder.compute(13) == nts::Undefined);
    REQUIRE(adder.compute(12) == nts::Undefined);
    REQUIRE(adder.compute(11) == nts::Undefined);
    REQUIRE(adder.compute(10) == nts::Undefined);

    // Link inputs (a_1->a_4, b_1->b_4, carry)
    nts::InputComponent a1("a1"), a2("a2"), a3("a3"), a4("a4");
    nts::InputComponent b1("b1"), b2("b2"), b3("b3"), b4("b4");
    nts::InputComponent carryIn("carryIn");
    REQUIRE_NOTHROW(adder.setLink(7, a1, 1));
    REQUIRE_NOTHROW(adder.setLink(6, b1, 1));
    REQUIRE_NOTHROW(adder.setLink(5, a2, 1));
    REQUIRE_NOTHROW(adder.setLink(4, b2, 1));
    REQUIRE_NOTHROW(adder.setLink(3, a3, 1));
    REQUIRE_NOTHROW(adder.setLink(2, b3, 1));
    REQUIRE_NOTHROW(adder.setLink(1, a4, 1));
    REQUIRE_NOTHROW(adder.setLink(15, b4, 1));
    REQUIRE_NOTHROW(adder.setLink(9, carryIn, 1));

    // Test all possible numbers, from 0 to 15
    // (No need to check undefined values, because they are already tested in SumComponent)
    // (And, as SumCOmponent is good, we only have to check if BitsAdder correctly maps the values)
    for (int a = 0; a < 16; a++) {
        setBinaryValue({&a1, &a2, &a3, &a4}, a);
        for (int b = 0; b < 16; b++) {
            setBinaryValue({&b1, &b2, &b3, &b4}, b);
            for (int carry = 0; carry < 2; carry++) {
                setInputVal(carryIn, carry ? nts::True : nts::False);
                // Get binary value of the bits adder
                std::array<nts::Tristate, 5> sum = {
                    adder.compute(14),
                    adder.compute(13),
                    adder.compute(12),
                    adder.compute(11),
                    adder.compute(10)
                };
                // Get actual value of the bits adder
                int actual = getBinaryValue(sum);
                // Compute expected value
                int expected = a + b + carry;
                // Check if the value is correct
                REQUIRE(actual == expected);
            }
        }
    }
}
