/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** DualFlipFlop
*/

#ifndef DUALFLIPFLOP_HPP_
#define DUALFLIPFLOP_HPP_
#include "AComplexComponent.hpp"

namespace nts {
    class DualFlipFlop: public AComplexComponent {
        public:
            DualFlipFlop(const std::string &name);
            ~DualFlipFlop() = default;
    };
}; // namespace nts

/*
 Dual D-Type Flip-Flop (4013)

     cl_1_clock  -3-+
                    |
                +---v---+
                |   |   |
                | +-v-+ |
                | |   | |
 in_1_data   -5->-> L | |
                | | A >->-1-  out_1_q
 in_1_set    -6->-> T | |
                | | C >->-2-  out_1_qb
 in_1_reset  -4->-> H | |
                | |   | |
                | +---+ |
                |       |
                | +---+ |
                | |   | |
 in_2_data   -9->-> L | |
                | | A >->-13- out_2_q
 in_2_set    -8->-> T | |
                | | C >->-12- out_2_qb
 in_2_reset -10->-> H | |
                | |   | |
                | +-^-+ |
                |   |   |
                +---^---+
                    |
     cl_2_clock -11-+
*/

#endif /* !DUALFLIPFLOP_HPP_ */
