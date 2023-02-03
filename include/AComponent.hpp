/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <array>

namespace nts
{
    template <size_t T1, size_t T2>
    class AComponent : public nts::IComponent {
        public:
            AComponent();
            ~AComponent();
        protected:
            std::array<nts::IComponent *, T1> _input;
            std::array<nts::IComponent *, T2> _output;
        private:
    };
}
#endif /* !ACOMPONENT_HPP_ */
