/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** XorComponent
*/

#ifndef XoRCOMPONENT_HPP_
#define XoRCOMPONENT_HPP_
#include "AElementaryComponent.hpp"

namespace nts {

    class XorComponent: public AElementaryComponent {
        public:
            XorComponent(const std::string &name);
            ~XorComponent() = default;
        private:
            nts::Tristate compute(nts::Tristate first, nts::Tristate second) const override;
    };

}

#endif /* !xorCOMPONENT_HPP_ */
