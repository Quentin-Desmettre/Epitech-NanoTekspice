/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** OutputComponent
*/

#ifndef OUTPUTCOMPONENT_HPP_
#define OUTPUTCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class OutputComponent: public AComponent<1, 0> {
        public:
            OutputComponent();
            ~OutputComponent() = default;

            void simulate(std::size_t tick) override;
            Tristate getValue() const;
            Tristate compute(std::size_t pin = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
            Tristate _value;
        private:
    };
} // namespace nts


#endif /* !OUTPUTCOMPONENT_HPP_ */
