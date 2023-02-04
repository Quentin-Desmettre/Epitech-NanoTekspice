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
    class AError: public std::exception {
        public:
            AError(const std::string &message);
            virtual ~AError() = 0;

            const char *what() const noexcept override;

        private:
            std::string _message;
    };
    class PinError: public AError {
        public:
            PinError(const std::string &componentName, const std::string &funcName, std::size_t pin);
            ~PinError() = default;
    };
    class ComponentNotFoundError: public AError {
        public:
            ComponentNotFoundError(const std::string &component);
            ~ComponentNotFoundError() = default;
    };
} // namespace nts


#endif /* !ERRORS_HPP_ */
