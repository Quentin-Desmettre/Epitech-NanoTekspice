/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Test_InputComponent.cpp
*/

#include "doctest.h"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "InputComponent.hpp"
#include "LoggerComponent.hpp"
#include <fstream>

TEST_CASE("Log Componant")
{
    std::ofstream file("log.bin", std::ios::out | std::ios::trunc);
    file.close();
    nts::LoggerComponent logger("logger");
    nts::TrueComponent trueComp("true");
    nts::InputComponent threeComp("th");
    nts::FalseComponent falseComp("false");
    nts::InputComponent undif("undif");

    logger.setLink(1, trueComp, 1);
    logger.setLink(2, trueComp, 1);
    logger.setLink(3, threeComp, 1);
    logger.setLink(4, trueComp, 1);
    logger.setLink(5, falseComp, 1);
    logger.setLink(6, trueComp, 1);
    logger.setLink(7, trueComp, 1);
    logger.setLink(8, falseComp, 1);
    logger.setLink(9, undif, 1);
    logger.setLink(10, falseComp, 1);

    REQUIRE_THROWS(logger.setLink(9, undif, 1));
    REQUIRE_THROWS(logger.setLink(10, undif, 1));

    threeComp.setValue(nts::True);
    threeComp.simulate(1);
    CHECK(logger.compute(1) == nts::False);
    undif.setValue(nts::True);
    undif.simulate(1);
    CHECK(logger.compute(1) == nts::False);
    undif.setValue(nts::False);
    undif.simulate(1);
    CHECK(logger.compute(1) == nts::False);
    undif.setValue(nts::True);
    undif.simulate(1);
    CHECK(logger.compute(1) == nts::True);
    CHECK(logger.compute(1) == nts::False);
    undif.setValue(nts::False);
    undif.simulate(1);
    CHECK(logger.compute(1) == nts::False);
    undif.setValue(nts::True);
    undif.simulate(1);
    threeComp.setValue(nts::False);
    threeComp.simulate(1);
    CHECK(logger.compute(1) == nts::True);
    std::ifstream file2("log.bin", std::ios::in);
    std::string str;
    std::getline(file2, str);
    CHECK(str == "ok");
    file2.close();
}