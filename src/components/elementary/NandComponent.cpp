/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** NandComponent
*/

#include "NandComponent.hpp"
#include "Errors.hpp"

nts::NandComponent::NandComponent(const std::string& name):
    AElementaryComponent(name)
{
}

nts::Tristate nts::NandComponent::compute(nts::Tristate first, nts::Tristate second) const
{
    if (first == nts::False || second == nts::False) // False not matter what the other is
        return nts::True;
    if (first == nts::Undefined || second == nts::Undefined) // They're either true or undefined here
        return nts::Undefined;
    // None of them is False, neither Undefined, hence they're both True
    return nts::False;
}
