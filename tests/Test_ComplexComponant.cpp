/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** fourGateComponant
*/

#include "doctest.h"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "NandComponent.hpp"
#include "NorComponent.hpp"
#include "NotComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "InputComponent.hpp"
#include "GateComponent.hpp"
#include "SixInvComponent.hpp"

// test 4 and Component
TEST_CASE("4 and Component")
{
    nts::GateComponent<nts::AndComponent> and1("and1");

    nts::TrueComponent true1("true1");
    nts::TrueComponent true2("true2");
    nts::FalseComponent false1("false1");
    nts::FalseComponent false2("false2");
    nts::InputComponent input1("input1");
    nts::InputComponent input2("input2");
    
    input1.setValue(nts::Undefined);
    input2.setValue(nts::Undefined);

    and1.setLink(1, true1, 1);
    and1.setLink(2, true2, 1);
    and1.setLink(5, false1, 1);
    and1.setLink(6, false2, 1);
    and1.setLink(8, input1, 1);
    and1.setLink(9, input2, 1);

    CHECK(and1.compute(3) == nts::True);
    CHECK(and1.compute(4) == nts::False);
    CHECK(and1.compute(10) == nts::Undefined);
    CHECK(and1.compute(11) == nts::Undefined);
}

TEST_CASE("Six not gate")
{
    nts::SixInvComponent Inv("inverter");

    nts::TrueComponent true1("true1");
    nts::FalseComponent false1("false1");
    nts::InputComponent input1("input1");

    input1.setValue(nts::Undefined);

    Inv.setLink(1, true1, 1);
    Inv.setLink(3, false1, 1);
    Inv.setLink(5, input1, 1);

    CHECK(Inv.compute(2) == nts::False);
    CHECK(Inv.compute(4) == nts::True);
    CHECK(Inv.compute(6) == nts::Undefined);
    CHECK(Inv.compute(8) == nts::Undefined);
}