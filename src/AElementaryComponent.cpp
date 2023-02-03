/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AElementaryComponent.cpp
*/

#include "AElementaryComponent.hpp"
#include "Errors.hpp"

nts::AElementaryComponent::~AElementaryComponent() {}

nts::AElementaryComponent::AElementaryComponent(const std::string &name):
    AComponent<2, 1>(name)
{
}

void nts::AElementaryComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin < 1 || pin > 3)
        throw nts::PinError(_name + "::setLink", "Pin " + std::to_string(pin) + " does not exist");
    if (pin == 3) // Output pin
        other.setLink(otherPin, *this, pin);
    _input[pin - 1].component = &other;
    _input[pin - 1].nb = otherPin;
}

nts::Tristate nts::AElementaryComponent::computeInput(std::size_t input)
{
    if (input >= 2)
        return nts::Undefined;
    return _input[input].component ? _input[input].component->compute(_input[input].nb) : nts::Undefined;
}

nts::Tristate nts::AElementaryComponent::compute(std::size_t pin)
{
    if (pin != 3)
        throw nts::PinError(_name + "::setLink", "Pin " + std::to_string(pin) + " does not exist");
    nts::Tristate first = computeInput(0);
    nts::Tristate second = computeInput(1);

    return AElementaryComponent::compute(first, second);
}
