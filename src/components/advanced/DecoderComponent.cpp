/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** DecoderComponent
*/

#include "DecoderComponent.hpp"

nts::DecoderComponent::DecoderComponent(const std::string &name):
    nts::AComponent<8, 16>(name)
{
    _oldClock = nts::False;
    _newClock = nts::False;
    _pinToIndex = {
        {11, 0},
        {9, 1},
        {10, 2},
        {8, 3},
        {7, 4},
        {6, 5},
        {5, 6},
        {4, 7},
        {18, 8},
        {17, 9},
        {20, 10},
        {19, 11},
        {14, 12},
        {13, 13},
        {16, 14},
        {15, 15}
    };
    _pinToInput = {
        {2, 0},
        {3, 1},
        {21, 2},
        {22, 3},
        {1, 4},
        {23, 5},
        {12, 6},
        {14, 7}
    };
    oldValues.fill(nts::Undefined);
}

void nts::DecoderComponent::simulate(std::size_t tick)
{
    (void)tick;
    _oldClock = _newClock;
}

nts::Tristate nts::DecoderComponent::compute(std::size_t pin)
{
    std::size_t value = 0;

    if (_pinToIndex.find(pin) == _pinToIndex.end())
        return nts::Undefined;
    pin = _pinToIndex[pin];
    nts::Tristate
        clock = computeInput(4),
        inhibit = computeInput(5),
        tmp = nts::False
    ;
    _newClock = clock;
    if (clock == nts::True)
        for (int i = 0; i < 4; i++)
            oldValues[i] = computeInput(i);
    if (clock == nts::Undefined) {
        for (int i = 0; i < 4; i++) {
            tmp = computeInput(i);
            if (oldValues[i] != tmp)
                oldValues[i] = nts::Undefined;
        }
    }
    if (inhibit == nts::True)
        return nts::False;
    if (inhibit == nts::Undefined)
        return nts::Undefined;
    for (int i = 0; i < 4; i++)
        if (oldValues[i] == nts::Undefined)
            return nts::Undefined;
    for (int i = 0; i < 4; i++)
        value += oldValues[i] * (1 << i);
    if (value == pin)
        return nts::True;
    return nts::False;
}
#include <iostream>
void nts::DecoderComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (_pinToInput.find(pin) != _pinToInput.end()) {
        _input[_pinToInput[pin]].setComponent(&other);
        _input[_pinToInput[pin]].setPin(otherPin);
    } else if (_pinToIndex.find(pin) != _pinToIndex.end()) {
        _output[_pinToIndex[pin]].setComponent(&other);
        _output[_pinToIndex[pin]].setPin(otherPin);
    } else
        throw nts::PinError(_name, "setLink", pin);
}
