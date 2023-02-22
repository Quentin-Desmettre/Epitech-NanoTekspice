/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_Ram.cpp
*/

#include "RandomAccess.hpp"
#include "doctest.h"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include <iostream>

void setInputValue(nts::InputComponent &input, nts::Tristate value)
{
    input.setValue(value);
    input.simulate(0);
}

void setAddress(nts::InputComponent addresses[10], std::size_t address)
{
    for (std::size_t i = 0; i < 10; i++) {
        setInputValue(addresses[i], nts::Tristate(address & (1 << i) ? 1 : 0));
    }
}

void setData(nts::InputComponent data[8], char value)
{
    for (std::size_t i = 0; i < 8; i++) {
        setInputValue(data[i], nts::Tristate(value & (1 << i) ? 1 : 0));
    }
}

TEST_CASE("Ram")
{
    nts::RandomAccess ram("ram");

    // Setup address pins
    nts::InputComponent address[10] = {
        nts::InputComponent("address0"),
        nts::InputComponent("address1"),
        nts::InputComponent("address2"),
        nts::InputComponent("address3"),
        nts::InputComponent("address4"),
        nts::InputComponent("address5"),
        nts::InputComponent("address6"),
        nts::InputComponent("address7"),
        nts::InputComponent("address8"),
        nts::InputComponent("address9")
    };
    ram.setLink(8, address[0], 1);
    ram.setLink(7, address[1], 1);
    ram.setLink(6, address[2], 1);
    ram.setLink(5, address[3], 1);
    ram.setLink(4, address[4], 1);
    ram.setLink(3, address[5], 1);
    ram.setLink(2, address[6], 1);
    ram.setLink(1, address[7], 1);
    ram.setLink(23, address[8], 1);
    ram.setLink(22, address[9], 1);

    // Setup enable, write, read
    nts::InputComponent enable("enable"), write("write"), read("read");
    ram.setLink(18, enable, 1);
    ram.setLink(21, write, 1);
    ram.setLink(20, read, 1);

    // Setup outputs
    nts::OutputComponent outputs[8] = {
        nts::OutputComponent("output0"),
        nts::OutputComponent("output1"),
        nts::OutputComponent("output2"),
        nts::OutputComponent("output3"),
        nts::OutputComponent("output4"),
        nts::OutputComponent("output5"),
        nts::OutputComponent("output6"),
        nts::OutputComponent("output7")
    };
    for (int i = 0; i < 8; i++) {
        std::size_t ramPin = (i >= 3 ? 10 : 9) + i;
        ram.setLink(ramPin, outputs[i], 1);
        outputs[i].setLink(1, ram, ramPin);
    }

    // Setup data inputs
    nts::InputComponent data[8] = {
        nts::InputComponent("data0"),
        nts::InputComponent("data1"),
        nts::InputComponent("data2"),
        nts::InputComponent("data3"),
        nts::InputComponent("data4"),
        nts::InputComponent("data5"),
        nts::InputComponent("data6"),
        nts::InputComponent("data7")
    };
    nts::InputComponent copyData[8] = {
        nts::InputComponent("data0"),
        nts::InputComponent("data1"),
        nts::InputComponent("data2"),
        nts::InputComponent("data3"),
        nts::InputComponent("data4"),
        nts::InputComponent("data5"),
        nts::InputComponent("data6"),
        nts::InputComponent("data7")
    };
    ram.setLink(9, data[0], 1);
    ram.setLink(10, data[1], 1);
    ram.setLink(11, data[2], 1);
    ram.setLink(13, data[3], 1);
    ram.setLink(14, data[4], 1);
    ram.setLink(15, data[5], 1);
    ram.setLink(16, data[6], 1);
    ram.setLink(17, data[7], 1);

    // Check memory is initialized to 0
    setInputValue(enable, nts::Tristate::False);
    setInputValue(write, nts::Tristate::True);
    setInputValue(read, nts::Tristate::False);
    for (std::size_t i = 0; i < 1024; i++) {
        setAddress(address, i);
        for (int j = 0; j < 8; j++) {
            REQUIRE(outputs[j].compute(1) == nts::Tristate::False);
        }
    }

    SUBCASE("Fill memory with random values")
    {
        // Write mode
        setInputValue(write, nts::Tristate::False);
        setInputValue(read, nts::Tristate::True);

        // Fill memory with random values
        std::vector<char> values;
        for (int i = 0; i < 1024; i++)
            values.push_back(random() % 256);

        // Write the values
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            setData(data, values[i]);
            setData(copyData, values[i]);
            for (int i = 0; i < 8; i++)
                REQUIRE(outputs[i].compute(1) == copyData[i].compute(1));
            ram.compute(nts::SIMULATOR_PIN);
        }

        // Get back the values
        setInputValue(write, nts::Tristate::True);
        setInputValue(read, nts::Tristate::False);
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            setData(copyData, values[i]);
            for (int i = 0; i < 8; i++)
                REQUIRE(outputs[i].compute(1) == copyData[i].compute(1));
            break;
        }
    }

    SUBCASE("Not enabled")
    {
        setInputValue(enable, nts::Tristate::True);
        setInputValue(write, nts::Tristate::False);
        setInputValue(read, nts::Tristate::False);
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            for (int j = 0; j < 8; j++) {
                REQUIRE(outputs[j].compute(1) == nts::Tristate::Undefined);
            }
        }
        setInputValue(write, nts::Tristate::False);
        setInputValue(read, nts::Tristate::True);
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            for (int j = 0; j < 8; j++) {
                REQUIRE(outputs[j].compute(1) == nts::Tristate::Undefined);
            }
        }
        setInputValue(write, nts::Tristate::True);
        setInputValue(read, nts::Tristate::False);
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            for (int j = 0; j < 8; j++) {
                REQUIRE(outputs[j].compute(1) == nts::Tristate::Undefined);
            }
        }
        setInputValue(write, nts::Tristate::True);
        setInputValue(read, nts::Tristate::True);
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            for (int j = 0; j < 8; j++) {
                REQUIRE(outputs[j].compute(1) == nts::Tristate::Undefined);
            }
        }
    }

    SUBCASE("Read and write enabled")
    {
        setInputValue(write, nts::Tristate::False);
        setInputValue(read, nts::Tristate::False);
        for (std::size_t i = 0; i < 1024; i++) {
            setAddress(address, i);
            for (int j = 0; j < 8; j++) {
                REQUIRE(outputs[j].compute(1) == nts::Tristate::Undefined);
            }
        }
    }
}