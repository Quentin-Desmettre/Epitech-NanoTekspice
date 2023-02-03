/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_
#include "AComponent.hpp"
#include <exception>

namespace nts {
    class InputComponent: public AComponent<0, 1>
    {
        public:
            InputComponent(std::string name);
            ~InputComponent() = default;

            void setValue(nts::Tristate value);
            nts::Tristate getValue() const;
            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
            Tristate _value, _nextValue;
    };
};

std::ostream &operator<<(std::ostream &s, const nts::InputComponent &input);

#endif /* !INPUTCOMPONENT_HPP_ */
