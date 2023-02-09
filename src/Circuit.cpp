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
#include <iostream>

bool nts::Circuit::_loop = false;

nts::Circuit::Circuit(const std::string &name):
    _tick(0)
{
    auto components = Parser::parseFile(name);

    for (auto &component: components.input) {
        _inputs.push_back(std::move(component));
        _all.push_back(_inputs.back().get());
    }
    for (auto &component: components.output) {
        _outputs.push_back(std::move(component));
        _all.push_back(_outputs.back().get());
    }
    for (auto &component: components.log) {
        _log.push_back(std::move(component));
        _all.push_back(_log.back().get());
    }
    for (auto &component: components.other) {
        _other.push_back(std::move(component));
        _all.push_back(_other.back().get());
    }

    std::signal(SIGINT, nts::Circuit::stopLoop);
}

void nts::Circuit::simulate()
{
    // Simulate
    for (std::size_t i = 0; i < _all.size(); i++)
        _all[i]->simulate(0);
    // Compute outputs
    for (std::size_t i = 0; i < _outputs.size(); i++)
        _outputs[i]->compute(1);
    for (std::size_t i = 0; i < _log.size(); i++)
        _log[i]->compute(1);
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

std::map<std::string, nts::InputComponent *> nts::Circuit::getInputsMappedByName() const
{
    std::map<std::string, nts::InputComponent *> components;

    for (std::size_t i = 0; i < _inputs.size(); i++)
        components[_inputs[i]->getName()] = dynamic_cast<nts::InputComponent *>(_inputs[i].get());
    return components;
}

std::ostream &operator<<(std::ostream &os, const nts::Circuit &circuit)
{
    nts::Tristate state;

    // Print tick
    os << "tick: " << circuit.getTick() << std::endl;

    // Print inputs
    os << "input(s):";
    for (auto &input: circuit.getSortedInputs()) {
        state = input->getValue();
        os << std::endl << "  " << input->getName() << ": " << (state == nts::Undefined ? "U" : std::to_string(state));
    }

    // Print outputs
    os << std::endl << "output(s):";
    for (auto &output: circuit.getSortedOutputs()) {
        state = output->getValue();
        os << std::endl << "  " << output->getName() << ": " << (state == nts::Undefined ? "U" : std::to_string(state));
    }
    return os;
}

std::size_t nts::Circuit::getTick() const
{
    return _tick;
}

