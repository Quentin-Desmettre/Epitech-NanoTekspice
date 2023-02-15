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
    _oldClock = nts::False;
    _newClock = nts::False;
    _data = nts::False;
    _newData = nts::False;

    _pinToPinType = {
        {1, nts::INPUT},
        {2, nts::INPUT},
        {3, nts::INPUT},
        {4, nts::INPUT},
        {5, nts::OUTPUT},
        {6, nts::OUTPUT}
    };
}

void nts::FlipFlopComponent::simulate(std::size_t tick)
{
    (void)tick;
    _oldClock = _newClock;
    _data = _newData;
}

/*

UP: 0->1
DOWN:  1->Any, 0->0, Undef->0
UNDEF: 0 -> Undef, Undef->Undef, Undef->1

Clock | set | reset | D | q | qb
  UP  |  0  |   0   | 0 | 0 | 1
  UP  |  0  |   0   | 1 | 1 | 0
  UP  |  0  |   0   | U | U | U

 DOWN |  0  |   0   | X | NC| NC

UNDEF |  0  |   0   |old| NC| NC
UNDEF |  0  |   0   |dif| U | U

  X   |  0  |   1   | X | 0 | 1
  X   |  0  |   U   | X | U | U

  X   |  1  |   0   | X | 1 | 0
  X   |  U  |   0   | X | U | U

  X   |  U  |   U   | X | U | U

*/

nts::Tristate nts::FlipFlopComponent::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 5 && pin != 6)
        return nts::Undefined;

    nts::Tristate
        clock = computeInput(0),
        newData  = computeInput(1),
        set   = computeInput(2),
        reset = computeInput(3),
        invertedData = nts::False
    ;

    if (set == nts::Undefined || reset == nts::Undefined)
        newData = nts::Undefined;
    else if (set == nts::True && reset == nts::False) {
        newData = nts::True;
        invertedData = nts::False;
    } else if (set == nts::False && reset == nts::True) {
        newData = nts::False;
        invertedData = nts::True;
    } else if (set == nts::True && reset == nts::True) {
        newData = nts::True;
        invertedData = nts::True;
    } else { // Both false
        if (_oldClock == nts::False && clock == nts::True)
            invertedData = AComponent::inverseTristate(newData);
        else if (_oldClock == nts::True || clock == nts::False) {
            newData = _data;
            invertedData = AComponent::inverseTristate(newData);
        } else if (_data != newData) {// Here, we're in 1 of these config: 0 -> Undef, Undef->Undef, Undef->1
            newData = nts::Undefined;
            invertedData = nts::Undefined;
        } else {
            newData = _data;
            invertedData = AComponent::inverseTristate(newData);
        }
    }

    _newClock = clock;
    _newData = newData;

    return pin == 5 ? newData : invertedData;

/*
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
*/
}

void nts::FlipFlopComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::ERROR)
        throw nts::PinError(_name, "setLink", pin);

    if (pin == 5 || pin == 6) {
        _output[pin - 5].setComponent(&other);
        _output[pin - 5].setPin(otherPin);
    } else {
        _input[pin - 1].setComponent(&other);
        _input[pin - 1].setPin(otherPin);
    }
}
