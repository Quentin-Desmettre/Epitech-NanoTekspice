/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** ShiftRegister.cpp
*/

#include "ShiftRegister.hpp"
#include <iostream>

std::map<std::size_t, std::size_t> nts::ShiftRegister::_pinToIndex = {
    {4, 0},
    {5, 1},
    {6, 2},
    {7, 3},
    {14, 4},
    {13, 5},
    {12, 6},
    {11, 7}
};

nts::ShiftRegister::ShiftRegister(const std::string &name):
    AComponent<4, 10>(name)
{
    std::fill(_register.begin(), _register.end(), nts::False);
    _newRegister = _register;
    std::fill(_savedValue.begin(), _savedValue.end(), nts::False);
    _newSavedValue = _savedValue;
    _oldClock = nts::False;
    _newClock = nts::False;
    _oldStrobe = nts::False;
    _newStrobe = nts::False;

    _pinToPinType  = {
        {1, nts::INPUT},
        {2, nts::INPUT},
        {3, nts::INPUT},
        {4, nts::OUTPUT},
        {5, nts::OUTPUT},
        {6, nts::OUTPUT},
        {7, nts::OUTPUT},
        {8, nts::UNUSED},
        {9, nts::OUTPUT},
        {10, nts::OUTPUT},
        {11, nts::OUTPUT},
        {12, nts::OUTPUT},
        {13, nts::OUTPUT},
        {14, nts::OUTPUT},
        {15, nts::INPUT},
        {16, nts::UNUSED}
    };
}

void nts::ShiftRegister::simulate(std::size_t tick)
{
    (void)tick;
    _register = _newRegister;
    _oldClock = _newClock;
    _oldStrobe = _newStrobe;
    _savedValue = _newSavedValue;
}

nts::Tristate nts::ShiftRegister::shiftRegister(nts::Tristate frontValue, std::array<nts::Tristate, 8> &registerToShift)
{
    nts::Tristate carryOut = registerToShift[7];

    for (std::size_t i = 7; i > 0; i--)
        registerToShift[i] = registerToShift[i - 1];
    registerToShift[0] = frontValue;
    return carryOut;
}

nts::Tristate nts::ShiftRegister::undefinedShiftRegister(nts::Tristate frontValue, std::array<nts::Tristate, 8> &registerToShift)
{
    // Copy the register, and shift the copy. If the elements of the copy and the register are different, set this register element to undefined
    auto cpyRegister = registerToShift;
    nts::Tristate cpyCarryOut = cpyRegister[7];
    nts::Tristate carryOut = shiftRegister(frontValue, cpyRegister);

    for (std::size_t i = 0; i < 8; i++) {
        if (registerToShift[i] != cpyRegister[i])
            registerToShift[i] = nts::Undefined;
    }
    // If the carry out are different, return undefined
    if (cpyCarryOut != carryOut)
        return nts::Undefined;
    return carryOut;
}

void nts::ShiftRegister::undefinedMemoryFlash()
{
    _newSavedValue = _savedValue;

    for (std::size_t i = 0; i < 8; i++)
        if (_newSavedValue[i] != _savedValue[i]) // Data has changed
            _newSavedValue[i] = nts::Undefined;
}

nts::Tristate nts::ShiftRegister::compute(std::size_t pin)
{
    if (getPinType(pin) != nts::OUTPUT)
        return nts::Undefined;

    if (pin != 9 && pin != 10 && _pinToIndex.find(pin) == _pinToIndex.end())
        return nts::Undefined;
    nts::Tristate
        strobe = computeInput(0),
        data   = computeInput(1),
        clock  = computeInput(2),
        enable = computeInput(3),
        carryOut = nts::False
    ;
    _newRegister = _register;
    _newSavedValue = _savedValue;

    // Try to shift the register
    if (_oldClock == nts::True && clock == nts::False)
        carryOut = shiftRegister(data, _newRegister);
    else if (_oldClock != nts::False && clock != nts::True)
        carryOut = undefinedShiftRegister(data, _newRegister);

    // Flash register into saved value
    if (_oldStrobe == nts::True && strobe == nts::False)
        _newSavedValue = _newRegister;
    else if (_oldStrobe != nts::False && strobe != nts::True)
        undefinedMemoryFlash();

    // Save clock and strobe
    _newClock = clock;
    _newStrobe = strobe;

    // Compute output
    if (pin == 9)
        return carryOut;
    if (pin == 10)
        return AComponent::inverseTristate(carryOut);
    if (enable == nts::False)
        return nts::False;
    std::size_t outputPin = _pinToIndex[pin];
    if (enable == nts::True)
        return _newSavedValue[outputPin];
    return (_newSavedValue[outputPin] == nts::False) ? nts::False : nts::Undefined;
}

void nts::ShiftRegister::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == nts::UNUSED) {
        if (_usedUnusedPins.find(pin) == _usedUnusedPins.end()) {
            _usedUnusedPins.insert(pin);
            return;
        } else
            throw nts::PinError(_name, "setLink", pin);
    }

    if (pin >= 1 && pin <= 3) {
        _input[pin - 1].setComponent(&other);
        _input[pin - 1].setPin(otherPin);
    } else if (pin == 15) {
        _input[3].setComponent(&other);
        _input[3].setPin(otherPin);
    } else if (pin >= 4 && pin <= 16) {
        _output[pin - 4].setComponent(&other);
        _output[pin - 4].setPin(otherPin);
    } else {
        throw nts::PinError(_name, "setLink", pin);
    }
}
