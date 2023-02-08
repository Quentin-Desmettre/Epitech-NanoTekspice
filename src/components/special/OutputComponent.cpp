/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"
#include "Errors.hpp"
#include <iostream>

nts::OutputComponent::OutputComponent(std::string name) :
    AComponent<1, 0>(name),
    _value(nts::Undefined)
{
    _pinToPinType = {
        {1, nts::INPUT}
    };
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::INPUT)
        return nts::Undefined;

    if (pin != 1)
        throw nts::PinError(_name, "compute", pin);
    if (_input[0].getComponent() == nullptr)
        _value = nts::Undefined;
    else
        _value = _input[0].getComponent()->compute(_input[0].getPin());
    return _value;
}

nts::Tristate nts::OutputComponent::getValue() const
{
    return _value;
}

void nts::OutputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);
    _input[pin - 1].setComponent(&other);
    _input[pin - 1].setPin(otherPin);
}
