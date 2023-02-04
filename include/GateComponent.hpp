/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** GateComponent
*/

#ifndef GATECOMPONENT_HPP_
#define GATECOMPONENT_HPP_
#include "AComplexComponent.hpp"

namespace nts
{
    template <typename T>
    class GateComponent : public nts::AComplexComponent {
        public:
            GateComponent(std::string name):
                AComplexComponent(name)
            {
                // Output pins
                _outputMap[3] = {3, new T(name + "-intern1")};
                _outputMap[4] = {3, new T(name + "-intern2")};
                _outputMap[10] = {3, new T(name + "-intern3")};
                _outputMap[11] = {3, new T(name + "-intern4")};

                // Input pins
                _inputMap[1] = {1, _outputMap[3].second};
                _inputMap[2] = {2, _outputMap[3].second};
                _inputMap[5] = {1, _outputMap[4].second};
                _inputMap[6] = {2, _outputMap[4].second};
                _inputMap[8] = {1, _outputMap[10].second};
                _inputMap[9] = {2, _outputMap[10].second};
                _inputMap[12] = {1, _outputMap[11].second};
                _inputMap[13] = {2, _outputMap[11].second};

                // Unused pins
                _unusedPins.push_back(7);
                _unusedPins.push_back(14);
            }
            ~GateComponent() = default;
    };
}
#endif /* !GATECOMPONENT_HPP_ */
