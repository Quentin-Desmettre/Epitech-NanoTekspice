/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** FlipFlopComponent
*/

#include "FlipFlopComponent.hpp"
#include <iostream>


nts::FlipFlopComponent::FlipFlopComponent(const std::string &name):
    nts::AComponent<4, 2>(name)
{
    _oldClock = nts::Undefined;
    _newClock = nts::Undefined;
    _data = nts::Undefined;
}

void nts::FlipFlopComponent::simulate(std::size_t tick)
{
    (void)tick;
    _oldClock = _newClock;
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
    bool updatedBySetOrReset = false;
    // If set or unset flags are set, they are prioritary, but the clock still has to be set.

    // Check set / reset
    if (set == nts::True) {
        // if reset is undefined or true, data is undefined
        _data = reset == nts::False ? nts::True : nts::Undefined;
    } else if (reset == nts::True) {
        // if set is undefined or true, data is undefined
        _data = set == nts::False ? nts::False : nts::Undefined;
    }
    if (set == nts::Undefined && reset == nts::Undefined)
        _data = nts::Undefined;
    if (set == nts::True || reset == nts::True || (set == nts::Undefined && reset == nts::Undefined))
        updatedBySetOrReset = true;

    // Check clock, positive-edge going
    if (!updatedBySetOrReset) {
        // If clock goes from low to high      => update data
        // If clock goes from low to low       => don't change data
        // If clock goes from low to undefined => data is undefined, except if the new data is same as before

        // If clock goes from high to high     => don't change data
        // If clock goes from high to low      => Don't change data
        // If clock goes from high to undefined=> Dont' change data

        // If clock goes from undefined to high  => data is undefined, except if the new data is same as before
        // If clock goes from undefined to low   => data is not changed
        // If Clock goes from undefined to undef => data is undefined, except is the new data is same as before

        // So, don't change data when:
        //      - low->low
        //      - high->anything
        //      - undefined->low
        // Undefined (except):
        //      - low->undefined
        //      - undef->high
        //      - undef->undef
        // Update:
        //      -low -> high
        if (_oldClock == nts::False && clock == nts::True)
            _data = data;
        else if ((_oldClock == nts::False && clock == nts::Undefined) || (_oldClock == nts::Undefined && clock != nts::False))
            _data = (data == _data ? _data : nts::Undefined);
        // else, do nothing
    }
    _newClock = clock;

    nts::Tristate invertedData;
    if (_data == nts::True)
        invertedData = nts::False;
    else if (_data == nts::False)
        invertedData = nts::True;
    else
        invertedData = nts::Undefined;
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
