/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AElementaryComponent
*/

#ifndef AELEMENTARYCOMPONENT_HPP_
#define AELEMENTARYCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class AElementaryComponent: public AComponent<2, 1> {
        public:
            AElementaryComponent(const std::string &name);
            virtual ~AElementaryComponent() = default;

            nts::Tristate compute(std::size_t pin);
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);

        private:
            virtual nts::Tristate compute(nts::Tristate first, nts::Tristate second) const = 0;
    };
}

#endif /* !AELEMENTARYCOMPONENT_HPP_ */
