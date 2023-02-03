/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"
#include "Errors.hpp"

std::vector<nts::ClockComponent *> nts::ClockComponent::_allClocks;

nts::ClockComponent::ClockComponent(std::string name) :
    InputComponent(name)
{
    _allClocks.push_back(this);
}

nts::ClockComponent::~ClockComponent()
{
    std::remove(_allClocks.begin(), _allClocks.end(), this);
}

void nts::ClockComponent::invert()
{
    if (_value == nts::Undefined)
        return;
    _nextValue = (_value == nts::True) ? nts::False : nts::True;
}

void nts::ClockComponent::switchClocks()
{
    for (auto &clock : _allClocks)
        clock->invert();
}
