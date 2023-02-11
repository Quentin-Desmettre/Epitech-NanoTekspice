/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** BinaryCounter
*/

#ifndef BINARYCOUNTER_HPP_
#define BINARYCOUNTER_HPP_
#include "AComponent.hpp"
#include <map>

namespace nts {
    class BinaryCounter: public nts::AComponent<4, 12> {
        public:
            BinaryCounter(const std::string &name);
            ~BinaryCounter() override = default;

            void simulate(std::size_t tick) override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            nts::Tristate compute(std::size_t pin) override;

        private:
            void increaseCounter(std::size_t bitIndex = 0);
            void undefinedReset();

            std::array<nts::Tristate, 12> _bits, _newBits;
            nts::Tristate _oldClock, _newClock;
            static std::map<std::size_t, std::size_t> _pinToBitIndex;
            bool _hasComputed;
    };
}; // namespace nts

/*
# 12-bits Binary Counter (4040)
#
#      cl_clock -10-+     +-11- in_reset
#                   |     |
#    +------4040----v-----v--------------+
# -8-|-ign   12-bit Binary Counter   ign-|-16-
#    +------v-v-v-v-v-v-v-v-v-v-v-v------+
#           | | | | | | | | | | | |
# out_00 -9-+ | | | | | | | | | | +-1- out_11
#   out_01 -7-+ | | | | | | | | +-15- out_10
#     out_02 -6-+ | | | | | | +-14- out_09
#       out_03 -5-+ | | | | +-12- out_08
#         out_04 -3-+ | | +-13- out_07
#           out_05 -2-+ +-4- out_06

If reset is undefined:
    if bit was 0           => 0
    if bit was 1/undefined => undefined
If reset is 0: do not change anything
if reset is 1: all bits to 0

If clock geos from 1 to 0:
    Increase internal counter by 1
    If counter is 4096, reset it to 0
If clock goes from 1 to 1:
    Do nothing
If clock  goes from 1 to undefined:
    Same as undefined reset

If clock goes from 0 to 0, 0 to 1 or 0 to undefined
    Do nothing

if Clock goes from undefined to 0:
    Same as undefined reset
If clock goes from undefined to 1:
    Do nothing
If clock goes from undefined to undefined:
    Same as undefined reset

So, do nothing if:
    - _oldClock is 0
    - newClock is 1
Increase counter if:
    - _oldClock is 1 && newClock is 0
Reset if:
    - reset is 1
Undefined reset if:
    - reset is undefined
    - _oldClock is undefined && clock != 1
    - _oldClock is 1 && clock is undefined

 Increasing the counter
    increaseBit(bitIndex) (index = 0 -> weakest bit)
        if bitIndex is 12:
            return
        if bit is 0:
            bit = 1
            return
        if bit is 1:
            bit = 0
            increaseBit(bitIndex + 1)
            return
        if bit is undefined:
            bit+1 = undefined
            return



 */

#endif /* !BINARYCOUNTER_HPP_ */
