/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** DecoderComponent
*/

#include "DecoderComponent.hpp"

nts::DecoderComponent::DecoderComponent(const std::string &name):
    nts::AComponent<8, 16>(name)
{
    _pinToIndex = {
        {11, 0},
        {9, 1},
        {10, 2},
        {8, 3},
        {7, 4},
        {6, 5},
        {5, 6},
        {4, 7},
        {18, 8},
        {17, 9},
        {20, 10},
        {19, 11},
        {14, 12},
        {13, 13},
        {16, 14},
        {15, 15}
    };
    _pinToInput = {
        {2, 0},
        {3, 1},
        {21, 2},
        {22, 3},
        {1, 4},
        {23, 5},
        {12, 6},
        {14, 7}
    };
    _oldValues.fill(nts::Undefined);
    _newValues.fill(nts::Undefined);
}

void nts::DecoderComponent::simulate(std::size_t tick)
{
    (void)tick;
    _oldValues = _newValues;
}

nts::Tristate nts::DecoderComponent::compute(std::size_t pin)
{
    if (_pinToIndex.find(pin) == _pinToIndex.end())
        return nts::Undefined;
    pin = _pinToIndex[pin];
    nts::Tristate
        strobe = computeInput(4),
        inhibit = computeInput(5),
        tmp = nts::False
    ;
    _newValues = _oldValues;

    // Update internal data if strobe
    if (strobe == nts::True)
        for (int i = 0; i < 4; i++)
            _newValues[i] = computeInput(i);
    if (strobe == nts::Undefined) {
        for (int i = 0; i < 4; i++) {
            tmp = computeInput(i);
            if (_newValues[i] != tmp)
                _newValues[i] = nts::Undefined;
        }
    }

    // Inhibit
    if (inhibit == nts::True)
        return nts::False;
    if (inhibit == nts::Undefined)// If inhibit is undefined, get normal output for selected pin. If output is not false, return undefined
        return getValueForIndex(pin) == nts::False ? nts::False : nts::Undefined;
    return getValueForIndex(pin);
}

nts::Tristate nts::DecoderComponent::getValueForIndex(std::size_t index)
{
    // Get differents possible values
    std::array<std::vector<int>, 4> combins;
    const std::vector<int> bothValues = {0, 1};
    for (int i = 0; i < 4; i++) {
        combins[i] = (_oldValues[i] == nts::Undefined ? bothValues : (std::vector<int>){int(_oldValues[i])});
    }
    std::set<int> possibleValues;
    getPossibilites(possibleValues, combins);

    // Here, possiblValues if filled with {0, 15, 8} for instance.
    // In this case, if index is 8, 15 or 0, we return undefined, as both of these values could have been and could not have been.
    // But, if index is none of them, we return false.
    // But, is possibleValues contained only 1 item, we return true if it's the same as index, false otherwise.
    if (possibleValues.size() == 1)
        return *possibleValues.begin() == int(index) ? nts::True : nts::False;
    return possibleValues.find(index) != possibleValues.end() ? nts::Undefined : nts::False;
}

void nts::DecoderComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (_pinToInput.find(pin) != _pinToInput.end()) {
        _input[_pinToInput[pin]].setComponent(&other);
        _input[_pinToInput[pin]].setPin(otherPin);
    } else if (_pinToIndex.find(pin) != _pinToIndex.end()) {
        _output[_pinToIndex[pin]].setComponent(&other);
        _output[_pinToIndex[pin]].setPin(otherPin);
    } else
        throw nts::PinError(_name, "setLink", pin);
}
