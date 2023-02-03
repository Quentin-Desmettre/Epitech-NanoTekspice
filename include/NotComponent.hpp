/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** NotComponent
*/

#ifndef NOTCOMPONENT_HPP_
#define NOTCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class NotComponent: public AComponent<1, 1> {
         public:
            NotComponent(const std::string &name);
            virtual ~NotComponent() = default;

            nts::Tristate compute(std::size_t pin);
            void setLink(std ::size_t pin, nts ::IComponent &other, std ::size_t otherPin);

        private:
            nts::Tristate computeInput(std::size_t input);
            nts::Tristate resolve(nts::Tristate first) const;
    };
};

#endif /* !NOTCOMPONENT_HPP_ */
