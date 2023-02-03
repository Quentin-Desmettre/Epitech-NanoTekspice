/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Errors
*/

#include "Errors.hpp"

nts::PinError::PinError(const std::string &component, const std::string &message) :
    component(component),
    message(message)
{
}

const char *nts::PinError::what() const noexcept
{
    return (component + ": " + message).c_str();
}
