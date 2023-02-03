/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Circuit.cpp
*/

#include "Circuit.hpp"
#include "Parser.hpp"
#include "ClockComponent.hpp"
#include <csignal>
#include <algorithm>

bool nts::Circuit::_loop = false;

nts::Circuit::Circuit(const std::string &name):
    _tick(0)
{
    auto components = Parser::parseFile(name);

    _inputs = components.first;
    _outputs = components.second;

    std::signal(SIGINT, nts::Circuit::stopLoop);
}

void nts::Circuit::simulate()
{
    // Compute outputs
    for (auto &output: _outputs)
        output->compute(0);
    // Switch clocks
    ClockComponent::switchClocks();
    _tick++;
}

void nts::Circuit::loop()
{
    _loop = true;
    while (_loop) {
        simulate();
        std::cout << *this << std::endl;
    }
}

void nts::Circuit::stopLoop(int)
{
    _loop = false;
}

std::vector<nts::InputComponent *> nts::Circuit::getSortedInputs() const
{
    return Circuit::getSortedVector<InputComponent>(_inputs);
}

std::vector<nts::OutputComponent *> nts::Circuit::getSortedOutputs() const
{
    return Circuit::getSortedVector<OutputComponent>(_outputs);
}

std::ostream &operator<<(std::ostream &os, const nts::Circuit &circuit)
{
    // Print tick
    os << "tick: " << circuit.getTick() << std::endl;

    // Print inputs
    os << "input(s):";
    for (auto &input: circuit.getSortedInputs())
        os << std::endl << "  " << input->getName() << "=" << input->compute(0);

    // Print outputs
    os << std::endl << "output(s):";
    for (auto &output: circuit.getSortedOutputs())
        os << std::endl << "  " << output->getName() << "=" << output->getValue();
    return os;
}

std::size_t nts::Circuit::getTick() const
{
    return _tick;
}
