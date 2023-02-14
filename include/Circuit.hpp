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
#include <algorithm>
#include <map>
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "Parser.hpp"

namespace nts {
    class Circuit {
        public:
            Circuit(const std::string &filename);
            ~Circuit() = default;

            void simulate();
            void loop();
            static void stopLoop(int);

            std::vector<InputComponent *> getSortedInputs() const;
            std::vector<OutputComponent *> getSortedOutputs() const;
            std::map<std::string, InputComponent *> getInputsMappedByName() const;
            std::size_t getTick() const;
            void compute() const;

        protected:
        private:
            std::size_t _tick;
            std::vector<UniqueIComponent> _inputs, _outputs, _log, _other;
            std::vector<IComponent *> _all;
            static bool _loop;

            template <typename T>
            static std::vector<T *> getSortedVector(const std::vector<UniqueIComponent> &vector) {
                std::vector<IComponent *> sortedVector;
                for (std::size_t i = 0; i < vector.size(); i++)
                    sortedVector.push_back(vector[i].get());

                std::sort(sortedVector.begin(), sortedVector.end(), [](IComponent *a, IComponent *b) {
                    return a->getName() < b->getName();
                });
                std::vector<T *> sortedVectorOfT;
                for (std::size_t i = 0; i < sortedVector.size(); i++)
                    sortedVectorOfT.push_back(dynamic_cast<T *>(sortedVector[i]));
                return sortedVectorOfT;
            }
    };
}; /* namespace nts */

std::ostream &operator<<(std::ostream &os, const nts::Circuit &circuit);

#endif /* !CIRCUIT_HPP_ */
