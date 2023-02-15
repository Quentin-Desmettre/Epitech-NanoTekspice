/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** decoderComponent
*/

#ifndef DECODERCOMPONENT_HPP_
#define DECODERCOMPONENT_HPP_

#include "AComponent.hpp"
#include <vector>
#include <algorithm>

namespace nts {
    class DecoderComponent: public nts::AComponent<8, 16> {
        public:
            DecoderComponent(const std::string &name);
            ~DecoderComponent() = default;

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
            std::array<nts::Tristate, 4> oldValues;
            std::map<std::size_t, std::size_t> _pinToIndex;
            std::map<std::size_t, std::size_t> _pinToInput;
    };
}

#endif /* !DECODERCOMPONENT_HPP_ */
