/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** TrueComponent
*/

#ifndef TRUECOMPONENT_HPP_
#define TRUECOMPONENT_HPP_
#include "AComponent.hpp"
#include <exception>

namespace nts {
    class TrueComponent: public AComponent<0, 1>
    {
        public:
            TrueComponent(std::string name);
            ~TrueComponent() = default;

            virtual Tristate compute(std::size_t pin = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
    };
};

std::ostream &operator<<(std::ostream &s, const nts::TrueComponent &True);

#endif /* !TRUECOMPONENT_HPP_ */
