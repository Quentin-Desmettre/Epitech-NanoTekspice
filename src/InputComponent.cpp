/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** InputComponent.cpp
*/

#include "InputComponent.hpp"
#include "Errors.hpp"

nts::InputComponent::InputComponent() :
    AComponent<0, 1>(),
    _value(nts::Undefined)
{
}

void nts::InputComponent::setValue(nts::Tristate value)
{
    _value = value;
}

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError("InputComponent::compute", "Pin does not exist");
    return _value;
}

void nts::InputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::PinError("InputComponent::setLink", "Pin does not exist");
    other.setLink(otherPin, *this, pin);
}
