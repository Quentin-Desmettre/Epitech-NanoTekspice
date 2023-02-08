/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_TrueComponent.cpp
*/

#include "doctest.h"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "InputComponent.hpp"

TEST_CASE("TrueComponent")
{
    nts::TrueComponent trueComponent("true");

    REQUIRE(trueComponent.getName() == "true");

    SUBCASE("Compute")
    {
        REQUIRE_NOTHROW(trueComponent.compute(1));
        REQUIRE(trueComponent.compute(1) == nts::True);
        REQUIRE_THROWS_AS(trueComponent.compute(2), nts::PinError);
        REQUIRE_THROWS_AS(trueComponent.compute(0), nts::PinError);
    }

    SUBCASE("SetLink")
    {
        nts::InputComponent input("input");
        REQUIRE_NOTHROW(trueComponent.setLink(1, input, 1));
        REQUIRE_NOTHROW(input.setLink(1, trueComponent, 1));

        REQUIRE_THROWS_AS(trueComponent.setLink(2, input, 1), nts::PinError);
        REQUIRE_THROWS_AS(input.setLink(2, trueComponent, 1), nts::PinError);
    }
}

TEST_CASE("FalseComponent")
{
    nts::FalseComponent falseComponent("false");

    REQUIRE(falseComponent.getName() == "false");

    SUBCASE("Compute")
    {
        REQUIRE_NOTHROW(falseComponent.compute(1));
        REQUIRE(falseComponent.compute(1) == nts::False);
        REQUIRE_THROWS_AS(falseComponent.compute(2), nts::PinError);
        REQUIRE_THROWS_AS(falseComponent.compute(0), nts::PinError);
    }

    SUBCASE("SetLink")
    {
        nts::InputComponent input("input");
        REQUIRE_NOTHROW(falseComponent.setLink(1, input, 1));
        REQUIRE_NOTHROW(input.setLink(1, falseComponent, 1));

        REQUIRE_THROWS_AS(falseComponent.setLink(2, input, 1), nts::PinError);
        REQUIRE_THROWS_AS(input.setLink(2, falseComponent, 1), nts::PinError);
    }
}
