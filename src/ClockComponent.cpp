/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"
#include "Errors.hpp"

nts::ClockComponent::ClockComponent():
    InputComponent()
{
}

nts::ClockComponent::~ClockComponent()
{
}

void nts::ClockComponent::invert()
{
    if (_value == nts::Undefined)
        return;
    _value = (_value == nts::True) ? nts::False : nts::True;
}

void nts::ClockComponent::setValue(nts::Tristate value)
{
    _nextValue = value;
}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::PinError("ClockComponent::compute", "Pin does not exist");
    if (_nextValue != _value)
        _value = _nextValue;
    return _value;
}
