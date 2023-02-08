/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** FalseComponent.cpp
*/

#include "FalseComponent.hpp"
#include "Errors.hpp"

nts::FalseComponent::FalseComponent(std::string name) :
    AComponent<0, 1>(name)
{
    _pinToPinType = {
        {1, nts::OUTPUT}
    };
}

void nts::FalseComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 1)
        throw nts::PinError(_name, "compute", pin);
    return nts::False;
}

void nts::FalseComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);

    _output[pin - 1].setComponent(&other);
    _output[pin - 1].setPin(otherPin);
}
