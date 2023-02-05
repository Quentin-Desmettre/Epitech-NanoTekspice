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
#include "ComponentFactory.hpp"
#include <regex>

namespace nts {
    class Parser {
        public:
            virtual ~Parser() = default;
            static InputOutputRestTruple parseFile(const std::string &file);

        protected:
        private:
            static std::regex _startChipset;
            static std::regex _chipsetRegex;
            static std::regex _startLink;
            static std::regex _linkRegex;

            static std::string parseChipsets(std::ifstream &ifs, InputOutputRestTruple &pair, std::map <std::string, IComponent *> &components);
            static void parseLinks(std::ifstream &ifs, const std::map <std::string, IComponent *> &components);
    };

} /* namespace std */

#endif /* !PARSER_HPP_ */
