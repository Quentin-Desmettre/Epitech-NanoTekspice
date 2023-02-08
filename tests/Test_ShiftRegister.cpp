/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_ShiftRegister.cpp
*/

#include "doctest.h"
#include "ShiftRegister.hpp"
#include "InputComponent.hpp"
#include <map>
#include <iostream>

static void setInputVal(nts::InputComponent &input, nts::Tristate val)
{
    input.setValue(val);
    input.simulate(1);
}

static void increaseCounter(nts::Tristate inputs[8], std::size_t pos = 0)
{
    if (pos == 8)
        return;
    if (inputs[pos] == nts::False) {
        inputs[pos] = nts::True;
        return;
    } else if (inputs[pos] == nts::True) {
        inputs[pos] = nts::Undefined;
    } else {
        inputs[pos] = nts::False;
        increaseCounter(inputs, pos + 1);
    }
}

static void randomFill(nts::Tristate inputs[8])
{
    for (int i = 0; i < 8; i++)
        inputs[i] = static_cast<nts::Tristate>(rand() % 3 - 1);
}

TEST_CASE("shift register")
{
    nts::ShiftRegister shiftRegister("shiftRegister");
    CHECK(shiftRegister.getName() == "shiftRegister");

    // Link inputs
    nts::InputComponent inputEnable("inputEnable");
    nts::InputComponent inputStrobe("inputStrobe");
    nts::InputComponent inputData("inputData");
    nts::InputComponent inputClock("inputClock");
    REQUIRE_NOTHROW(shiftRegister.setLink(1, inputStrobe, 1));
    REQUIRE_NOTHROW(shiftRegister.setLink(2, inputData, 1));
    REQUIRE_NOTHROW(shiftRegister.setLink(3, inputClock, 1));
    REQUIRE_NOTHROW(shiftRegister.setLink(15, inputEnable, 1));
    REQUIRE_THROWS(shiftRegister.setLink(1, inputStrobe, 1));
    REQUIRE_THROWS(shiftRegister.setLink(2, inputData, 1));
    REQUIRE_THROWS(shiftRegister.setLink(3, inputClock, 1));
    REQUIRE_THROWS(shiftRegister.setLink(15, inputEnable, 1));

    std::map<std::size_t, std::size_t> indexToPin = {
            {0, 4},
            {1, 5},
            {2, 6},
            {3, 7},
            {4, 14},
            {5, 13},
            {6, 12},
            {7, 11}
        };
    SUBCASE("Enable true, all possible combinations")
    {
        setInputVal(inputEnable, nts::True);
        nts::Tristate inputs[8] = {nts::False, nts::False, nts::False, nts::False, nts::False, nts::False, nts::False, nts::False};
        for (int _ = 0; _ < 6561 /* 3^8*/; _++) {
            setInputVal(inputStrobe, nts::True);
            // Feed the inputs
            for (int j = 0; j < 8; j++) {
                setInputVal(inputClock, nts::True);
                setInputVal(inputData, inputs[j]);
                // Temp compute, to update the clock
                shiftRegister.compute(9);
                shiftRegister.simulate(0);
                // Clock goes from 1 to 0 -> It updates the data
                setInputVal(inputClock, nts::False);
                REQUIRE(shiftRegister.compute(9) == nts::False);
                REQUIRE(shiftRegister.compute(10) == nts::True);
                shiftRegister.simulate(0);
            }
            // Flash data into inputs
            setInputVal(inputStrobe, nts::False);
            REQUIRE(shiftRegister.compute(9) == nts::False); // Clock not update, so data not changed
            REQUIRE(shiftRegister.compute(10) == nts::True);
            shiftRegister.simulate(0);

            // Fetch outputs
            for (int j = 7; j >= 0; j--) {
                REQUIRE(shiftRegister.compute(indexToPin[j]) == inputs[7 - j]);
            }

            // Reset inputs
            for (int j = 0; j < 8; j++) {
                setInputVal(inputClock, nts::True);
                setInputVal(inputData, nts::False);
                // Temp compute, to update the clock
                shiftRegister.compute(9);
                shiftRegister.simulate(0);
                // Clock goes from 1 to 0 -> It updates the data
                setInputVal(inputClock, nts::False);
                REQUIRE(shiftRegister.compute(9) == inputs[j]);
                REQUIRE(shiftRegister.compute(10) == ((inputs[j] == nts::True) ? nts::False : ((inputs[j] == nts::False) ? nts::True : nts::Undefined)));
                shiftRegister.simulate(0);
            }

            // Update combination
            increaseCounter(inputs);
        }
    }

    SUBCASE("Enable false, 10 random")
    {
        setInputVal(inputEnable, nts::False);
        nts::Tristate inputs[8];
        for (int _ = 0; _ < 10; _++) {
            randomFill(inputs);
            setInputVal(inputStrobe, nts::True);
            // Feed the inputs
            for (int j = 0; j < 8; j++) {
                setInputVal(inputClock, nts::True);
                setInputVal(inputData, inputs[j]);
                // Temp compute, to update the clock
                shiftRegister.compute(9);
                shiftRegister.simulate(0);
                // Clock goes from 1 to 0 -> It updates the data
                setInputVal(inputClock, nts::False);
                REQUIRE(shiftRegister.compute(9) == nts::False);
                REQUIRE(shiftRegister.compute(10) == nts::True);
                shiftRegister.simulate(0);
            }
            // Flash data into inputs
            setInputVal(inputStrobe, nts::False);
            REQUIRE(shiftRegister.compute(9) == nts::False); // Clock not update, so data not changed
            REQUIRE(shiftRegister.compute(10) == nts::True);
            shiftRegister.simulate(0);

            // Fetch outputs
            for (int j = 7; j >= 0; j--) {
                REQUIRE(shiftRegister.compute(indexToPin[j]) == nts::False);
            }

            // Reset inputs
            for (int j = 0; j < 8; j++) {
                setInputVal(inputClock, nts::True);
                setInputVal(inputData, nts::False);
                // Temp compute, to update the clock
                shiftRegister.compute(9);
                shiftRegister.simulate(0);
                // Clock goes from 1 to 0 -> It updates the data
                setInputVal(inputClock, nts::False);
                REQUIRE(shiftRegister.compute(9) == inputs[j]);
                REQUIRE(shiftRegister.compute(10) == ((inputs[j] == nts::True) ? nts::False : ((inputs[j] == nts::False) ? nts::True : nts::Undefined)));
                shiftRegister.simulate(0);
            }
        }
    }

    SUBCASE("Enable undefined, 10 random")
    {
        setInputVal(inputEnable, nts::Undefined);
        nts::Tristate inputs[8];
        for (int _ = 0; _ < 10; _++) {
            randomFill(inputs);
            setInputVal(inputStrobe, nts::True);
            // Feed the inputs
            for (int j = 0; j < 8; j++) {
                setInputVal(inputClock, nts::True);
                setInputVal(inputData, inputs[j]);
                // Temp compute, to update the clock
                shiftRegister.compute(9);
                shiftRegister.simulate(0);
                // Clock goes from 1 to 0 -> It updates the data
                setInputVal(inputClock, nts::False);
                REQUIRE(shiftRegister.compute(9) == nts::False);
                REQUIRE(shiftRegister.compute(10) == nts::True);
                shiftRegister.simulate(0);
            }
            // Flash data into inputs
            setInputVal(inputStrobe, nts::False);
            REQUIRE(shiftRegister.compute(9) == nts::False); // Clock not update, so data not changed
            REQUIRE(shiftRegister.compute(10) == nts::True);
            shiftRegister.simulate(0);

            // Fetch outputs
            for (int j = 7; j >= 0; j--) {
                nts::Tristate expected = (inputs[7 - j] == nts::False ? nts::False : nts::Undefined);
                REQUIRE(shiftRegister.compute(indexToPin[j]) == expected);
            }

            // Reset inputs
            for (int j = 0; j < 8; j++) {
                setInputVal(inputClock, nts::True);
                setInputVal(inputData, nts::False);
                // Temp compute, to update the clock
                shiftRegister.compute(9);
                shiftRegister.simulate(0);
                // Clock goes from 1 to 0 -> It updates the data
                setInputVal(inputClock, nts::False);
                REQUIRE(shiftRegister.compute(9) == inputs[j]);
                REQUIRE(shiftRegister.compute(10) == ((inputs[j] == nts::True) ? nts::False : ((inputs[j] == nts::False) ? nts::True : nts::Undefined)));
                shiftRegister.simulate(0);
            }
        }
    }
}
