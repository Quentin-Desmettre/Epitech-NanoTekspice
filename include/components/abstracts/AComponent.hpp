/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include "Errors.hpp"
#include <array>
#include <algorithm>

namespace nts
{
    template <size_t T1, size_t T2>
    class AComponent : public nts::IComponent {
        public:
            AComponent(std::string name):
                _name(name)
            {
                std::fill(_input.begin(), _input.end(), Pin{nullptr, 0});
                std::fill(_output.begin(), _output.end(), Pin{nullptr, 0});
            }
            virtual ~AComponent() = default;
            virtual void simulate(std::size_t tick) override {(void)tick;}
            std::string getName() const override { return _name; }

            static nts::Tristate inverseTristate(nts::Tristate state)
            {
                if (state == nts::True)
                    return nts::False;
                if (state == nts::False)
                    return nts::True;
                return nts::Undefined;
            }
        protected:
            nts::Tristate computeInput(std::size_t input) {
                if (input >= T1)
                    throw nts::PinError(_name, "computeInput", input);
                return _input[input].component ? _input[input].component->compute(_input[input].nb) : nts::Undefined;
            }
            std::array<Pin, T1> _input;
            std::array<Pin, T2> _output;
            std::string _name;
        private:
    };
}
#endif /* !ACOMPONENT_HPP_ */