/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_
#include <string>
#include <vector>
#include "InputComponent.hpp"
#include "OutputComponent.hpp"

namespace nts {
    class Circuit {
        public:
            Circuit(const std::string &filename);
            ~Circuit();

            void simulate();
            void loop();

            std::vector<InputComponent *> getInputs() const;
            std::vector<OutputComponent *> getOutputs() const;

        protected:
        private:
            std::vector<InputComponent *> _inputs;
            std::vector<OutputComponent *> _outputs;
    };
}; /* namespace nts */

std::ostream &operator<<(std::ostream &os, const nts::Circuit &circuit);

#endif /* !CIRCUIT_HPP_ */
