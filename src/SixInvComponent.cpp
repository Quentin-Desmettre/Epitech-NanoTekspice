/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SixInvComponent
*/

#include "SixInvComponent.hpp"

nts::SixInvComponent::SixInvComponent(std::string name):
    AComponent<6, 6>(name)
{
    _componentForOutputPin[2] = {2, new NotComponent(name + "-intern1")};
    _componentForOutputPin[4] = {2, new NotComponent(name + "-intern2")};
    _componentForOutputPin[6] = {2, new NotComponent(name + "-intern3")};
    _componentForOutputPin[8] = {2, new NotComponent(name + "-intern4")};
    _componentForOutputPin[10] = {2, new NotComponent(name + "-intern5")};
    _componentForOutputPin[12] = {2, new NotComponent(name + "-intern6")};

    _componentForInputPin[1] = {1, _componentForOutputPin[2].second};
    _componentForInputPin[3] = {1, _componentForOutputPin[4].second};
    _componentForInputPin[5] = {1, _componentForOutputPin[6].second};
    _componentForInputPin[9] = {1, _componentForOutputPin[8].second};
    _componentForInputPin[11] = {1, _componentForOutputPin[10].second};
    _componentForInputPin[13] = {1, _componentForOutputPin[12].second};
}

nts::SixInvComponent::~SixInvComponent()
{
    for (auto &it : _componentForOutputPin)
        delete it.second.second;
};