/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AComplexComponent
*/

#ifndef ACOMPLEXCOMPONENT_HPP_
#define ACOMPLEXCOMPONENT_HPP_
#include "AComponent.hpp"
#include <map>

// A component that contains other components
namespace nts {
    class AComplexComponent: public nts::AComponent<0, 0> {
        public:
            AComplexComponent(const std::string &name);
            ~AComplexComponent() = default;

            void simulate(std::size_t tick) override;
            nts::Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            nts::PinType getPinType(std::size_t pin) const override;

        protected:
            // Map an output pin (13, 12, 11, 10) to an internal component and it's associated pin
            std::map<std::size_t, std::pair<std::size_t, SharedIComponent>> _outputMap;
            // Map an input pinto an internal component and it's associated pin
            std::map<std::size_t, std::pair<std::size_t, SharedIComponent>> _inputMap;
            // Map an unused pin to an internal component and it's associated pin
            std::map<std::size_t, std::pair<std::size_t, SharedIComponent>> _unusedMap;
            // Unused pins
            std::vector<std::size_t> _unusedPins;
    };
}; // namespace nts

#endif /* !ACOMPLEXCOMPONENT_HPP_ */
