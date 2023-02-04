/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** SixInverter
*/

#ifndef SIXINVERTER_HPP_
#define SIXINVERTER_HPP_

#include "AComponent.hpp"
#include "NotComponent.hpp"
#include <map>
#include "Errors.hpp"

namespace nts
{
    class SixInvComponent : public nts::AComponent<6, 6> {
        public:
            SixInvComponent(std::string name);
            ~SixInvComponent();
            nts::Tristate compute(std::size_t pin) {
                if (_componentForOutputPin.find(pin) == _componentForOutputPin.end())
                    return nts::Tristate::Undefined;
                return _componentForOutputPin[pin].second->compute(pin);
            }
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) {
                // Find the pin in the input or output map
                bool isInInput = _componentForInputPin.find(pin) != _componentForInputPin.end();
                bool isInOutput = _componentForOutputPin.find(pin) != _componentForOutputPin.end();
                if (!isInInput && !isInOutput)
                    throw PinError(_name, "setLink", pin);
                // Get the component and the pin number, and set the link
                std::pair<std::size_t, NotComponent *> pinAndComponent = isInInput ? _componentForInputPin[pin] : _componentForOutputPin[pin];
                pinAndComponent.second->setLink(pinAndComponent.first, other, otherPin);
            }
        protected:
            // Maps a pin number, to a component and its associated pin number
            std::map<size_t, std::pair<std::size_t, NotComponent *>> _componentForInputPin;
            std::map<size_t, std::pair<std::size_t, NotComponent *>> _componentForOutputPin;
    };
}
#endif /* !SIXINVERTER_HPP_ */
