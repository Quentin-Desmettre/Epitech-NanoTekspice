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
            static void stopLoop(int);

            std::vector<InputComponent *> getSortedInputs() const;
            std::vector<OutputComponent *> getSortedOutputs() const;
            std::size_t getTick() const;

        protected:
        private:
            std::size_t _tick;
            std::vector<InputComponent *> _inputs;
            std::vector<OutputComponent *> _outputs;
            static bool _loop;

            template <typename T>
            static std::vector<T *> getSortedVector(const std::vector<T *> &vector) {
                std::vector<T *> sortedVector = vector;

                std::sort(sortedVector.begin(), sortedVector.end(), [](T *a, T *b) {
                    return a->getName() < b->getName();
                });
                return sortedVector;
            }
    };
}; /* namespace nts */

std::ostream &operator<<(std::ostream &os, const nts::Circuit &circuit);

#endif /* !CIRCUIT_HPP_ */
