/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** LoggerComponent
*/

#ifndef LOGGERCOMPONENT_HPP_
#define LOGGERCOMPONENT_HPP_
#include "AComponent.hpp"

namespace nts {
    class LoggerComponent: public AComponent<10, 0> {
        public:
            LoggerComponent(std::string name);
            ~LoggerComponent() = default;

            Tristate compute(std::size_t pin = 1) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
        private:
            nts::Tristate _oldClock;
    };
} // namespace nts


#endif /* !LOGGERCOMPONENT_HPP_ */
