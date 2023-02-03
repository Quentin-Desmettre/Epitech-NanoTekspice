/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** GateComponent
*/

#ifndef GATECOMPONENT_HPP_
#define GATECOMPONENT_HPP_

#include "AComponent.hpp"
#include "Errors.hpp"

namespace nts
{
    template <typename T>
    class GateComponent : public nts::AComponent<10, 4> {
        public:
            GateComponent(std::string name):
                AComponent<10, 4>(name)
            {
                _componentForOutputPin[3] = {3, new T(name + "-intern1")};
                _componentForOutputPin[4] = {3, new T(name + "-intern2")};
                _componentForOutputPin[10] = {3, new T(name + "-intern3")};
                _componentForOutputPin[11] = {3, new T(name + "-intern4")};

                _componentForInputPin[1] = {1, _componentForOutputPin[3].second};
                _componentForInputPin[2] = {2, _componentForOutputPin[3].second};
                _componentForInputPin[5] = {1, _componentForOutputPin[4].second};
                _componentForInputPin[6] = {2, _componentForOutputPin[4].second};
                _componentForInputPin[8] = {1, _componentForOutputPin[10].second};
                _componentForInputPin[9] = {2, _componentForOutputPin[10].second};
                _componentForInputPin[12] = {1, _componentForOutputPin[11].second};
                _componentForInputPin[13] = {2, _componentForOutputPin[11].second};
            }
            ~GateComponent() {
                for (auto &it : _componentForOutputPin)
                    delete it.second.second;
            };
            nts::Tristate compute(std::size_t pin) {
                if (_componentForOutputPin.find(pin) == _componentForOutputPin.end())
                    return nts::Tristate::Undefined;
                return _componentForOutputPin[pin].second->AElementaryComponent::compute(pin);
            }
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
                // Find the pin in the input or output map
                bool isInInput = _componentForInputPin.find(pin) != _componentForInputPin.end();
                bool isInOutput = _componentForOutputPin.find(pin) != _componentForOutputPin.end();
                if (!isInInput && !isInOutput)
                    throw PinError(_name, "setLink", pin);
                // Get the component and the pin number, and set the link
                std::pair<std::size_t, T *> pinAndComponent = isInInput ? _componentForInputPin[pin] : _componentForOutputPin[pin];
                pinAndComponent.second->setLink(pinAndComponent.first, other, otherPin);
            }
        protected:
            // Maps a pin number, to a component and its associated pin number
            std::map<size_t, std::pair<std::size_t, T *>> _componentForInputPin;
            std::map<size_t, std::pair<std::size_t, T *>> _componentForOutputPin;
    };
}
#endif /* !GATECOMPONENT_HPP_ */
