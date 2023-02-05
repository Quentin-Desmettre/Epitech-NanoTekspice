/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SixInvComponent
*/

#include "SixInvComponent.hpp"
#include "NotComponent.hpp"
#include "ComponentFactory.hpp"

nts::SixInvComponent::SixInvComponent(std::string name):
    AComplexComponent(name)
{
    // Output pins
    _outputMap[2] = {2, std::make_shared<NotComponent>(name + "-intern1")};
    _outputMap[4] = {2, std::make_shared<NotComponent>(name + "-intern2")};
    _outputMap[6] = {2, std::make_shared<NotComponent>(name + "-intern3")};
    _outputMap[8] = {2, std::make_shared<NotComponent>(name + "-intern4")};
    _outputMap[10] = {2, std::make_shared<NotComponent>(name + "-intern5")};
    _outputMap[12] = {2, std::make_shared<NotComponent>(name + "-intern6")};

    // Input pins
    _inputMap[1] = {1, _outputMap[2].second};
    _inputMap[3] = {1, _outputMap[4].second};
    _inputMap[5] = {1, _outputMap[6].second};
    _inputMap[9] = {1, _outputMap[8].second};
    _inputMap[11] = {1, _outputMap[10].second};
    _inputMap[13] = {1, _outputMap[12].second};

    // Unused pins
    _unusedPins.push_back(7);
    _unusedPins.push_back(14);
}
