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
}

void nts::FalseComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError(_name + "::compute", "Pin does not exist");
    return nts::False;
}

void nts::FalseComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::PinError(_name + "::setLink", "Pin does not exist");
    other.setLink(otherPin, *this, pin);
}
