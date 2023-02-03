/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"
#include "Errors.hpp"

nts::OutputComponent::OutputComponent(std::string name) :
    AComponent<1, 0>(name)
{
}

void nts::OutputComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError(_name + "::compute", "Pin does not exist");
    if (_input[0].component == nullptr)
        _value = nts::Undefined;
    else
        _value = _input[0].component->compute(0/*same TODO as below*/);
    return _value;
}

nts::Tristate nts::OutputComponent::getValue() const
{
    return _value;
}

void nts::OutputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::PinError(_name + "::setLink", "Pin does not exist");
    _input[pin - 1].component = &other;
    _input[pin - 1].nb = otherPin;
}
