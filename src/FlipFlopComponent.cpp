/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** FlipFlopComponent
*/

#include "FlipFlopComponent.hpp"

nts::FlipFlopComponent::FlipFlopComponent(const std::string &name):
    nts::AComponent<4, 2>(name)
{
    _oldClock = nts::Undefined;
    _data = nts::Undefined;
}

nts::Tristate nts::FlipFlopComponent::compute(std::size_t pin)
{
    if (pin != 5 && pin != 6)
        return nts::Undefined;

    nts::Tristate
        clock = computeInput(0),
        data  = computeInput(1),
        set   = computeInput(2),
        reset = computeInput(3)
    ;
    // If set or unset flags are set, they are prioritary, but the clock still has to be set.
    if (set == nts::True) {
        // if reset is undefined or true, data is undefined
        _data = reset == nts::False ? nts::True : nts::Undefined;
    } else if (reset == nts::True) {
        // if set is undefined or true, data is undefined
        _data = set == nts::False ? nts::False : nts::Undefined;
    }
    // positive-edged triggered (low -> high)
    else if (clock == nts::True && (_oldClock == nts::False || _oldClock == nts::Undefined)) {
        _data = data;
    }
    // // negative-edged triggered (high -> low)
    // else if (clock == nts::False && _oldClock == nts::True) {
    //     _data = data;
    // }
    _oldClock = clock;


    nts::Tristate invertedData =
        (_data == nts::True)  ? nts::False :
        (_data == nts::False) ? nts::True  :
                                nts::Undefined
    ;
    return pin == 5 ? _data : invertedData;
}

void nts::FlipFlopComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 0 || pin > 6)
        throw nts::PinError(_name, "setLink", pin);
    if (pin == 5 || pin == 6) {
        _output[pin - 5].component = &other;
        _output[pin - 5].nb = otherPin;
    } else {
        _input[pin - 1].component = &other;
        _input[pin - 1].nb = otherPin;
    }
}
