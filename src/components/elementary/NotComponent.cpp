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
    _pinToPinType = {
        {1, nts::INPUT},
        {2, nts::OUTPUT}
    };
}

void nts::NotComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);

    if (pin == 2) {// Output pin
        _output[0].setComponent(&other);
        _output[0].setPin(otherPin);
    } else {
        _input[0].setComponent(&other);
        _input[0].setPin(otherPin);
    }
}

nts::Tristate nts::NotComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

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
