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

            void setValue(nts::Tristate value) override;
            Tristate compute(std::size_t pin = 1) override;

            static void switchClocks();
        private:
            void invert();
            static std::vector<ClockComponent *> _allClocks;
            Tristate _nextValue;

    };
} // namespace nts

#endif /* !CLOCKCOMPONENT_HPP_ */
