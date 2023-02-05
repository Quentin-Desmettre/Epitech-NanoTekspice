/*
** EPITECH PROJECT, 2022
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** ComponentFactory.cpp
*/

#include "ComponentFactory.hpp"
#include "Errors.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "ClockComponent.hpp"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "NotComponent.hpp"
#include "GateComponent.hpp"
#include "SixInvComponent.hpp"
#include "BitsAdder.hpp"
#include "DualFlipFlop.hpp"

nts::ComponentFactory::~ComponentFactory() {};

std::map<std::string, nts::IComponent *(*) (const std::string &)> nts::ComponentFactory::_components = {
    {"input", nts::ComponentFactory::createInput},
    {"output", nts::ComponentFactory::createOutput},
    {"true", nts::ComponentFactory::createTrue},
    {"false", nts::ComponentFactory::createFalse},
    {"clock", nts::ComponentFactory::createClock},
    {"4001", nts::ComponentFactory::create4001},
    {"4011", nts::ComponentFactory::create4011},
    {"4030", nts::ComponentFactory::create4030},
    {"4069", nts::ComponentFactory::create4069},
    {"4071", nts::ComponentFactory::create4071},
    {"4081", nts::ComponentFactory::create4081},
    {"4008", nts::ComponentFactory::create4008},
    {"4013", nts::ComponentFactory::create4013},
    {"4017", nts::ComponentFactory::create4017},
    {"4040", nts::ComponentFactory::create4040},
    {"4094", nts::ComponentFactory::create4094},
    {"4512", nts::ComponentFactory::create4512},
    {"4514", nts::ComponentFactory::create4514},
    {"4801", nts::ComponentFactory::create4801},
    {"2716", nts::ComponentFactory::create2716},
    {"and", nts::ComponentFactory::createAnd},
    {"or", nts::ComponentFactory::createOr},
    {"xor", nts::ComponentFactory::createXor},
    {"not", nts::ComponentFactory::createNot},
};

nts::IComponent *nts::ComponentFactory::createComponent(const std::string &type, const std::string &name) {
    if (_components.find(type) == _components.end())
        throw nts::ComponentNotFoundError(type);
    return _components[type](name);
}

nts::IComponent *nts::ComponentFactory::createInput(const std::string &name)
{
    return new nts::InputComponent(name);
}

nts::IComponent *nts::ComponentFactory::createOutput(const std::string &name)
{
    return new nts::OutputComponent(name);
}

nts::IComponent *nts::ComponentFactory::createTrue(const std::string &name)
{
    return new nts::TrueComponent(name);
}

nts::IComponent *nts::ComponentFactory::createFalse(const std::string &name)
{
    return new nts::FalseComponent(name);
}

nts::IComponent *nts::ComponentFactory::createClock(const std::string &name)
{
    return new nts::ClockComponent(name);
}

nts::IComponent *nts::ComponentFactory::createAnd(const std::string &name)
{
    return new nts::AndComponent(name);
}

nts::IComponent *nts::ComponentFactory::createOr(const std::string &name)
{
    return new nts::OrComponent(name);
}

nts::IComponent *nts::ComponentFactory::createXor(const std::string &name)
{
    return new nts::XorComponent(name);
}

nts::IComponent *nts::ComponentFactory::createNot(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4001(const std::string &name)
{
    return new nts::AndComponent(name); // TODO
}

nts::IComponent *nts::ComponentFactory::create4011(const std::string &name)
{
    return new nts::OrComponent(name); // TODO
}

nts::IComponent *nts::ComponentFactory::create4030(const std::string &name)
{
    return new nts::GateComponent<XorComponent>(name);
}

nts::IComponent *nts::ComponentFactory::create4069(const std::string &name)
{
    return new nts::SixInvComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4071(const std::string &name)
{
    return new nts::GateComponent<OrComponent>(name);
}

nts::IComponent *nts::ComponentFactory::create4081(const std::string &name)
{
    return new nts::GateComponent<AndComponent>(name);
}

nts::IComponent *nts::ComponentFactory::create4008(const std::string &name)
{
    return new nts::BitsAdder(name);
}

nts::IComponent *nts::ComponentFactory::create4013(const std::string &name)
{
    return new nts::DualFlipFlop(name);
}

nts::IComponent *nts::ComponentFactory::create4017(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4040(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4094(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4512(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4514(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create4801(const std::string &name)
{
    return new nts::NotComponent(name);
}

nts::IComponent *nts::ComponentFactory::create2716(const std::string &name)
{
    return new nts::NotComponent(name);
}
