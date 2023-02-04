/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** BitsAdder
*/

#include "BitsAdder.hpp"

nts::BitsAdder::BitsAdder(const std::string &name):
    nts::AComponent<0, 0>(name)
{
    SumComponent *sum13 = new SumComponent(name+"_sum1");
    SumComponent *sum12 = new SumComponent(name+"_sum2");
    SumComponent *sum11 = new SumComponent(name+"_sum3");
    SumComponent *sum10 = new SumComponent(name+"_sum4");

    // Internal links
    sum13->setLink(3, *sum12, 4);
    sum12->setLink(4, *sum13, 3);

    sum12->setLink(3, *sum11, 4);
    sum11->setLink(4, *sum12, 3);

    sum11->setLink(3, *sum10, 4);
    sum10->setLink(4, *sum11, 3);

    // Map to output pins
    _outputMap[14] = {4, sum13}; // My pin 14 is the pin 4 of the sum13 component
    _outputMap[13] = {5, sum13};
    _outputMap[12] = {5, sum12};
    _outputMap[11] = {5, sum11};
    _outputMap[10] = {5, sum10};

    // Map to input pins
    _inputMap[15] = {1, sum13}; // My pin 15 is the pin 1 of the sum13 component
    _inputMap[1] = {2, sum13};

    _inputMap[2] = {1, sum12};
    _inputMap[3] = {2, sum12};

    _inputMap[4] = {1, sum11};
    _inputMap[5] = {2, sum11};

    _inputMap[6] = {1, sum10};
    _inputMap[7] = {2, sum10};

    _inputMap[9] = {3, sum10};
}

nts::BitsAdder::~BitsAdder()
{
    for (auto &it : _outputMap)
        delete it.second.second;
}

void nts::BitsAdder::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (pin == 8 || pin == 16)
        return;
    if (_inputMap.find(pin) != _inputMap.end()) {
        _inputMap[pin].second->setLink(_inputMap[pin].first, other, otherPin);
    } else if (_outputMap.find(pin) != _outputMap.end()) {
        _outputMap[pin].second->setLink(_outputMap[pin].first, other, otherPin);
    } else {
        throw nts::PinError(_name, "setLink", pin);
    }
}

nts::Tristate nts::BitsAdder::compute(std::size_t pin)
{
    if (_inputMap.find(pin) != _inputMap.end() || pin == 8 || pin == 16)
        return nts::Undefined;

    if (_outputMap.find(pin) != _outputMap.end())
        return _outputMap[pin].second->compute(_outputMap[pin].first);
    throw nts::PinError(_name, "compute", pin);
}