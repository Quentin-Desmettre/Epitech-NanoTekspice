/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** NorComponent.cpp
*/

#include "NorComponent.hpp"

nts::NorComponent::NorComponent(const std::string& name):
    AElementaryComponent(name)
{
}

nts::Tristate nts::NorComponent::compute(nts::Tristate first, nts::Tristate second) const
{
    if (first == nts::True || second == nts::True) // True no matter what the other is
        return nts::False;
    if (first == nts::Undefined || second == nts::Undefined) // They're either false or undefined here; Undefined means undefined result
        return nts::Undefined;
    // None of them is True, neither Undefined, hence they're both False
    return nts::False;
}
