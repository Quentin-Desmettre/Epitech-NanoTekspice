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
    if (_outputMap.find(pin) == _outputMap.end())
        return nts::Undefined;
    return _outputMap[pin].second->compute(_outputMap[pin].first);
}

void nts::AComplexComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (_inputMap.find(pin) != _inputMap.end()) {
        _inputMap[pin].second->setLink(_inputMap[pin].first, other, otherPin);
        return;
    }
    if (_outputMap.find(pin) != _outputMap.end()) {
        _outputMap[pin].second->setLink(_outputMap[pin].first, other, otherPin);
        return;
    }
    if (std::find(_unusedPins.begin(), _unusedPins.end(), pin) != _unusedPins.end())
        return;
    throw nts::PinError(_name, "setLink", pin);
}
