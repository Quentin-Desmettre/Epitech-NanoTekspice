/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** BitsAdder
*/

#ifndef BITSADDER_HPP_
#define BITSADDER_HPP_
#include "AComplexComponent.hpp"

// 4-bits Adder (4008)
namespace nts {
    class BitsAdder: public nts::AComplexComponent {
        public:
            BitsAdder(const std::string &name);
            ~BitsAdder() = default;
    };
}; // namespace nts

/*
4-bits Adder (4008)

                 +-14- out_c
                 |
          +-4008-^------+
          |      |      |
in_b4 -15->---+--^--+   |
          |   | sum |--->-13- out_3
in_a4  -1->---+--+--+   |
          |      |      |
in_b3  -2->---+--^--+   |
          |   | sum |--->-12- out_2
in_a3  -3->---+--+--+   |
          |      |      |
in_b2  -4->---+--^--+   |
          |   | sum |--->-11- out_1
in_a2  -5->---+--+--+   |
          |      |      |
in_b1  -6->---+--^--+   |
          |   | sum |--->-10- out_0
in_a1  -7->---+--+--+   |
          |      |      |
in_c   -9->------+      |
          |             |
       -8-+- ign   ign -+-16-
          |             |
          +-------------+


         4 (carry)
         ^
    +---sum---+
-1->|         |
    |         |-->5 (result)
-2->|         |
    +---------+
         ^
         |
         3

sum truth table:

A B C | S C
-----------------
0 0 0 | 0 0
0 0 1 | 1 0
0 0 U | U 0

0 1 0 | 1 0
0 1 1 | 0 1
0 1 U | U U

0 U 0 | U 0
0 U 1 | U U
0 U U | U U
-----------------

1 0 0 | 1 0
1 0 1 | 0 1
1 0 U | U U

1 1 0 | 0 1
1 1 1 | 1 1
1 1 U | U 1

1 U 0 | U U
1 U 1 | U 1
1 U U | U U
-----------------

U 0 0 | U 0
U 0 1 | U U
U 0 U | U U

U 1 0 | U U
U 1 1 | U 1
U 1 U | U U

U U 0 | U U
U U 1 | U U
U U U | U U
-----------------



0 0 0 | 0 0
0 0 1 | 1 0
0 1 0 | 1 0
0 1 1 | 0 1
1 0 0 | 1 0
1 0 1 | 0 1
1 1 0 | 0 1
1 1 1 | 1 1
-----------------

*/

#endif /* !BITSADDER_HPP_ */
