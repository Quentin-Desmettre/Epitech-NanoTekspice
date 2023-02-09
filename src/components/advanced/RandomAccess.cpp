/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** RandomAccess.cpp
*/

#include "RandomAccess.hpp"
#include <fstream>

nts::RandomAccess::RandomAccess(const std::string &name):
    AComponent<0, 0>(name),
    _hasWrittenData(false)
{
    _inputMap = {
        {1, Pin()},
        {2, Pin()},
        {3, Pin()},
        {4, Pin()},
        {5, Pin()},
        {6, Pin()},
        {7, Pin()},
        {8, Pin()},
        {9, Pin()},
        {10, Pin()},
        {11, Pin()},
        {13, Pin()},
        {14, Pin()},
        {15, Pin()},
        {16, Pin()},
        {17, Pin()},
        {18, Pin()},
        {20, Pin()},
        {21, Pin()},
        {22, Pin()},
        {23, Pin()}
    };
    // Both
    _outputMap = {
        {9, Pin()},
        {10, Pin()},
        {11, Pin()},
        {13, Pin()},
        {14, Pin()},
        {15, Pin()},
        {16, Pin()},
        {17, Pin()}
    };
    _unusedMap = {
        {12, Pin()},
        {19, Pin()},
        {24, Pin()}
    };
}

nts::PinType nts::RandomAccess::getPinType(std::size_t pin) const
{
    bool isInInput = _inputMap.find(pin) != _inputMap.end();
    bool isInOutput = _outputMap.find(pin) != _outputMap.end();
    bool isUnused = std::find(_unusedPins.begin(), _unusedPins.end(), pin) != _unusedPins.end();

    if (isInInput && isInOutput)
        return nts::PinType::BOTH;
    if (isInInput)
        return nts::PinType::INPUT;
    if (isInOutput)
        return nts::PinType::OUTPUT;
    if (isUnused)
        return nts::PinType::UNUSED;
    return nts::PinType::ERROR;
}

void nts::RandomAccess::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    // Check errors
    if (getPinType(pin) == nts::PinType::ERROR)
        throw nts::PinError(_name, "setLink", pin);
    // If input, set input
    if (getPinType(pin) == INPUT) {
        _inputMap[pin].setComponent(&other);
        _inputMap[pin].setPin(otherPin);
     // If can be both, try to link to both
    } else if (getPinType(pin) == BOTH) {
        if (other.getPinType(otherPin) == BOTH) {
            try {
                _inputMap.at(pin).setComponent(&other);
                _inputMap.at(pin).setPin(otherPin);
            } catch (std::exception &e) {
                _outputMap.at(pin).setComponent(&other);
                _outputMap.at(pin).setPin(otherPin);
            }
        } else if (other.getPinType(otherPin) == INPUT) {
            _outputMap[pin].setComponent(&other);
            _outputMap[pin].setPin(otherPin);
        } else {
            _inputMap[pin].setComponent(&other);
            _inputMap[pin].setPin(otherPin);
        }
    } else if (getPinType(pin) == OUTPUT) {
        _outputMap[pin].setComponent(&other);
        _outputMap[pin].setPin(otherPin);
    } else { // Else it is Unused
        _unusedMap[pin].setComponent(&other);
        _unusedMap[pin].setPin(otherPin);
    }
}

nts::Tristate nts::RandomAccess::computeInput(std::size_t pin)
{
    nts::PinType type = getPinType(pin);

    if (type != nts::PinType::INPUT && type != nts::PinType::BOTH)
        return nts::Undefined;
    if (_inputMap[pin].getComponent() != nullptr)
        return _inputMap[pin].getComponent()->compute(_inputMap[pin].getPin());
    return nts::Undefined;
}

void nts::RandomAccess::writeData(std::size_t address)
{
    if (_hasWrittenData)
        return;
    _hasWrittenData = true;
    std::array<nts::Tristate, 8> data = {
        computeInput(9),
        computeInput(10),
        computeInput(11),
        computeInput(13),
        computeInput(14),
        computeInput(15),
        computeInput(16),
        computeInput(17)
    };
    // Undefined bits in the data => Undefined results
    if (std::find(data.begin(), data.end(), nts::Undefined) != data.end())
        return;
    // Write data
    for (std::size_t i = 0; i < 8 && address + i < 1024; i++)
        _ram[address + 1] = data[i];
}

// Compute only reads from the memory
nts::Tristate nts::RandomAccess::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::PinType::BOTH)
        return nts::Undefined; // Because only computable pins are BOTH

    nts::Tristate
        enable = computeInput(18),
        write = computeInput(21),
        read = computeInput(20)
    ;
    if (enable == nts::False)
        return nts::False;

    std::size_t address = getAddress();
    // Check data to write
    if (write == nts::True && read == nts::False && enable == nts::True) {
        writeData(address);
        return nts::Undefined;
    }
    // Check write
    else if (read == nts::True && write == nts::False && enable == nts::True)
        return _ram[address];
    return nts::Undefined;
}

std::size_t nts::RandomAccess::getAddress()
{
    std::array<nts::Tristate, 10> addressBits = {
        computeInput(8),
        computeInput(7),
        computeInput(6),
        computeInput(5),
        computeInput(4),
        computeInput(3),
        computeInput(2),
        computeInput(1),
        computeInput(23),
        computeInput(22)
    };
    // Undefined bits in the address => Undefined results
    if (std::find(addressBits.begin(), addressBits.end(), nts::Undefined) != addressBits.end())
        return (std::size_t)(-1);
    // Get the address
    std::size_t address = 0;
    for (int i = 0; i < 10; i++) {
        if (addressBits[i] == nts::True)
            address += 1 << i;
    }
    return address;
}

void nts::RandomAccess::simulate(std::size_t tick)
{
    (void)tick;
    _hasWrittenData = false;
}
