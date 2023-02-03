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
}

void nts::TrueComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError(_name + "::compute", "Pin does not exist");
    return nts::True;
}

void nts::TrueComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::PinError(_name + "::setLink", "Pin does not exist");
    other.setLink(otherPin, *this, pin);
}
