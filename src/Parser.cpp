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
std::regex nts::Parser::_chipsetRegex = std::regex("^\\s*([a-zA-Z0-9]+)\\s+([a-zA-Z0-9]+)\\s*$");
std::regex nts::Parser::_startLink = std::regex("^\\s*.links:\\s*$");
std::regex nts::Parser::_linkRegex = std::regex("^\\s*([a-zA-Z0-9]+):([0-9]+)\\s+([a-zA-Z0-9]+):([0-9]+)\\s*$");

InputOutputRestTruple nts::Parser::parseFile(const std::string &file)
{
    std::ifstream ifs(file);
    std::string line;
    InputOutputRestTruple truple;
    std::map<std::string, IComponent *> components;

    if (!ifs.is_open())
        throw std::runtime_error("File not found");
    while (std::getline(ifs, line))
    {
        line.substr(0, line.find('#'));
        if (!std::regex_match(line, std::regex("^\\s*$")))
            break;
    }
    if (std::regex_match(line, _startChipset))
        line = parseChipsets(ifs, truple, components);
    else
        throw std::runtime_error("Invalid file format");
    if (std::regex_match(line, _startLink))
        parseLinks(ifs, components);
    else
        throw std::runtime_error("Invalid file format");
    return truple;
}

std::string nts::Parser::parseChipsets(std::ifstream &ifs, InputOutputRestTruple &pair, std::map<std::string, IComponent *> &components)
{
    std::string line;
    std::smatch match;

    while (std::getline(ifs, line))
    {
        line.substr(0, line.find('#'));
        if (std::regex_match(line, std::regex("^\\s*$")))
            continue;
        if (std::regex_match(line, match, _chipsetRegex)) {
            if (components.find(match.str(2)) != components.end())
                throw std::runtime_error("Chipset: " + match.str(2) +" already exists");
            auto unique = nts::ComponentFactory::createComponent(match.str(1), match.str(2));
            components[match.str(2)] = unique.get();
            if (match.str(1) == "input" || match.str(1) == "clock")
                pair[0].push_back(std::move(unique));
            else if (match.str(1) == "output")
                pair[1].push_back(std::move(unique));
            else
                pair[2].push_back(std::move(unique));
        } else
            return line;
    }
    return line;
}

void nts::Parser::parseLinks(std::ifstream &ifs, const std::map<std::string, IComponent *> &components)
{
    std::string line;
    std::smatch match;

    while (std::getline(ifs, line))
    {
        line.substr(0, line.find('#'));
        if (std::regex_match(line, std::regex("^\\s*$")))
            continue;
        if (std::regex_match(line, match, _linkRegex)) {
            if (components.find(match.str(1)) == components.end())
                throw std::runtime_error("Chipset: " + match.str(1) + " unknown");
            if (components.find(match.str(3)) == components.end())
                throw std::runtime_error("Chipset: " + match.str(3) + " unknown");
            components.at(match.str(1))->setLink(std::stoi(match.str(2)), *components.at(match.str(3)), std::stoi(match.str(4)));
            components.at(match.str(3))->setLink(std::stoi(match.str(4)), *components.at(match.str(1)), std::stoi(match.str(2)));
        }
    }
}
