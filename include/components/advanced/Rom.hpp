/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Rom
*/

#ifndef ROM_HPP_
#define ROM_HPP_

#include "AComponent.hpp"
#include "Errors.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace nts {
    class RomComponent: public nts::AComponent<17, 8> {
        public:
            RomComponent(const std::string &name);
            ~RomComponent() = default;

            nts::Tristate compute(std::size_t pin = 1) override;
            // void simulate(std::size_t tick) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        protected:
        private:
            std::map<std::size_t, std::size_t> _pinToIndex;
    };
}; // namespace nts

#endif /* !ROM_HPP_ */
