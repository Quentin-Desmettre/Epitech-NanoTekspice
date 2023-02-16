/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** JohnsonComponent
*/

#include "JohnsonComponent.hpp"
#include <iostream>

nts::JohnsonComponent::JohnsonComponent(const std::string &name):
    nts::AComponent<3, 11>(name)
{
    _oldClock = nts::False;
    _newClock = nts::False;
    indexs.push_back(0);
    _pinToIndex = {
        {3, 0},
        {2, 1},
        {4, 2},
        {7, 3},
        {10, 4},
        {1, 5},
        {5, 6},
        {6, 7},
        {9, 8},
        {11, 9},
        {12, 10}
    };
}

void nts::JohnsonComponent::simulate(std::size_t tick)
{
    (void)tick;
    _oldClock = _newClock;
    oldIndexs = indexs;
}

nts::Tristate nts::JohnsonComponent::compute(std::size_t pin)
{
    if (_pinToIndex.find(pin) == _pinToIndex.end())
        return nts::Undefined;
    pin = _pinToIndex[pin];
    nts::Tristate
        dis  = computeInput(0),
        clock = computeInput(1),
        reset   = computeInput(2)
    ;
    _newClock = clock;
    indexs = oldIndexs;
    if (dis == nts::True && reset != nts::True)
        return returnResult(pin);
    if (clock == nts::True) {
        if (dis == nts::False)
            incValues();
        else if (std::find(indexs.begin(), indexs.end(), pin) == indexs.end())
            addIndex();
    }
    if (clock == nts::Undefined) {
        addIndex();
    }
    if (reset == nts::Undefined && std::find(indexs.begin(), indexs.end(), 0) == indexs.end())
        indexs.push_back(0);
    if (reset == nts::True) {
        indexs.clear();
        indexs.push_back(0);
    }
    return returnResult(pin);
}

nts::Tristate nts::JohnsonComponent::returnResult(std::size_t pin)
{
    int carryOut = -2;

    if (pin == 10) {
        if (indexs.size() == 1) {
            return (indexs.front() < 5) ? nts::True : nts::False;
        }
        for (auto &it : indexs) {
            if (carryOut == -2)
                carryOut = it < 5;
            else if (carryOut != (it < 5))
                return nts::Undefined;
        }
        return (carryOut == 1) ? nts::True : nts::False;
    }
    if (std::find(indexs.begin(), indexs.end(), pin) == indexs.end())
        return nts::False;
    if (indexs.size() != 1) {
        return nts::Undefined;
    }
    return nts::True;
}

void nts::JohnsonComponent::incValues()
{
    for (size_t i = 0; i < indexs.size(); i++)
        indexs[i] = (indexs[i] + 1) % 10;
}

void nts::JohnsonComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 0 || pin > 16)
        throw nts::PinError(_name, "setLink", pin);
    if (pin >= 13 && pin <= 15) {
        _input[pin - 13].setComponent(&other);
        _input[pin - 13].setPin(otherPin);
    } else if (pin != 8 && pin != 16) {
        if (pin > 8)
            pin--;
        _output[pin - 1].setComponent(&other);
        _output[pin - 1].setPin(otherPin);
    }
}

void nts::JohnsonComponent::addIndex()
{
    size_t size = indexs.size();
    for (size_t i = 0; i < size; i++) {
        if (std::find(indexs.begin(), indexs.end(), (indexs[i] + 1) % 10) == indexs.end())
            indexs.push_back((indexs[i] + 1) % 10);
    }
}