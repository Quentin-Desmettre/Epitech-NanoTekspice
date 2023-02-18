/*
** EPITECH PROJECT, 2023
** *
** File description:
** SelectorComponent
*/

#ifndef SELECTORCOMPONENT_HPP_
#define SELECTORCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class SelectorComponent: public AComponent<16, 1> {
        public:
            SelectorComponent(const std::string &name);
            ~SelectorComponent() = default;

            nts::Tristate compute(std::size_t pin);
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);

        protected:
        private:
            nts::Tristate computeInput(nts::Tristate a, nts::Tristate b, nts::Tristate c);

    };
}; // namespace nts

#endif /* !SELECTORCOMPONENT_HPP_ */
