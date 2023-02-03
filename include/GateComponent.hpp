/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** GateComponent
*/

#ifndef GATECOMPONENT_HPP_
#define GATECOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts
{
    template <typename T>
    class GateComponent : public nts::IComponent {
        public:
            AComponent();
            ~AComponent();
            nts::Tristate compute(std ::size_t pin) {
                if (pin == 7 || pin == 14) {

                }

            }
        protected:
            std::map<T *, 4> _components;
        private:
    };  
}
#endif /* !GATECOMPONENT_HPP_ */
