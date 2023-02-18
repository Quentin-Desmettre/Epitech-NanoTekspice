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

/*

Inhibit | Enable | Behaviour
----------------------------
   0    |   0    | Normal
   0    |   1    | Absolute Undefined
   0    |   U    | Absolute Undefined
   1    |   0    | False
   1    |   1    | Absolute Undefined
   1    |   U    | Absolute Undefined
   U    |   0    | Undefined (if result should be false, it will be false, else undefined)
   U    |   1    | Absolute Undefined
   U    |   U    | Absolute Undefined

Absolute undefined if:
    Enable is true/undefined
False if:
    Inhibit is true and enable is false
Undefined if:
    Inhibit U, enable 0
Normale if:
    Inhibit 0, enable 0
*/

nts::Tristate nts::SelectorComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 14)
        return nts::Undefined;
    // Check enable
    nts::Tristate enable = AComponent::computeInput(14);
    if (enable == nts::Undefined || enable == nts::True)
        return nts::Undefined;

    // Check inhibit
    nts::Tristate inhibit = AComponent::computeInput(9);
    // From now on, enable is false.
    if (inhibit == nts::True)
        return nts::False;

    // Compute
    nts::Tristate a = AComponent::computeInput(10);
    nts::Tristate b = AComponent::computeInput(11);
    nts::Tristate c = AComponent::computeInput(12);

    // If inhibit is undefined:
    //    get the value of the pin.
    //    If it's false, return false.
    //    Else, return undefined.
    // Else, return the value of the pin.
    if (inhibit == nts::Undefined) {
        nts::Tristate value = computeInput(a, b, c);
        if (value == nts::False)
            return nts::False;
        return nts::Undefined;
    }
    return computeInput(a, b, c);
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

nts::Tristate nts::SelectorComponent::computeInput(nts::Tristate a, nts::Tristate b, nts::Tristate c)
{
    // First, get all the possible combinations of a, b, and c
    std::vector<int> combinA, combinB, combinC;
    const std::vector<int> bothState = {0, 1};

    combinA = (a == nts::Undefined ? bothState : std::vector<int>{int(a)});
    combinB = (b == nts::Undefined ? bothState : std::vector<int>{int(b)});
    combinC = (c == nts::Undefined ? bothState : std::vector<int>{int(c)});

    // Then, get all the possible values for all those combinations
    std::set<nts::Tristate> possibleValues;
    int bit;
    for (auto &intA : combinA) {
        for (auto &intB : combinB) {
            for (auto &intC : combinC) {
                bit = intA + intB * 2 + intC * 4;
                if (bit == 7)
                    bit = 8;
                possibleValues.insert(AComponent::computeInput(bit));
            }
        }
    }
    return possibleValues.size() > 1 ? nts::Undefined : *possibleValues.begin();
}
