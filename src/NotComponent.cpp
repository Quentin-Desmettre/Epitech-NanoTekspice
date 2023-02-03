/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** NotComponent.cpp
*/

#include "NotComponent.hpp"
#include "Errors.hpp"

nts::NotComponent::NotComponent(const std::string &name):
    AComponent<1, 1>(name)
{
}

void nts::NotComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin < 1 || pin > 2)
        throw nts::PinError(_name, "setLink", pin);
    if (pin == 2) {// Output pin
        _output[0].component = &other;
        _output[0].nb = otherPin;
    } else {
        _input[0].component = &other;
        _input[0].nb = otherPin;
    }
}

nts::Tristate nts::NotComponent::computeInput(std::size_t input)
{
    if (input >= 1)
        return nts::Undefined;
    return _input[input].component ? _input[input].component->compute(_input[input].nb) : nts::Undefined;
}

nts::Tristate nts::NotComponent::compute(std::size_t pin)
{
    if (pin != 2)
        throw nts::PinError(_name, "setLink", pin);
    nts::Tristate first = computeInput(0);

    return resolve(first);
}

nts::Tristate nts::NotComponent::resolve(nts::Tristate first) const
{
    if (first == nts::Undefined)
        return nts::Undefined;
    return first == nts::True ? nts::False : nts::True;
}
