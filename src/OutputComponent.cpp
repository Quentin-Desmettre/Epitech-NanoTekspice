/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"
#include "Errors.hpp"

nts::OutputComponent::OutputComponent():
    AComponent<1, 0>()
{
}

void nts::OutputComponent::simulate(std::size_t tick)
{
    (void)tick;
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError("OutputComponent::compute", "Pin does not exist");
    if (_input[0] == nullptr)
        _value = nts::Undefined;
    else
        _value = _input[0]->compute(0/*same TODO as below*/);
    return _value;
}

void nts::OutputComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin != 1)
        throw nts::PinError("OutputComponent::setLink", "Pin does not exist");
    _input[pin - 1] = &other; // TODO: tell that it is linked on a special pin
}
