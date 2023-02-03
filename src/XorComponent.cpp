/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** XorComponent.cpp
*/

#include "XorComponent.hpp"

nts::XorComponent::XorComponent(const std::string& name):
    AElementaryComponent(name)
{
}

nts::Tristate nts::XorComponent::compute(nts::Tristate first, nts::Tristate second) const
{
    // Basic case
    if ((first == nts::True && second == nts::False) ||
        (first == nts::False && second == nts::True))
        return nts::True;
    // If one of them is undefined, the whole result is undefined, as it is possible that the undefined one is the same as the other
    if (first == nts::Undefined || second == nts::Undefined)
        return nts::Undefined;
    // None of them are undefined, and the result cannot be true: The result must be false
    return nts::False;
}
