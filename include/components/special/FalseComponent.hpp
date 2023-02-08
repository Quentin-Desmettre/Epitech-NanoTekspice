/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** FalseComponent
*/

#ifndef FALSECOMPONENT_HPP_
#define FALSECOMPONENT_HPP_
#include "AComponent.hpp"
#include <exception>

namespace nts {
    class FalseComponent: public AComponent<0, 1>
    {
        public:
            FalseComponent(std::string name);
            ~FalseComponent() = default;

            void simulate(std::size_t tick) override;
            virtual Tristate compute(std::size_t pin = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
    };
};

std::ostream &operator<<(std::ostream &s, const nts::FalseComponent &True);

#endif /* !FALSECOMPONENT_HPP_ */
