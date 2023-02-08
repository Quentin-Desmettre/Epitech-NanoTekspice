/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** OrComponent
*/

#ifndef ORCOMPONENT_HPP_
#define ORCOMPONENT_HPP_
#include "AElementaryComponent.hpp"

namespace nts {

    class OrComponent: public AElementaryComponent {
        public:
            OrComponent(const std::string &name);
            ~OrComponent() = default;
        private:
            nts::Tristate compute(nts::Tristate first, nts::Tristate second) const override;
    };

}

#endif /* !OrCOMPONENT_HPP_ */
