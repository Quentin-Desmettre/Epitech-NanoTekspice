/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Shell
*/

#include "Shell.hpp"
#include <istream>

const std::map<std::string, void (nts::Shell::*)()> nts::Shell::_commandToAction = {
    {"exit", &nts::Shell::exit},
    {"display", &nts::Shell::display},
    {"simulate", &nts::Shell::simulate},
    {"loop", &nts::Shell::loop}
};

nts::Shell::Shell(nts::Circuit &circuit):
    _circuit(circuit),
    _run(true)
{
}

std::string nts::Shell::getCommand()
{
    std::string command;
    std::cout << "> ";
    std::getline(std::cin, command);
    if (std::cin.eof())
        throw EndOfInputError();
    return command;
}

bool nts::Shell::lineMatchInputChange(const std::string &line)
{
    return std::regex_search(line, _inputChangeMatch, _inputChangeRegex);
}

void nts::Shell::run()
{
    std::string command;
    while (_run) {
        try {
            command = getCommand();
        } catch (EndOfInputError &e) {
            break;
        }

        if (lineMatchInputChange(command))
            setValueForInput();
        else if (_commandToAction.find(command) != _commandToAction.end())
            (this->*_commandToAction.at(command))();
        else
            std::cout << "Unknown command: '" << command << "'." << std::endl;
    }
}

// Actions

void nts::Shell::setValueForInput()
{
    const std::string &name = _inputChangeMatch.str(1);
    const std::string &value = _inputChangeMatch.str(2);
    std::map<std::string, InputComponent *> _inputByName = _circuit.getInputsMappedByName();

    if (_inputByName.find(name) == _inputByName.end())
        std::cout << "Component '" << name << "' does not exist." << std::endl;
    else {
        _inputByName.at(name)->setValue((std::map<std::string, nts::Tristate>) {
            {"1", nts::True},
            {"0", nts::False},
            {"U", nts::Undefined}
        }[value]);
    }
}

void nts::Shell::exit()
{
    _run = false;
}

void nts::Shell::display()
{
    std::cout << _circuit << std::endl;
}

void nts::Shell::simulate()
{
    _circuit.simulate();
}

void nts::Shell::loop()
{
    _circuit.loop();
}
