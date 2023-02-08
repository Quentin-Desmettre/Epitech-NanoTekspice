/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** NandComponent
*/

#ifndef NANDCOMPONENT_HPP_
#define NANDCOMPONENT_HPP_
#include "AElementaryComponent.hpp"

namespace nts {

    class NandComponent: public AElementaryComponent {
        public:
            NandComponent(const std::string &name);
            ~NandComponent() = default;
        private:
            nts::Tristate compute(nts::Tristate first, nts::Tristate second) const override;
    };
}

#endif /* !NANDCOMPONENT_HPP_ */
