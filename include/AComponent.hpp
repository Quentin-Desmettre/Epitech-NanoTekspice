/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <array>

namespace nts
{
    template <size_t T1, size_t T2>
    class AComponent : public nts::IComponent {
        public:
            AComponent(std::string name) {_name = name;}
            virtual ~AComponent() = default;
            std::string getName() const override { return _name; }
        protected:
            std::array<Pin, T1> _input;
            std::array<Pin, T2> _output;
            std::string _name;
        private:
    };
}
#endif /* !ACOMPONENT_HPP_ */
