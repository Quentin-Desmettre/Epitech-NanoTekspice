/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** TrueComponent.cpp
*/

#include "TrueComponent.hpp"
#include "Errors.hpp"

nts::TrueComponent::TrueComponent(std::string name) :
    AComponent<0, 1>(name)
{
    _pinToPinType = {
        {1, nts::OUTPUT}
    };
}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 1)
        throw nts::PinError(_name, "compute", pin);
    return nts::True;
}

void nts::TrueComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);
    _output[pin - 1].setComponent(&other);
    _output[pin - 1].setPin(otherPin);
}
