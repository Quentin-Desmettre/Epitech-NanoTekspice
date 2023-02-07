/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_SelectorComponent.cpp
*/

#include "../include/SelectorComponent.hpp"
#include "doctest.h"
#include "../include/InputComponent.hpp"
#include <iostream>

static void setInputVal(nts::InputComponent &component, nts::Tristate value)
{
    component.setValue(value);
    component.simulate(0);
}

TEST_CASE("Selector")
{
    nts::SelectorComponent selector("selector");

    // Basic
    REQUIRE(selector.getName() == "selector");
    REQUIRE(selector.compute(5) == nts::Undefined);

    // Linking
    nts::InputComponent a("in_a");
    nts::InputComponent b("in_b");
    nts::InputComponent c("in_c");
    nts::InputComponent enable("in_enable");
    nts::InputComponent inhibit("in_inhibit");
    nts::InputComponent bits[8] = {
        nts::InputComponent("in_bit0"),
        nts::InputComponent("in_bit1"),
        nts::InputComponent("in_bit2"),
        nts::InputComponent("in_bit3"),
        nts::InputComponent("in_bit4"),
        nts::InputComponent("in_bit5"),
        nts::InputComponent("in_bit6"),
        nts::InputComponent("in_bit7")
    };

    // Linking throws
    REQUIRE_THROWS(selector.setLink(0, a, 1));
    REQUIRE_THROWS(selector.setLink(16, a, 1));
    REQUIRE_THROWS(selector.setLink(-1, a, 1));

    // Linking doesn't throw
    // Bits
    REQUIRE_NOTHROW(selector.setLink(1, bits[0], 1));
    REQUIRE_NOTHROW(selector.setLink(2, bits[1], 1));
    REQUIRE_NOTHROW(selector.setLink(3, bits[2], 1));
    REQUIRE_NOTHROW(selector.setLink(4, bits[3], 1));
    REQUIRE_NOTHROW(selector.setLink(5, bits[4], 1));
    REQUIRE_NOTHROW(selector.setLink(6, bits[5], 1));
    REQUIRE_NOTHROW(selector.setLink(7, bits[6], 1));
    REQUIRE_NOTHROW(selector.setLink(9, bits[7], 1));
    // A, B, C
    REQUIRE_NOTHROW(selector.setLink(11, a, 1));
    REQUIRE_NOTHROW(selector.setLink(12, b, 1));
    REQUIRE_NOTHROW(selector.setLink(13, c, 1));
    // Enable, Inhibit
    REQUIRE_NOTHROW(selector.setLink(15, enable, 1));
    REQUIRE_NOTHROW(selector.setLink(10, inhibit, 1));

    SUBCASE("Basic cases")
    {
        setInputVal(inhibit, nts::False);
        setInputVal(enable, nts::True);
        for (int i = 0; i < 4; i++) {
            for (int i = 0; i < 8; i++) {
                setInputVal(a, (i & 0b100) ? nts::True : nts::False);
                setInputVal(b, (i & 0b010) ? nts::True : nts::False);
                setInputVal(c, (i & 0b001) ? nts::True : nts::False);
                // Set a random value for the focused bit
                int rnd = random() % 3;
                nts::Tristate val;
                if (rnd == 0)
                    val = nts::True;
                else if (rnd == 1)
                    val = nts::False;
                else
                    val = nts::Undefined;
                setInputVal(bits[i], val);
                // Compute
                nts::Tristate computed = selector.compute(14);
                REQUIRE(computed == val);
            }
        }
    }

    SUBCASE("Undefined values")
    {
        setInputVal(inhibit, nts::False);
        setInputVal(enable, nts::True);

        SUBCASE("A undefined")
        {
            setInputVal(a, nts::Undefined);
            setInputVal(b, nts::True);
            setInputVal(c, nts::False);
            for (int i = 0; i < 8; i++) {
                setInputVal(bits[i], nts::False);
            }
            REQUIRE(selector.compute(14) == nts::Undefined);
        }
        SUBCASE("B undefined")
        {
            setInputVal(a, nts::True);
            setInputVal(b, nts::Undefined);
            setInputVal(c, nts::False);
            for (int i = 0; i < 8; i++) {
                setInputVal(bits[i], nts::False);
            }
            REQUIRE(selector.compute(14) == nts::Undefined);
        }
        SUBCASE("C undefined")
        {
            setInputVal(a, nts::True);
            setInputVal(b, nts::False);
            setInputVal(c, nts::Undefined);
            for (int i = 0; i < 8; i++) {
                setInputVal(bits[i], nts::False);
            }
            REQUIRE(selector.compute(14) == nts::Undefined);
        }
    }

    SUBCASE("Inhibit = True")
    {
        setInputVal(inhibit, nts::True);
        setInputVal(enable, nts::False);

        setInputVal(a, nts::False);
        setInputVal(b, nts::False);
        setInputVal(c, nts::False);
        setInputVal(bits[0], nts::True);
        for (int i = 1; i < 8; i++) {
            setInputVal(bits[i], nts::False);
        }
        REQUIRE(selector.compute(14) == nts::Undefined);
    }
    SUBCASE("Enable = False")
    {
        setInputVal(inhibit, nts::False);
        setInputVal(enable, nts::False);

        setInputVal(a, nts::False);
        setInputVal(b, nts::False);
        setInputVal(c, nts::False);
        setInputVal(bits[0], nts::True);
        for (int i = 1; i < 8; i++) {
            setInputVal(bits[i], nts::False);
        }
        REQUIRE(selector.compute(14) == nts::Undefined);
    }
    SUBCASE("Inhibit = True && Enable = True")
    {
        setInputVal(inhibit, nts::True);
        setInputVal(enable, nts::True);

        setInputVal(a, nts::False);
        setInputVal(b, nts::False);
        setInputVal(c, nts::False);
        setInputVal(bits[0], nts::True);
        for (int i = 1; i < 8; i++) {
            setInputVal(bits[i], nts::False);
        }
        REQUIRE(selector.compute(14) == nts::Undefined);
    }
}
