/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_InputComponent.cpp
*/

#include "doctest.h"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "ClockComponent.hpp"
#include "JohnsonComponent.hpp"
#include <fstream>
#include <iostream>

TEST_CASE("test Johnson") {
    nts::JohnsonComponent johnson("johnson");
    nts::TrueComponent true1("true");
    nts::InputComponent false1("false");
    nts::InputComponent false2("false2");
    nts::ClockComponent clock("clock");

    false1.setValue(nts::False);
    false2.setValue(nts::False);
    false1.simulate(0);
    false2.simulate(0);
    johnson.setLink(13, false1, 1);
    johnson.setLink(14, clock, 1);
    johnson.setLink(15, false2, 1);

    clock.setValue(nts::False);

    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    for (int j = 1; j < 12; j++)
    {
        if (j == 7)
            j++;
        clock.simulate(0);
        johnson.simulate(0);
        for (int i = 0; i < 11; i++) {
            if (i == 7)
                i++;
            if (i == j)
                CHECK(johnson.compute(i + 1) == nts::True);
            else
                CHECK(johnson.compute(i + 1) == nts::False);
        }
        clock.simulate(0);
        johnson.simulate(0);
        for (int i = 0; i < 11; i++) {
            if (i == 7)
                i++;
            if (i == j)
                CHECK(johnson.compute(i + 1) == nts::True);
            else
                CHECK(johnson.compute(i + 1) == nts::False);
        }
    }
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    false1.setValue(nts::True);
    false1.simulate(0);
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    false1.setValue(nts::False);
    false1.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 1)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    false2.setValue(nts::True);
    false2.simulate(0);
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
}

TEST_CASE("test Johnson undefined") {
    nts::JohnsonComponent johnson("johnson");
    nts::TrueComponent true1("true");
    nts::FalseComponent false1("false");
    nts::InputComponent false2("false2");
    nts::ClockComponent clock("clock");
    nts::InputComponent input("input");

    false2.setValue(nts::False);
    false2.simulate(0);
    johnson.setLink(13, false1, 1);
    johnson.setLink(15, false2, 1);

    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0 || i == 1)
            CHECK(johnson.compute(i + 1) == nts::Undefined);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i <= 2)
            CHECK(johnson.compute(i + 1) == nts::Undefined);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    false2.setValue(nts::True);
    false2.simulate(0);
    clock.simulate(0);
    johnson.simulate(0);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 0)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
}
