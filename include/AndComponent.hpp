/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AndComponent
*/

#ifndef ANDCOMPONENT_HPP_
#define ANDCOMPONENT_HPP_
#include "AElementaryComponent.hpp"

namespace nts {

    class AndComponent: public AElementaryComponent {
        public:
            AndComponent(const std::string &name);
            ~AndComponent() = default;
        private:
            nts::Tristate compute(nts::Tristate first, nts::Tristate second) const override;
    };
}

#endif /* !ANDCOMPONENT_HPP_ */
