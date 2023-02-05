/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_InputComponent.cpp
*/

#include "doctest.h"
#include "../include/InputComponent.hpp"
#include "../include/OutputComponent.hpp"

TEST_CASE("InputComponent")
{
    nts::InputComponent input("input");

    REQUIRE(input.getName() == "input");
    REQUIRE(input.getValue() == nts::Undefined);

    SUBCASE("Set value")
    {
        input.setValue(nts::True);
        CHECK(input.getValue() == nts::Undefined);
        input.simulate(0);
        REQUIRE(input.compute() == nts::True);
        REQUIRE(input.compute() == nts::True);

        input.setValue(nts::False);
        CHECK(input.getValue() == nts::True);
        input.simulate(0);
        REQUIRE(input.compute() == nts::False);
        REQUIRE(input.compute() == nts::False);

        input.setValue(nts::Undefined);
        CHECK(input.getValue() == nts::False);
        input.simulate(0);
        REQUIRE(input.compute() == nts::Undefined);
        REQUIRE(input.compute() == nts::Undefined);

        SUBCASE("OutputComponent")
        {
            nts::OutputComponent output("output");

            REQUIRE(output.getName() == "output");
            REQUIRE(output.getValue() == nts::Undefined);

            SUBCASE("SetLink")
            {
                nts::InputComponent input("input");
                REQUIRE_NOTHROW(output.setLink(1, input, 1));
                REQUIRE_NOTHROW(input.setLink(1, output, 1));

                REQUIRE_THROWS_AS(output.setLink(2, input, 1), nts::PinError);
                REQUIRE_THROWS_AS(input.setLink(2, output, 1), nts::PinError);

                SUBCASE("Compute")
                {
                    input.setValue(nts::True);
                    input.simulate(0);
                    REQUIRE(output.compute() == nts::True);

                    input.setValue(nts::False);
                    input.simulate(0);
                    REQUIRE(output.compute() == nts::False);

                    input.setValue(nts::Undefined);
                    input.simulate(0);
                    REQUIRE(output.compute() == nts::Undefined);
                }
            }
        }

    }

    SUBCASE("SetLink")
    {
        nts::InputComponent input2("input2");
        REQUIRE_NOTHROW(input.setLink(1, input2, 1));
        REQUIRE_NOTHROW(input2.setLink(1, input, 1));

        REQUIRE_THROWS_AS(input.setLink(2, input2, 1), nts::PinError);
        REQUIRE_THROWS_AS(input2.setLink(2, input, 1), nts::PinError);
    }
}
