/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_
#include "IComponent.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"

namespace nts {
    class Parser {
        public:
            virtual ~Parser() = 0;
            static std::pair<std::vector<InputComponent *>, std::vector<OutputComponent *>> parseFile(const std::string &file) {return {{}, {}};};

        protected:
        private:
    };

} /* namespace std */


nts::Parser::~Parser() {};

#endif /* !PARSER_HPP_ */
