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

    _pinToPinType = {
        {1, nts::INPUT},
        {2, nts::INPUT},
        {3, nts::INPUT},
        {4, nts::INPUT},
        {5, nts::INPUT},
        {6, nts::INPUT},
        {7, nts::INPUT},
        {8, nts::INPUT},
        {9, nts::INPUT},
        {10, nts::INPUT}
    };
}

nts::Tristate nts::LoggerComponent::compute(std::size_t pin)
{
    char c = 0;
    (void)pin;
    if (_input[8].getComponent() == nullptr || _input[8].getComponent()->compute(_input[8].getPin()) != nts::True || _oldClock != nts::False) {
        if (_input[8].getComponent() != nullptr)
            _oldClock = _input[8].getComponent()->compute(_input[8].getPin());
        else
            _oldClock = nts::Undefined;
        return nts::False;
    }
    for (size_t i = 0; i < 8; i++) {
        if (_input[i].getComponent() == nullptr)
            return nts::False;
        if (_input[i].getComponent()->compute(_input[i].getPin()) == nts::True)
            c |= 1 << i;
        else if (_input[i].getComponent()->compute(_input[i].getPin()) == nts::Undefined)
            return nts::False;
    }
    _oldClock = nts::True;
    if (_input[9].getComponent() == nullptr || _input[9].getComponent()->compute(_input[9].getPin()) == nts::True)
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
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);
    _input[pin - 1].setComponent(&other);
    _input[pin - 1].setPin(otherPin);
}
