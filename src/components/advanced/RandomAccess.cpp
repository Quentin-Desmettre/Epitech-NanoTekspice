/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** RandomAccess.cpp
*/

#include "RandomAccess.hpp"
#include <fstream>
#include <iostream>

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

    _pinToBitOffset = {
        {9, 0},
        {10, 1},
        {11, 2},
        {13, 3},
        {14, 4},
        {15, 5},
        {16, 6},
        {17, 7}
    };

    std::fill(_ram.begin(), _ram.end(), nts::False);
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

nts::Tristate nts::RandomAccess::writeData(std::size_t pin)
{
    // Get all possible addresses
    std::set<int> possibleAddresses = getPossibleAddresses();

    // Get data to write
    std::array<nts::Tristate, 8> dataToWrite = {
        computeInput(9),
        computeInput(10),
        computeInput(11),
        computeInput(13),
        computeInput(14),
        computeInput(15),
        computeInput(16),
        computeInput(17)
    };

    // Write data to all possible addresses
    for (int address: possibleAddresses) {
        for (int i = 0; i < 8; i++)
            _ram[address * 8 + i] = dataToWrite[i];
    }

    // Return input addres for given pin
    return pin != nts::SIMULATOR_PIN ? dataToWrite[_pinToBitOffset[pin]] : nts::Undefined;
}

std::set<int> nts::RandomAccess::getPossibleAddresses()
{
    // Get possibles addresses
    const std::vector<int> bothState = {0, 1};
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

    // Get possible combinations of bits
    std::array<std::vector<int>, 10> addressCombins;
    for (int i = 0; i < 10; i++)
        addressCombins[i] = (addressBits[i] == nts::Undefined ? bothState : std::vector<int>{int(addressBits[i])});

    // Get possible addresses
    std::set<int> possibleAddresses;
    getPossibilites(possibleAddresses, addressCombins);
    return possibleAddresses;
}

nts::Tristate nts::RandomAccess::getData(std::size_t pin)
{
    // Get possible addresses
    std::set<int> possibleAddresses = getPossibleAddresses();

    // From those addresses, get the possible data
    std::set<nts::Tristate> possibleData;
    for (auto &a: possibleAddresses) {
        possibleData.insert(_ram[a * 8 + _pinToBitOffset[pin]]);
    }
    return (possibleData.size() == 1 ? *possibleData.begin() : nts::Undefined);
}

/*

21 undefined, 18 LOW:
    If OE HIGH, return undefined & write data
    If OE LOW, read & write data
    If OE undefined, return undefined & write data

20 undefined, 18 LOW:
    If WE HIGH, return undefined
    If WE LOW, write data, return Din
    If WE undefined, return undefined & write data
*/


/*
So, if 18 LOW:

Write data if:
    WE Low / Undefined

Read data if:
    OE LOW, WE HIGH
    OE LOW, WE Undefined
    => OE Low, WE not Low
Return undefined if:
    WE High, OE High
    WE undefined, OE != low
    OE undefined, WE != low

*/

// Compute only reads from the memory
nts::Tristate nts::RandomAccess::compute(std::size_t pin)
{
    if (pin != nts::SIMULATOR_PIN && getPinType(pin) != nts::PinType::BOTH)
        return nts::Undefined; // Because only computable pins are BOTH

    // Var setup
    nts::Tristate
        enable = computeInput(18),
        write = computeInput(21),
        read = computeInput(20),
        writtenData = nts::Undefined,
        readedData = nts::Undefined;
    bool
        writeData = false,
        readData = false;

    // Check if the memory is enabled
    if (enable != nts::False) {
        return nts::Undefined;
    }

    // Get the mode to use (Read / Write / Read & Write)
    if (write != nts::True)
        writeData = true;
    if (read == nts::False && write != nts::False)
        readData = true;

    // If no mode selected, return undefined
    if (!writeData && !readData) {
        return nts::Undefined;
    }

    // Compute the data
    if (writeData)
        writtenData = this->writeData(pin);
    if (readData)
        readedData = (pin == nts::SIMULATOR_PIN ? writtenData : this->getData(pin));

    // If both mode were active, return undefined if the data are different
    if ((writeData && readData && writtenData != readedData) || write == nts::Undefined || read == nts::Undefined)
        return nts::Undefined;
    if (writeData)
        return writtenData;
    return readedData;
}

void nts::RandomAccess::simulate(std::size_t tick)
{
    (void)tick;
    _hasWrittenData = false;
}
