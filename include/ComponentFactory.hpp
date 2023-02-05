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

            static std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &name);

            // Special components
            static std::unique_ptr<IComponent> createInput(const std::string &name);
            static std::unique_ptr<IComponent> createOutput(const std::string &name);
            static std::unique_ptr<IComponent> createTrue(const std::string &name);
            static std::unique_ptr<IComponent> createFalse(const std::string &name);
            static std::unique_ptr<IComponent> createClock(const std::string &name);

            // Elementary components
            static std::unique_ptr<IComponent> createAnd(const std::string &name);
            static std::unique_ptr<IComponent> createOr(const std::string &name);
            static std::unique_ptr<IComponent> createXor(const std::string &name);
            static std::unique_ptr<IComponent> createNot(const std::string &name);

            // Gates components
            static std::unique_ptr<IComponent> create4001(const std::string &name);
            static std::unique_ptr<IComponent> create4011(const std::string &name);
            static std::unique_ptr<IComponent> create4030(const std::string &name);
            static std::unique_ptr<IComponent> create4069(const std::string &name);
            static std::unique_ptr<IComponent> create4071(const std::string &name);
            static std::unique_ptr<IComponent> create4081(const std::string &name);

            // Advanced components
            static std::unique_ptr<IComponent> create4008(const std::string &name);
            static std::unique_ptr<IComponent> create4013(const std::string &name);
            static std::unique_ptr<IComponent> create4017(const std::string &name);
            static std::unique_ptr<IComponent> create4040(const std::string &name);
            static std::unique_ptr<IComponent> create4094(const std::string &name);
            static std::unique_ptr<IComponent> create4512(const std::string &name);
            static std::unique_ptr<IComponent> create4514(const std::string &name);
            static std::unique_ptr<IComponent> create4801(const std::string &name);
            static std::unique_ptr<IComponent> create2716(const std::string &name);

            // Mapper
            static std::map<std::string, std::unique_ptr<IComponent>(*) (const std::string &)> _components;
};

}; // namespace nts

#endif /* !COMPONENTFACTORY_HPP_ */
