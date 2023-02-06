/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SelectorComponent.cpp
*/

#include "SelectorComponent.hpp"
#include "Errors.hpp"

nts::SelectorComponent::SelectorComponent(const std::string &name):
    AComponent<16, 1>(name)
{
}

nts::Tristate nts::SelectorComponent::compute(std::size_t pin)
{
    if (pin != 14)
        return nts::Undefined;
    nts::Tristate a = computeInput(10);
    nts::Tristate b = computeInput(11);
    nts::Tristate c = computeInput(12);
    nts::Tristate inhibit = computeInput(9);
    nts::Tristate enable = computeInput(14);

    if (inhibit == enable || enable == nts::Undefined || inhibit == nts::Undefined ||
    a == nts::Undefined || b == nts::Undefined || c == nts::Undefined ||
    inhibit == nts::True || enable == nts::False)
        return nts::Undefined;

    // Here, enable is true ad inhibit is false
    // And, a, b and c are all defined
    // Get integer value of a, b and c
    int a_value = a == nts::True ? 1 : 0,
        b_value = b == nts::True ? 1 : 0,
        c_value = c == nts::True ? 1 : 0;
    // A: lowest bit, C: highest bit
    int bit = a_value * 4 + b_value * 2 + c_value * 1;
    // C: lowest bit, A: highest bit
    // int bit = a_value * 1 + b_value * 2 + c_value * 4;

    // Pin 8 is actually pin 9
    if (bit == 7)
        bit = 8;

    // Compute
    return computeInput(bit);
}

void nts::SelectorComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 8)
        return;
    if (pin == 0 || pin > 15)
        throw nts::PinError(_name, "setLink", pin);
    if (pin == 14) {
        _output[0].component = &other;
        _output[0].nb = otherPin;
    } else {
        _input[pin - 1].component = &other;
        _input[pin - 1].nb = otherPin;
    }
}
