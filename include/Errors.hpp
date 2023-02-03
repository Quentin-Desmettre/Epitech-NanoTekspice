/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_
#include <exception>
#include <string>

namespace nts {
    class PinError : public std::exception {
        public:
            PinError(const std::string &component, const std::string &message);
            ~PinError() = default;

            const char *what() const noexcept override;

        protected:
            std::string component;
            std::string message;
    };
} // namespace nts


#endif /* !ERRORS_HPP_ */
