/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SumComponent
*/

#include "SumComponent.hpp"

nts::SumComponent::SumComponent(const std::string &name):
    nts::AComponent<3, 2>(name)
{
}

nts::Tristate nts::SumComponent::compute(std::size_t pin)
{
    if (pin != 4 && pin != 5)
        return nts::Undefined;

    nts::Tristate first = computeInput(0);
    nts::Tristate second = computeInput(1);
    nts::Tristate carry = computeInput(2);

    if (pin == 5) // Compute sum
        return computeSum(first, second, carry);
    // Pin must be 4 -> Compute carry
    return computeCarry(first, second, carry);
}

void nts::SumComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 1 || pin == 2 || pin == 3) // Inputs
        _input[pin - 1] = {&other, otherPin};
    else if (pin == 4 || pin == 5) // Outputs
        _output[pin - 4] = {&other, otherPin};
    else
        throw nts::PinError(_name, "setLink", pin);
}

nts::Tristate nts::SumComponent::computeSum(nts::Tristate first, nts::Tristate second, nts::Tristate carry)
{
    // If one of them is undefined, the sum is undefined
    if (first == nts::Undefined || second == nts::Undefined || carry == nts::Undefined)
        return nts::Undefined;
    // From here, none of them is undefined.
    // Different cases:
    // 0 or 2 are True -> return False
    // 1 or 3 are True -> return True
    std::array<nts::Tristate, 3> elems{first, second, carry};
    std::size_t nbTrue = std::count(elems.begin(), elems.end(), nts::True);
    if (nbTrue == 0 || nbTrue == 2)
        return nts::False;
    else
        return nts::True;
}
nts::Tristate nts::SumComponent::computeCarry(nts::Tristate first, nts::Tristate second, nts::Tristate carry)
{
    std::array<nts::Tristate, 3> elems{first, second, carry};
    std::size_t nbFalse = std::count(elems.begin(), elems.end(), nts::False);
    std::size_t nbTrue = std::count(elems.begin(), elems.end(), nts::True);

    // 2 of them are 0 -> carry 0
    if (nbFalse == 2)
        return nts::False;
    // 2 or more are 1 -> carry 1
    if (nbTrue >= 2)
        return nts::True;
    // Any other case -> carry undefined
    return nts::Undefined;
}
