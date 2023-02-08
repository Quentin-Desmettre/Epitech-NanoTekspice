/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"
#include "Errors.hpp"
#include <algorithm>

nts::ClockComponent::ClockComponent(std::string name) :
    InputComponent(name)
{
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    (void)tick;
    InputComponent::simulate(tick);
    if (_value == nts::Undefined)
        return;
    _nextValue = (_value == nts::True) ? nts::False : nts::True;
}
