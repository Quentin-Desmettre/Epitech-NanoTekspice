/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** ShiftRegister
*/

#ifndef SHIFTREGISTER_HPP_
#define SHIFTREGISTER_HPP_
#include "AComponent.hpp"
#include <map>

namespace nts {
    class ShiftRegister: public AComponent<4, 10> {
    public:
        ShiftRegister(const std::string &name);
        ~ShiftRegister() = default;

        void simulate(std::size_t tick) override;
        nts::Tristate compute(std::size_t pin = 1) override;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
    private:
        static nts::Tristate shiftRegister(nts::Tristate frontValue, std::array<nts::Tristate, 8> &registerToShift);
        static nts::Tristate undefinedShiftRegister(nts::Tristate frontValue,  std::array<nts::Tristate, 8> &registerToShift);
        void undefinedMemoryFlash();

        std::array<nts::Tristate, 8> _register, _newRegister;
        std::array<nts::Tristate, 8> _savedValue, _newSavedValue;
        nts::Tristate _oldClock, _newClock;
        nts::Tristate _oldStrobe, _newStrobe;
        nts::Tristate _carryOut1, _newCarryOut1,
                      _carryOut2, _newCarryOut2;

        static std::map<std::size_t, std::size_t> _pinToIndex;
    };
}; // namespace nts

/*
# 8-bits Shift Register (4094)
#
#                   out_3 -7-+   +-14- out_4
#               out_2 -6-+   |   |   +-13- out_5
#           out_1 -5-+   |   |   |   |   +-12- out_6
#       out_0 -4-+   |   |   |   |   |   |   +-11- out_7
#                |   |   |   |   |   |   |   |
#            +---^---^---^---^---^---^---^---^---+
#            |   |   |   |   |   |   |   |   |   |
# enable -15->--[/]-[/]-[/]-[/]-[/]-[/]-[/]-[/]  |
#            |   |   |   |   |   |   |   |   |   |
#            |  +-----------------------------+  |
#            |  |         saved value         |  |
#            |  +-----------------------------+  |
#            |   |   |   |   |   |   |   |   |   |
#  strobe -1->--[/]-[/]-[/]-[/]-[/]-[/]-[/]-[/]  |
#            |   |   |   |   |   |   |   |   |   |
#            |  +-----------------------------+  |
#    data -2->-->    8 bits shift register    >-->-9- out_qs
#            |  +-^-------------------------v-+  |
#            |    |                         |    |
#   clock -3->----+                         +---->-10- out_q's
#            |                                   |
#            +-4094------------------------------+


8 bits shift register: like a conveyor belt, containing 8 items.

When clock goes from 1 to 0, the conveyor belt moves to the right.
    The value stored in data is then put at the front of the conveyor belt.
    The value that was at the back of the conveyor belt, before it was shifted, is then put in qs, and its inverse is put in q's

When strobe goes from 1 to 0, the data present in the conveyor belt is flashed into the saved value.

When enable is 1, the outputs gets the different values of the saved data (not the conveyor, the data flashed by strobe !!).
When enable is 0, the outputs are 0.
When enable is undefined, the outputs are 0 if they were 0, else undefined.



Clock:
    0 -> 1: shift
    0 -> 0 nothing
    0 -> undefined: undefined shift

    1 -> Any: nothing

    undefined -> 0: nothing
    undefined -> 1: undefined
    undefined -> undefined: undefined

strobe:
    0: Do not flash
    1: flash
    U: undefined flash

enable:
    0: Undefined
    1: vraie valeurs
    U: Undefined

// OLD WAY OF DOING THINGS
Clock:
    0 -> any: nothing change

    1 -> 0: shift the conveyor belt to the right
    1 -> 1: nothing change
    1 -> undefined: shifts conveyor belt; if data at index i changed, it is now undefined, else it is the same as before

    undefined -> 0: same as 1 -> undefined
    undefined -> 1: nothing change
    undefined -> undefined: same as 1 -> undefined

Strobe:
    0 -> any: nothing change

    1 -> 0: flash the conveyor belt into the saved value
    1 -> 1: nothing change
    1 -> undefined: flash the conveyor belt into the saved value; if data at index i changed, it is now undefined, else it is the same as before

    undefined -> 0: same as 1 -> 0
    undefined -> 1: same as 1 -> nothing change
    undefined -> undefined: same as 1 -> undefined

Enable:
    0: Every data is 0
    1: Every data is the saved value
    undefined: Every data is 0 if it was 0, else undefined
*/

#endif /* !SHIFTREGISTER_HPP_ */


