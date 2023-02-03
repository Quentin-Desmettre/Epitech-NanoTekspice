/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_
#include "Circuit.hpp"
#include <map>
#include <regex>

namespace nts {
    class Shell {
        public:
            Shell(Circuit &circuit);
            ~Shell() = default;

            void run();

        private:
            class EndOfInputError: public std::exception {
                public:
                    EndOfInputError() = default;
                    ~EndOfInputError() = default;

                    const char *what() const noexcept override {
                        return "End of input";
                    }
            };

            // Actions
            void exit();
            void display();
            void simulate();
            void loop();
            void setValueForInput();
            static const std::map<std::string, void (nts::Shell::*)()> _commandToAction;

            // Utils
            bool lineMatchInputChange(const std::string &line);
            static std::string getCommand();

            // Attributes
            Circuit &_circuit;
            bool _run;
            const std::regex _inputChangeRegex = std::regex("[\\ ]*([^\\ =]+)=([01U])");
            std::smatch _inputChangeMatch;
    };
}; // namespace nts

#endif /* !SHELL_HPP_ */
