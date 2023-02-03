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
            ClockComponent(std::string name);
            ~ClockComponent();

            static void switchClocks();
        private:
            void invert();
            static std::vector<ClockComponent *> _allClocks;
    };
} // namespace nts

#endif /* !CLOCKCOMPONENT_HPP_ */
