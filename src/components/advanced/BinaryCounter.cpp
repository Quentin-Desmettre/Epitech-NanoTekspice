/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** BinaryCounter.cpp
*/

#include "BinaryCounter.hpp"
#include <iostream>

std::map<std::size_t, std::size_t> nts::BinaryCounter::_pinToBitIndex = {
    {9, 0},
    {7, 1},
    {6, 2},
    {5, 3},
    {3, 4},
    {2, 5},
    {4, 6},
    {13, 7},
    {12, 8},
    {14, 9},
    {15, 10},
    {1, 11}
};

nts::BinaryCounter::BinaryCounter(const std::string& name):
    nts::AComponent<4, 12>(name)
{
    std::fill(_bits.begin(), _bits.end(), nts::False);
    _newBits = _bits;
    _oldClock = nts::False;
    _newClock = nts::False;
}

void nts::BinaryCounter::simulate(std::size_t tick)
{
    (void)tick;
    _oldClock = _newClock;
    _bits = _newBits;
}

void nts::BinaryCounter::undefinedReset()
{
    for (std::size_t i = 0; i < _bits.size(); i++) {
        if (_newBits[i] != nts::False)
            _newBits[i] = nts::Undefined;
    }
}

void nts::BinaryCounter::increaseCounter(std::size_t bitIndex)
{
    if (bitIndex == 12)
        return;
    if (_newBits[bitIndex] == nts::False) {
        _newBits[bitIndex] = nts::True;
        return;
    } else if (_newBits[bitIndex] == nts::True) {
        _newBits[bitIndex] = nts::False;
        return increaseCounter(bitIndex + 1);
    } else if (bitIndex + 1 < 12) {
        if (_newBits[bitIndex + 1] == nts::Undefined)
            return increaseCounter(bitIndex + 1);
        _newBits[bitIndex + 1] = nts::Undefined;
    }
}

nts::Tristate nts::BinaryCounter::compute(std::size_t pin)
{
    nts::Tristate
        clock = computeInput(0),
        reset = computeInput(1)
    ;
    _newBits = _bits; // For safety issues

    if (reset == nts::True) {
        std::fill(_newBits.begin(), _newBits.end(), nts::False);
    }
    else if (reset == nts::Undefined || (_oldClock == nts::Undefined && clock != 1) || (_oldClock == nts::True && clock == nts::Undefined)) {
        undefinedReset();
    }
    else if (_oldClock == nts::True && clock == nts::False)
        increaseCounter();
    _newClock = clock;
    return _newBits[_pinToBitIndex[pin]];
}

void nts::BinaryCounter::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 10 || pin == 11) {
        _input[pin - 10].component = &other;
        _input[pin - 10].nb = otherPin;
    } else if (_pinToBitIndex.find(pin) != _pinToBitIndex.end()) {
        _output[_pinToBitIndex[pin]].component = &other;
        _output[_pinToBitIndex[pin]].nb = otherPin;
    } else
        throw nts::PinError(_name, "setLink", pin);
}