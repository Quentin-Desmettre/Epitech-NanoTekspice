/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AComplexComponent
*/

#include "AComplexComponent.hpp"
#include <set>

nts::AComplexComponent::AComplexComponent(const std::string &name):
    AComponent<0, 0>(name)
{
}

void nts::AComplexComponent::simulate(std::size_t tick)
{
    // Get unique components
    std::set<IComponent *> uniqueComponents;
    for (auto &it: _inputMap)
        uniqueComponents.insert(it.second.second.get());
    for (auto &it: _outputMap)
        uniqueComponents.insert(it.second.second.get());

    // Simulate all components
    for (auto &it: uniqueComponents)
        it->simulate(tick);
}

nts::Tristate nts::AComplexComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;
    return _outputMap[pin].second->compute(_outputMap[pin].first);
}

nts::PinType nts::AComplexComponent::getPinType(std::size_t pin) const
{
    if (_inputMap.find(pin) != _inputMap.end())
        return nts::INPUT;
    if (_outputMap.find(pin) != _outputMap.end())
        return nts::OUTPUT;
    if (std::find(_unusedPins.begin(), _unusedPins.end(), pin) != _unusedPins.end())
        return nts::UNUSED;
    return nts::ERROR;
}

#include <iostream>

void nts::AComplexComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);

    if (_unusedMap.find(pin) != _unusedMap.end()) {
        _unusedMap[pin].second->setLink(_unusedMap[pin].first, other, otherPin);
        return;
    }
    if (_inputMap.find(pin) != _inputMap.end()) {
        _inputMap[pin].second->setLink(_inputMap[pin].first, other, otherPin);
        return;
    }
    _outputMap[pin].second->setLink(_outputMap[pin].first, other, otherPin);
}
