/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** NorComponent
*/

#ifndef NORCOMPONENT_HPP_
#define NORCOMPONENT_HPP_
#include "AElementaryComponent.hpp"

namespace nts {

    class NorComponent: public AElementaryComponent {
        public:
            NorComponent(const std::string &name);
            ~NorComponent() = default;
        private:
            nts::Tristate compute(nts::Tristate first, nts::Tristate second) const override;
    };

}

#endif /* NOrCOMPONENT_HPP_ */
