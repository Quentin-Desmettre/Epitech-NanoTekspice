/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** DualFlipFlop.cpp
*/

#include "DualFlipFlop.hpp"
#include "FlipFlopComponent.hpp"

nts::DualFlipFlop::DualFlipFlop(const std::string &name):
    AComplexComponent(name)
{
    FlipFlopComponent *flipFlop1 = new FlipFlopComponent(_name + "_flipFlop1");
    FlipFlopComponent *flipFlop2 = new FlipFlopComponent(_name + "_flipFlop2");

    // Map output
    _outputMap[1] = {5, flipFlop1};
    _outputMap[2] = {6, flipFlop1};
    _outputMap[13] = {5, flipFlop2};
    _outputMap[12] = {6, flipFlop2};

    // Map input
    _inputMap[3] = {1, flipFlop1}; // Clock
    _inputMap[5] = {2, flipFlop1}; // Data
    _inputMap[6] = {3, flipFlop1}; // Set
    _inputMap[4] = {4, flipFlop1}; // Reset

    _inputMap[11] = {1, flipFlop2}; // Clock
    _inputMap[9] =  {2, flipFlop2}; // Data
    _inputMap[8] =  {3, flipFlop2}; // Set
    _inputMap[10] = {4, flipFlop2}; // Reset
}
