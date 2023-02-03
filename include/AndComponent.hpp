/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AndComponent
*/

#ifndef ANDCOMPONENT_HPP_
#define ANDCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {

    class AndComponent: public AComponent<2, 1> {
        public:
            AndComponent(const std::string &name);
            ~AndComponent();

            nts::Tristate compute(std::size_t pin);
            virtual nts::Tristate compute(nts::Tristate first, nts::Tristate second);
            void setLink(std ::size_t pin, nts ::IComponent &other, std ::size_t otherPin);

        protected:
        private:
            nts::Tristate computeInput(std::size_t input);
    };

}

#endif /* !ANDCOMPONENT_HPP_ */
