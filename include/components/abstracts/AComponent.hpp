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
#include <map>
#include <set>

namespace nts
{
    template <size_t T1, size_t T2>
    class AComponent : public nts::IComponent {
        public:
            AComponent(std::string name):
                _name(name)
            {
                std::fill(_input.begin(), _input.end(), Pin());
                std::fill(_output.begin(), _output.end(), Pin());
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
            virtual nts::PinType getPinType(std::size_t pin) const override
            {
                if (_pinToPinType.find(pin) != _pinToPinType.end())
                    return _pinToPinType.at(pin);
                return nts::ERROR;
            }
        protected:
            virtual nts::Tristate computeInput(std::size_t input) {
                if (input >= T1)
                    throw nts::PinError(_name, "computeInput", input);
                return _input[input].getComponent() ? _input[input].getComponent()->compute(_input[input].getPin()) : nts::Undefined;
            }
            std::array<Pin, T1> _input;
            std::array<Pin, T2> _output;
            std::set<std::size_t> _usedUnusedPins;
            std::vector<std::size_t> _unusedPins;
            std::map<std::size_t, nts::PinType> _pinToPinType;
            std::string _name;
    };
}
#endif /* !ACOMPONENT_HPP_ */
