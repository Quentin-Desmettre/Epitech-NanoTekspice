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
typedef std::pair<std::vector<nts::InputComponent *>, std::vector<nts::OutputComponent *>> InputOutputPair;

namespace nts {
    class Parser {
        public:
            virtual ~Parser() = default;
            static InputOutputPair parseFile(const std::string &file);
            static void parseChipsets(std::ifstream &ifs, InputOutputPair &pair, std::map <std::string, nts::IComponent *>);
            static void parseLinks(std::ifstream &ifs, std::map <std::string, nts::IComponent *>);

        protected:
        private:
            static std::regex _startChipset;
            static std::regex _chipsetRegex;
            static std::regex _startLink;
            static std::regex _linkRegex;
    };

} /* namespace std */

#endif /* !PARSER_HPP_ */
