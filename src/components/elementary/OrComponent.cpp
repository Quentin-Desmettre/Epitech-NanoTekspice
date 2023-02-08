/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** OrComponent.cpp
*/

#include "OrComponent.hpp"

nts::OrComponent::OrComponent(const std::string& name):
    AElementaryComponent(name)
{
}

nts::Tristate nts::OrComponent::compute(nts::Tristate first, nts::Tristate second) const
{
    if (first == nts::True || second == nts::True) // True no matter what the other is
        return nts::True;
    if (first == nts::Undefined || second == nts::Undefined) // They're either false or undefined here; Undefined means undefined result
        return nts::Undefined;
    // None of them is True, neither Undefined, hence they're both False
    return nts::False;
}
