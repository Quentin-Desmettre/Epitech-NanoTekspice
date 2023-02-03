/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_
#include "InputComponent.hpp"

namespace nts {
    class ClockComponent : public InputComponent {
        public:
            ClockComponent();
            ~ClockComponent();

            void invert();
            void setValue(nts::Tristate value) override;
            Tristate compute(std::size_t pin = 1) override;
        private:
            Tristate _nextValue;

    };
} // namespace nts

#endif /* !CLOCKCOMPONENT_HPP_ */
