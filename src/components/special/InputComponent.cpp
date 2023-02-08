/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** InputComponent.cpp
*/

#include "InputComponent.hpp"
#include "Errors.hpp"

nts::InputComponent::InputComponent(std::string name) :
    AComponent<0, 1>(name),
    _value(nts::Undefined),
    _nextValue(nts::Undefined)
{
}

void nts::InputComponent::setValue(nts::Tristate value)
{
    _nextValue = value;
}

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;
    _value = _nextValue;
}

nts::Tristate nts::InputComponent::getValue() const
{
    return _value;
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError(_name, "compute", pin);
    return _value;
}

void nts::InputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::PinError(_name, "setLink", pin);
    _output[pin - 1].component = &other;
    _output[pin - 1].nb = otherPin;
}
