/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SumComponent
*/

#ifndef SUMCOMPONENT_HPP_
#define SUMCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class SumComponent: public nts::AComponent<3, 2> {
    public:
        SumComponent(const std::string &name);
        ~SumComponent() = default;

        nts::Tristate compute(std::size_t pin) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

    protected:
    private:
        nts::Tristate computeSum(nts::Tristate first, nts::Tristate second, nts::Tristate carry);
        nts::Tristate computeCarry(nts::Tristate first, nts::Tristate second, nts::Tristate carry);
    };
}; // namespace nts

#endif /* !SUMCOMPONENT_HPP_ */
