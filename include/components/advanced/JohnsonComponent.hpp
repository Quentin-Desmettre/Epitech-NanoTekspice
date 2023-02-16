/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** JohnsonComponent
*/

#ifndef JOHNSONCOMPONENT_HPP_
#define JOHNSONCOMPONENT_HPP_
#include "AComponent.hpp"
#include <vector>
#include <algorithm>
namespace nts {
    class JohnsonComponent: public nts::AComponent<3, 11> {
        public:
            JohnsonComponent(const std::string &name);
            ~JohnsonComponent() = default;

            nts::Tristate compute(std::size_t pin = 1) override;
            void simulate(std::size_t tick) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
        private:
            nts::Tristate returnResult(std::size_t pin);
            void incValues();
            void addIndex();

            nts::Tristate _oldClock;
            nts::Tristate _newClock;
            nts::Tristate _oldDis, _newDis;
            std::vector<std::size_t> indexs;
            std::vector<std::size_t> oldIndexs;
            std::map<std::size_t, std::size_t> _pinToIndex;
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

#endif /* !JOHNSONCOMPONENT_HPP_ */
