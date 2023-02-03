/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** ComponentFactory
*/

#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_
#include "IComponent.hpp"
#include <map>

namespace nts {
    class ComponentFactory {
        public:
            virtual ~ComponentFactory() = 0;

            static IComponent *createComponent(const std::string &type, const std::string &name);

        protected:
        private:
            // Special components
            static IComponent *createInput(const std::string &name);
            static IComponent *createOutput(const std::string &name);
            static IComponent *createTrue(const std::string &name);
            static IComponent *createFalse(const std::string &name);
            static IComponent *createClock(const std::string &name);

            // Elementary components
            static IComponent *createAnd(const std::string &name);
            static IComponent *createOr(const std::string &name);
            static IComponent *createXor(const std::string &name);
            static IComponent *createNot(const std::string &name);

            // Gates components
            static IComponent *create4001(const std::string &name);
            static IComponent *create4011(const std::string &name);
            static IComponent *create4030(const std::string &name);
            static IComponent *create4069(const std::string &name);
            static IComponent *create4071(const std::string &name);
            static IComponent *create4081(const std::string &name);

            // Advanced components
            static IComponent *create4008(const std::string &name);
            static IComponent *create4013(const std::string &name);
            static IComponent *create4017(const std::string &name);
            static IComponent *create4040(const std::string &name);
            static IComponent *create4094(const std::string &name);
            static IComponent *create4512(const std::string &name);
            static IComponent *create4514(const std::string &name);
            static IComponent *create4801(const std::string &name);
            static IComponent *create2716(const std::string &name);

            // Mapper
            static std::map<std::string, IComponent *(*) (const std::string &)> _components;
};

}; // namespace nts

#endif /* !COMPONENTFACTORY_HPP_ */
