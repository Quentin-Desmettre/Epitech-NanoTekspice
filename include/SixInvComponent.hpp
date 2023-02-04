/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SixInverter
*/

#ifndef SIXINVERTER_HPP_
#define SIXINVERTER_HPP_

#include "AComplexComponent.hpp"

namespace nts
{
    class SixInvComponent : public nts::AComplexComponent {
        public:
            SixInvComponent(std::string name);
            ~SixInvComponent() = default;
    };
}
#endif /* !SIXINVERTER_HPP_ */
