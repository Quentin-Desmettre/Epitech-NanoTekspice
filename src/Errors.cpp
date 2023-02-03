/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Errors
*/

#include "Errors.hpp"

nts::AError::~AError() {}

nts::AError::AError(const std::string &message) :
    _message(message)
{
}

const char *nts::AError::what() const noexcept
{
    return _message.c_str();
}

nts::PinError::PinError(const std::string &componentName, const std::string &funcName, std::size_t pin):
    AError(componentName+ "::" + funcName + ": Pin " + std::to_string(pin) + " doesn't exist")
{
}

nts::ComponentNotFoundError::ComponentNotFoundError(const std::string &component) :
    AError(component + ": Component not found")
{
}
