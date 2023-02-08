/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Parser
*/

#include "Parser.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::regex nts::Parser::_startChipset = std::regex("^\\s*.chipsets:\\s*$");
std::regex nts::Parser::_chipsetRegex = std::regex("^\\s*([^\\ =]+)\\s+([^\\ =]+)\\s*$");
std::regex nts::Parser::_startLink = std::regex("^\\s*.links:\\s*$");
std::regex nts::Parser::_linkRegex = std::regex("^\\s*([^\\ =]+):([0-9]+)\\s+([^\\ =]+):([0-9]+)\\s*$");

nts::InputOutputRest nts::Parser::parseFile(const std::string &file)
{
    std::ifstream ifs(file);
    std::string line;
    nts::InputOutputRest compo;
    std::map<std::string, IComponent *> components;

    if (!ifs.is_open())
        throw std::runtime_error("File not found");
    while (std::getline(ifs, line))
    {
        line = line.substr(0, line.find('#'));
        if (!std::regex_match(line, std::regex("^\\s*$")))
            break;
    }
    if (std::regex_match(line, _startChipset))
        line = parseChipsets(ifs, compo, components);
    else
        throw std::runtime_error("Invalid file format");
    if (std::regex_match(line, _startLink))
        parseLinks(ifs, components);
    else
        throw std::runtime_error("Invalid file format");
    return compo;
}

std::string nts::Parser::parseChipsets(std::ifstream &ifs, InputOutputRest &pair, std::map<std::string, IComponent *> &components)
{
    std::string line;
    std::smatch match;

    while (std::getline(ifs, line))
    {
        line = line.substr(0, line.find('#'));
        if (std::regex_match(line, std::regex("^\\s*$")))
            continue;
        if (std::regex_match(line, match, _chipsetRegex)) {
            if (components.find(match.str(2)) != components.end())
                throw std::runtime_error("Chipset: " + match.str(2) +" already exists");
            auto unique = nts::ComponentFactory::createComponent(match.str(1), match.str(2));
            components[match.str(2)] = unique.get();
            if (match.str(1) == "input" || match.str(1) == "clock")
                pair.input.push_back(std::move(unique));
            else if (match.str(1) == "output")
                pair.output.push_back(std::move(unique));
            else if (match.str(1) == "logger")
                pair.log.push_back(std::move(unique));
            else
                pair.other.push_back(std::move(unique));
        } else
            return line;
    }
    return line;
}

void nts::Parser::parseLinks(std::ifstream &ifs, const std::map<std::string, IComponent *> &components)
{
    std::string line;
    std::smatch match;
    IComponent *compoA, *compoB;
    std::size_t pinA, pinB;

    while (std::getline(ifs, line))
    {
        line = line.substr(0, line.find('#'));
        if (std::regex_match(line, std::regex("^\\s*$")))
            continue;
        if (std::regex_match(line, match, _linkRegex)) {
            if (components.find(match.str(1)) == components.end())
                throw std::runtime_error("Chipset: " + match.str(1) + " unknown");
            if (components.find(match.str(3)) == components.end())
                throw std::runtime_error("Chipset: " + match.str(3) + " unknown");
            compoA = components.at(match.str(1));
            compoB = components.at(match.str(3));
            pinA = std::stoi(match.str(2));
            pinB = std::stoi(match.str(4));
            // Check if we're not linking an output to an output or an input to an input
            if ((compoA->getPinType(pinA) == nts::OUTPUT && compoB->getPinType(pinB)) == nts::OUTPUT ||
                (compoA->getPinType(pinA) == nts::INPUT && compoB->getPinType(pinB) == nts::INPUT))
                throw std::runtime_error("Invalid link");
            // Actually link the components
            compoA->setLink(pinA, *compoB, pinB);
            compoB->setLink(pinB, *compoA, pinA);
        } else
            throw std::runtime_error("Invalid file format");
    }
}
