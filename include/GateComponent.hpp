/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** GateComponent
*/

#ifndef GATECOMPONENT_HPP_
#define GATECOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts
{
    template <typename T>
    class GateComponent : public nts::IComponent {
        public:
            GateComponent(std::string name) {
                _name = name;
                _components[3] = new T();
                _components[4] = new T();
                _components[10] = new T();
                _components[11] = new T();
                }
            ~GateComponent() {
                for (auto &it : _components)
                    delete it.second;
            };
            nts::Tristate compute(std ::size_t pin) {
                if (pin == 7 || pin == 14) {}
                if (_components.find(pin) == _components.end())
                    return nts::Tristate::Undefined;
                return _components[pin]->compute(3);
            }
        protected:
            std::map<size_t, T *> _components;
        private:
    };  
}
#endif /* !GATECOMPONENT_HPP_ */
