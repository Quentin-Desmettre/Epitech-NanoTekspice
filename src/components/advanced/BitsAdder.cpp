/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** BitsAdder
*/

#include "BitsAdder.hpp"
#include "SumComponent.hpp"

nts::BitsAdder::BitsAdder(const std::string &name):
    nts::AComplexComponent(name)
{
    auto sum13 = std::make_shared<SumComponent>(name + "_sum1");
    auto sum12 = std::make_shared<SumComponent>(name + "_sum2");
    auto sum11 = std::make_shared<SumComponent>(name + "_sum3");
    auto sum10 = std::make_shared<SumComponent>(name + "_sum4");

    // Internal links
    sum13->setLink(3, *sum12, 4);
    sum12->setLink(4, *sum13, 3);

    sum12->setLink(3, *sum11, 4);
    sum11->setLink(4, *sum12, 3);

    sum11->setLink(3, *sum10, 4);
    sum10->setLink(4, *sum11, 3);

    // Map to output pins
    _outputMap[14] = {4, sum13}; // My pin 14 is the pin 4 of the sum13 component
    _outputMap[13] = {5, sum13};
    _outputMap[12] = {5, sum12};
    _outputMap[11] = {5, sum11};
    _outputMap[10] = {5, sum10};

    // Map to input pins
    _inputMap[15] = {1, sum13}; // My pin 15 is the pin 1 of the sum13 component
    _inputMap[1] = {2, sum13};

    _inputMap[2] = {1, sum12};
    _inputMap[3] = {2, sum12};

    _inputMap[4] = {1, sum11};
    _inputMap[5] = {2, sum11};

    _inputMap[6] = {1, sum10};
    _inputMap[7] = {2, sum10};

    _inputMap[9] = {3, sum10};

    // Unused pins
    _unusedPins.push_back(8);
    _unusedPins.push_back(16);
}
