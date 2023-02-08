/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AElementaryComponent.cpp
*/

#include "AElementaryComponent.hpp"
#include "Errors.hpp"

nts::AElementaryComponent::AElementaryComponent(const std::string &name):
    AComponent<2, 1>(name)
{
    _pinToPinType = {
        {1, nts::INPUT},
        {2, nts::INPUT},
        {3, nts::OUTPUT}
    };
    // No Unused pins
}

void nts::AElementaryComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);

    if (pin == 3) { // Output pin
        _output[0].setComponent(&other);
        _output[0].setPin(otherPin);
    } else { // Input pins
        _input[pin - 1].setComponent(&other);
        _input[pin - 1].setPin(otherPin);
    }
}

nts::Tristate nts::AElementaryComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 3)
        throw nts::PinError(_name, "setLink", pin);
    nts::Tristate first = computeInput(0);
    nts::Tristate second = computeInput(1);

    return compute(first, second);
}
