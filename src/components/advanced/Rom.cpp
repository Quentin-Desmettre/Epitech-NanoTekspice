/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Rom
*/

#include "Rom.hpp"

nts::RomComponent::RomComponent(const std::string &name):
    nts::AComponent<17, 8>(name)
{
    _pinToIndex = {
        {8, 0},
        {7, 1},
        {6, 2},
        {5, 3},
        {4, 4},
        {3, 5},
        {2, 6},
        {1, 7},
        {23, 8},
        {22, 9},
        {19, 10},
        {18, 11},
        {20, 12},
        {12, 13},
        {25, 14},
        {24, 15},
        {21, 16},
    };
}


void nts::RomComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 0 || pin > 25)
        throw nts::PinError(_name, "setLink", pin);
    if (pin >= 9 && pin <= 17 && pin != 12) {
        if (pin > 12)
            pin--;
        _output[pin - 9].setComponent(&other);
        _output[pin - 9].setPin(otherPin);
    } else {
        pin = _pinToIndex[pin];
        _input[pin].setComponent(&other);
        _input[pin].setPin(otherPin);
    }
}

nts::Tristate nts::RomComponent::compute(std::size_t pin)
{
    nts::Tristate tmp;
    long int index = 0;
    nts::Tristate enable = computeInput(11);
    nts::Tristate read = computeInput(12);

    if (read != nts::False || enable != nts::False)
        return nts::Undefined;
    if (getPinType(pin) == nts::PinType::UNUSED)
        return nts::Undefined;
    if (pin > 12)
        pin--;
    pin -= 9;
    for (int i = 0; i <= 10; i++) {
        tmp = computeInput(i);
        if (tmp == nts::Undefined)
            return nts::Undefined;
        index += tmp * (1 << i);
    }
    std::ifstream file("./rom.bin", std::ios::in | std::ios::binary);
    if (!file)
        return nts::Undefined;
    char c;
    for (int i = 0; i <= index; i++) {
        if (file.read(&c, 1).eof())
            return nts::Undefined;
    }
    c >>= pin;
    c &= 1;
    return (nts::Tristate)c;
}