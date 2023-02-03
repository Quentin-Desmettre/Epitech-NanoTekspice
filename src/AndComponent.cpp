/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AndComponent
*/

#include "AndComponent.hpp"
#include "Errors.hpp"

nts::AndComponent::AndComponent(const std::string& name):
    AComponent<2, 1>(name)
{
}

void nts::AndComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin < 1 || pin > 3)
        throw nts::PinError(_name + "::setLink", "Pin " + std::to_string(pin) + " does not exist");
    if (pin == 3) // Output pin
        other.setLink(otherPin, *this, pin);
    _input[pin - 1].component = &other;
    _input[pin - 1].nb = otherPin;
}

nts::Tristate nts::AndComponent::computeInput(std::size_t input)
{
    if (input >= 2)
        return nts::Undefined;
    return _input[input].component ? _input[input].component->compute(_input[input].nb) : nts::Undefined;
}

nts::Tristate nts::AndComponent::compute(nts::Tristate first, nts::Tristate second)
{
    if (first == nts::False || second == nts::False) // False not matter what the other is
        return nts::False;
    if (first == nts::Undefined || second == nts::Undefined) // They're either true or undefined here
        return nts::Undefined;
    // None of them is False, neither Undefined, hence they're both True
    return nts::True;
}

nts::Tristate nts::AndComponent::compute(std::size_t pin)
{
    if (pin != 3)
        throw nts::PinError(_name + "::setLink", "Pin " + std::to_string(pin) + " does not exist");
    nts::Tristate first = computeInput(0);
    nts::Tristate second = computeInput(1);

    return AndComponent::compute(first, second);
}
