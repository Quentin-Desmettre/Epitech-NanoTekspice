/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** main
*/

#include "Circuit.hpp"
#include "Shell.hpp"
#include <iostream>

int main(int ac, char **av)
{
    // Arg check
    if (ac != 2) {
        std::cerr << "Usage: ./nanotekspice <file.nts>" << std::endl;
        return 84;
    }

    // Build circuit
    std::unique_ptr<nts::Circuit> circuit;
    try {
        circuit = std::make_unique<nts::Circuit>(av[1]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    // Run simulation
    nts::Shell shell(*circuit);
    shell.run();
    return 0;
}
