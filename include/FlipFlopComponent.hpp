/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** FlipFlopComponent
*/

#ifndef FLIPFLOPCOMPONENT_HPP_
#define FLIPFLOPCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class FlipFlopComponent: public nts::AComponent<4, 2> {
        public:
            FlipFlopComponent(const std::string &name);
            ~FlipFlopComponent() = default;

            void simulate(std::size_t tick = 0) override;
            nts::Tristate compute(std::size_t pin = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
        private:
            nts::Tristate _oldClock, _newClock;
            nts::Tristate _data;
    };
}; // namespace nts


/*
         +---FlipFlop---+
         |              |
clock--1->              |
         |              |
 data--2->              >-5- Output
         |              |
  set--3->              >-6- Inverted output
         |              |
reset--4->              |
         |              |
         +--------------+
*/

#endif /* !FLIPFLOPCOMPONENT_HPP_ */
