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
    nts::FalseComponent false1("false");
    nts::ClockComponent clock("clock");

    johnson.setLink(13, false1, 1);
    johnson.setLink(14, clock, 1);
    johnson.setLink(15, false1, 1);

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
    johnson.setLink(13, true1, 1);
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
    johnson.setLink(13, false1, 1);
    for (int i = 0; i < 11; i++) {
        if (i == 7)
            i++;
        if (i == 1)
            CHECK(johnson.compute(i + 1) == nts::True);
        else
            CHECK(johnson.compute(i + 1) == nts::False);
    }
    johnson.setLink(15, true1, 1);
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
    nts::ClockComponent clock("clock");
    nts::InputComponent input("input");

    johnson.setLink(13, false1, 1);
    johnson.setLink(15, false1, 1);

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
    johnson.setLink(15, true1, 1);
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
    johnson.setLink(15, false1, 1);
}
