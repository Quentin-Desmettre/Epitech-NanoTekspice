/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SelectorComponent.cpp
*/

#include "SelectorComponent.hpp"
#include "Errors.hpp"

nts::SelectorComponent::SelectorComponent(const std::string &name):
    AComponent<16, 1>(name)
{
    _pinToPinType = {
        {1, nts::INPUT},
        {2, nts::INPUT},
        {3, nts::INPUT},
        {4, nts::INPUT},
        {5, nts::INPUT},
        {6, nts::INPUT},
        {7, nts::INPUT},
        {8, nts::UNUSED},
        {9, nts::INPUT},
        {10, nts::INPUT},
        {11, nts::INPUT},
        {12, nts::INPUT},
        {13, nts::INPUT},
        {14, nts::OUTPUT},
        {15, nts::INPUT},
        {16, nts::UNUSED}
    };
}

nts::Tristate nts::SelectorComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 14)
        return nts::Undefined;
    nts::Tristate a = computeInput(10);
    nts::Tristate b = computeInput(11);
    nts::Tristate c = computeInput(12);
    nts::Tristate inhibit = computeInput(9);
    nts::Tristate enable = computeInput(14);

    if (inhibit == nts::True && enable == nts::False)
        return nts::False;
    if (inhibit == enable || enable == nts::Undefined || inhibit == nts::Undefined ||
    a == nts::Undefined || b == nts::Undefined || c == nts::Undefined)
        return nts::Undefined;

    // Here, enable is true ad inhibit is false
    // And, a, b and c are all defined
    // Get integer value of a, b and c
    int a_value = a == nts::True ? 1 : 0,
        b_value = b == nts::True ? 1 : 0,
        c_value = c == nts::True ? 1 : 0;
    // A: lowest bit, C: highest bit
    // int bit = a_value * 4 + b_value * 2 + c_value * 1;
    // C: lowest bit, A: highest bit
    int bit = a_value * 1 + b_value * 2 + c_value * 4;

    // Pin 8 is actually pin 9
    if (bit == 7)
        bit = 8;

    // Compute
    return computeInput(bit);
}

void nts::SelectorComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);
    if (getPinType(pin) == nts::UNUSED) {
        if (_usedUnusedPins.find(pin) == _usedUnusedPins.end()) {
            _usedUnusedPins.insert(pin);
            return;
        } else
            throw nts::PinError(_name, "setLink", pin);
    }
    if (pin == 14) {
        _output[0].setComponent(&other);
        _output[0].setPin(otherPin);
    } else {
        _input[pin - 1].setComponent(&other);
        _input[pin - 1].setPin(otherPin);
    }
}
