/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** LoggerComponent
*/

#include "LoggerComponent.hpp"
#include <fstream>
#include <iostream>
#include <string>

nts::LoggerComponent::LoggerComponent(std::string name) :
    AComponent<10, 0>(name)
{
    _oldClock = nts::False;
}

nts::Tristate nts::LoggerComponent::compute(std::size_t pin)
{
    char c = 0;
    (void)pin;
    if (_input[8].component == nullptr || _input[8].component->compute(_input[8].nb) != nts::True || _oldClock != nts::False) {
        if (_input[8].component != nullptr)
            _oldClock = _input[8].component->compute(_input[8].nb);
        else
            _oldClock = nts::Undefined;
        return nts::False;
    }
    for (size_t i = 0; i < 8; i++) {
        if (_input[i].component == nullptr)
            return nts::False;
        if (_input[i].component->compute(_input[i].nb) == nts::True)
            c |= 1 << i;
        else if (_input[i].component->compute(_input[i].nb) == nts::Undefined)
            return nts::False;
    }
    _oldClock = nts::True;
    if (_input[9].component == nullptr || _input[9].component->compute(_input[9].nb) == nts::True)
        return nts::False;
    std::ofstream file("log.bin", std::ios::in | std::ios::app);
    if (file) {
        file << std::string(1, c);
        file.close();
    }
    return nts::True;
}

void nts::LoggerComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin < 1 || pin > 10)
        throw nts::PinError(_name, "setLink", pin);
    _input[pin - 1].component = &other;
    _input[pin - 1].nb = otherPin;
}
