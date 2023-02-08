/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** testGates
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
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

// test AND gate
TEST_CASE("AND gate")
{
    nts::TrueComponent true1("true1");
    nts::TrueComponent true2("true2");
    nts::FalseComponent false1("false1");
    nts::FalseComponent false2("false2");
    nts::InputComponent input1("input1");
    nts::InputComponent input2("input2");
    nts::AndComponent and1("and1");
    nts::AndComponent and2("and2");
    nts::AndComponent and3("and3");
    nts::AndComponent and4("and4");
    nts::AndComponent and5("and5");
    nts::AndComponent and6("and6");
    nts::AndComponent and7("and7");

    input1.setValue(nts::Undefined);
    input2.setValue(nts::Undefined);

    and1.setLink(1, true1, 1);
    and1.setLink(2, true2, 1);
    and2.setLink(1, true1, 1);
    and2.setLink(2, false1, 1);
    and3.setLink(1, false1, 1);
    and3.setLink(2, true1, 1);
    and4.setLink(1, false1, 1);
    and4.setLink(2, false2, 1);
    and5.setLink(1, input1, 1);
    and5.setLink(2, input2, 1);
    and6.setLink(1, input1, 1);
    and6.setLink(2, true1, 1);
    and7.setLink(1, input1, 1);
    and7.setLink(2, false1, 1);

    REQUIRE_THROWS(and7.setLink(1, input1, 1));
    REQUIRE_THROWS(and7.setLink(2, false1, 1));


    CHECK(and1.AElementaryComponent::compute(3) == nts::True);
    CHECK(and2.AElementaryComponent::compute(3) == nts::False);
    CHECK(and3.AElementaryComponent::compute(3) == nts::False);
    CHECK(and4.AElementaryComponent::compute(3) == nts::False);
    CHECK(and5.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(and6.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(and7.AElementaryComponent::compute(3) == nts::False);
}

// test OR gate
TEST_CASE("OR gate")
{
    nts::TrueComponent true1("true1");
    nts::TrueComponent true2("true2");
    nts::FalseComponent false1("false1");
    nts::FalseComponent false2("false2");
    nts::InputComponent input1("input1");
    nts::InputComponent input2("input2");
    nts::OrComponent or1("or1");
    nts::OrComponent or2("or2");
    nts::OrComponent or3("or3");
    nts::OrComponent or4("or4");
    nts::OrComponent or5("or5");
    nts::OrComponent or6("or6");
    nts::OrComponent or7("or7");

    input1.setValue(nts::Undefined);
    input2.setValue(nts::Undefined);
    
    or1.setLink(1, true1, 1);
    or1.setLink(2, true2, 1);
    or2.setLink(1, true1, 1);
    or2.setLink(2, false1, 1);
    or3.setLink(1, false1, 1);
    or3.setLink(2, true1, 1);
    or4.setLink(1, false1, 1);
    or4.setLink(2, false2, 1);
    or5.setLink(1, input1, 1);
    or5.setLink(2, input2, 1);
    or6.setLink(1, input1, 1);
    or6.setLink(2, true1, 1);
    or7.setLink(1, input1, 1);
    or7.setLink(2, false1, 1);

    CHECK(or1.AElementaryComponent::compute(3) == nts::True);
    CHECK(or2.AElementaryComponent::compute(3) == nts::True);
    CHECK(or3.AElementaryComponent::compute(3) == nts::True);
    CHECK(or4.AElementaryComponent::compute(3) == nts::False);
    CHECK(or5.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(or6.AElementaryComponent::compute(3) == nts::True);
    CHECK(or7.AElementaryComponent::compute(3) == nts::Undefined);
}

// test XOR gate
TEST_CASE("XOR gate")
{
    nts::TrueComponent true1("true1");
    nts::TrueComponent true2("true2");
    nts::FalseComponent false1("false1");
    nts::FalseComponent false2("false2");
    nts::InputComponent input1("input1");
    nts::InputComponent input2("input2");
    nts::XorComponent xor1("xor1");
    nts::XorComponent xor2("xor2");
    nts::XorComponent xor3("xor3");
    nts::XorComponent xor4("xor4");
    nts::XorComponent xor5("xor5");
    nts::XorComponent xor6("xor6");
    nts::XorComponent xor7("xor7");

    input1.setValue(nts::Undefined);
    input2.setValue(nts::Undefined);
    
    xor1.setLink(1, true1, 1);
    xor1.setLink(2, true2, 1);
    xor2.setLink(1, true1, 1);
    xor2.setLink(2, false1, 1);
    xor3.setLink(1, false1, 1);
    xor3.setLink(2, true1, 1);
    xor4.setLink(1, false1, 1);
    xor4.setLink(2, false2, 1);
    xor5.setLink(1, input1, 1);
    xor5.setLink(2, input2, 1);
    xor6.setLink(1, input1, 1);
    xor6.setLink(2, true1, 1);
    xor7.setLink(1, input1, 1);
    xor7.setLink(2, false1, 1);

    CHECK(xor1.AElementaryComponent::compute(3) == nts::False);
    CHECK(xor2.AElementaryComponent::compute(3) == nts::True);
    CHECK(xor3.AElementaryComponent::compute(3) == nts::True);
    CHECK(xor4.AElementaryComponent::compute(3) == nts::False);
    CHECK(xor5.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(xor6.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(xor7.AElementaryComponent::compute(3) == nts::Undefined);
}


// test NAND gate
TEST_CASE("NAND gate")
{
    nts::TrueComponent true1("true1");
    nts::TrueComponent true2("true2");
    nts::FalseComponent false1("false1");
    nts::FalseComponent false2("false2");
    nts::InputComponent input1("input1");
    nts::InputComponent input2("input2");
    nts::NandComponent nand1("nand1");
    nts::NandComponent nand2("nand2");
    nts::NandComponent nand3("nand3");
    nts::NandComponent nand4("nand4");
    nts::NandComponent nand5("nand5");
    nts::NandComponent nand6("nand6");
    nts::NandComponent nand7("nand7");

    input1.setValue(nts::Undefined);
    input2.setValue(nts::Undefined);
    
    nand1.setLink(1, true1, 1);
    nand1.setLink(2, true2, 1);
    nand2.setLink(1, true1, 1);
    nand2.setLink(2, false1, 1);
    nand3.setLink(1, false1, 1);
    nand3.setLink(2, true1, 1);
    nand4.setLink(1, false1, 1);
    nand4.setLink(2, false2, 1);
    nand5.setLink(1, input1, 1);
    nand5.setLink(2, input2, 1);
    nand6.setLink(1, input1, 1);
    nand6.setLink(2, true1, 1);
    nand7.setLink(1, input1, 1);
    nand7.setLink(2, false1, 1);

    CHECK(nand1.AElementaryComponent::compute(3) == nts::False);
    CHECK(nand2.AElementaryComponent::compute(3) == nts::True);
    CHECK(nand3.AElementaryComponent::compute(3) == nts::True);
    CHECK(nand4.AElementaryComponent::compute(3) == nts::True);
    CHECK(nand5.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(nand6.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(nand7.AElementaryComponent::compute(3) == nts::True);
}

// test NOR gate
TEST_CASE("NOR gate")
{
    nts::TrueComponent true1("true1");
    nts::TrueComponent true2("true2");
    nts::FalseComponent false1("false1");
    nts::FalseComponent false2("false2");
    nts::InputComponent input1("input1");
    nts::InputComponent input2("input2");
    nts::NorComponent nor1("nor1");
    nts::NorComponent nor2("nor2");
    nts::NorComponent nor3("nor3");
    nts::NorComponent nor4("nor4");
    nts::NorComponent nor5("nor5");
    nts::NorComponent nor6("nor6");
    nts::NorComponent nor7("nor7");

    input1.setValue(nts::Undefined);
    input2.setValue(nts::Undefined);
    
    nor1.setLink(1, true1, 1);
    nor1.setLink(2, true2, 1);
    nor2.setLink(1, true1, 1);
    nor2.setLink(2, false1, 1);
    nor3.setLink(1, false1, 1);
    nor3.setLink(2, true1, 1);
    nor4.setLink(1, false1, 1);
    nor4.setLink(2, false2, 1);
    nor5.setLink(1, input1, 1);
    nor5.setLink(2, input2, 1);
    nor6.setLink(1, input1, 1);
    nor6.setLink(2, true1, 1);
    nor7.setLink(1, input1, 1);
    nor7.setLink(2, false1, 1);

    CHECK(nor1.AElementaryComponent::compute(3) == nts::False);
    CHECK(nor2.AElementaryComponent::compute(3) == nts::False);
    CHECK(nor3.AElementaryComponent::compute(3) == nts::False);
    CHECK(nor4.AElementaryComponent::compute(3) == nts::True);
    CHECK(nor5.AElementaryComponent::compute(3) == nts::Undefined);
    CHECK(nor6.AElementaryComponent::compute(3) == nts::False);
    CHECK(nor7.AElementaryComponent::compute(3) == nts::Undefined);
}

// test NOT gate
TEST_CASE("NOT gate")
{
    nts::TrueComponent true1("true1");
    nts::FalseComponent false1("false1");
    nts::InputComponent input1("input1");
    nts::NotComponent not1("not1");
    nts::NotComponent not2("not2");
    nts::NotComponent not3("not3");

    input1.setValue(nts::Undefined);
    
    not1.setLink(1, true1, 1);
    not2.setLink(1, false1, 1);
    not3.setLink(1, input1, 1);

    CHECK(not1.compute(2) == nts::False);
    CHECK(not2.compute(2) == nts::True);
    CHECK(not3.compute(2) == nts::Undefined);
}