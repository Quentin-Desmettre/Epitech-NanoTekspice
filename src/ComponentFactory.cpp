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
#include "NotComponent.hpp"
#include "NandComponent.hpp"
#include "NorComponent.hpp"
#include "LoggerComponent.hpp"
#include "SelectorComponent.hpp"
#include "BinaryCounter.hpp"
#include "ShiftRegister.hpp"
#include "JohnsonComponent.hpp"
#include "RandomAccess.hpp"
#include "Rom.hpp"
#include "DecoderComponent.hpp"

nts::ComponentFactory::~ComponentFactory() {};

std::map<std::string, std::unique_ptr<nts::IComponent>(*) (const std::string &)> nts::ComponentFactory::_components = {
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
    {"logger", nts::ComponentFactory::createLogger},
};

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createComponent(const std::string &type, const std::string &name) {
    if (_components.find(type) == _components.end())
        throw nts::ComponentNotFoundError(type);
    return _components[type](name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createInput(const std::string &name)
{
    return std::make_unique<nts::InputComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createOutput(const std::string &name)
{
    return std::make_unique<nts::OutputComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createTrue(const std::string &name)
{
    return std::make_unique<nts::TrueComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createFalse(const std::string &name)
{
    return std::make_unique<nts::FalseComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createClock(const std::string &name)
{
    return std::make_unique<nts::ClockComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createAnd(const std::string &name)
{
    return std::make_unique<nts::AndComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createOr(const std::string &name)
{
    return std::make_unique<nts::OrComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createXor(const std::string &name)
{
    return std::make_unique<nts::XorComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createNot(const std::string &name)
{
    return std::make_unique<nts::NotComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4001(const std::string &name)
{
    return std::make_unique<nts::GateComponent<NorComponent>>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4011(const std::string &name)
{
    return std::make_unique<nts::GateComponent<NandComponent>>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4030(const std::string &name)
{
    return std::make_unique<nts::GateComponent<XorComponent>>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4069(const std::string &name)
{
    return std::make_unique<nts::SixInvComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4071(const std::string &name)
{
    return std::make_unique<nts::GateComponent<OrComponent>>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4081(const std::string &name)
{
    return std::make_unique<nts::GateComponent<AndComponent>>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4008(const std::string &name)
{
    return std::make_unique<nts::BitsAdder>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4013(const std::string &name)
{
    return std::make_unique<nts::DualFlipFlop>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4017(const std::string &name)
{
    return std::make_unique<nts::JohnsonComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4040(const std::string &name)
{
    return std::make_unique<nts::BinaryCounter>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4094(const std::string &name)
{
    return std::make_unique<nts::ShiftRegister>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4512(const std::string &name)
{
    return std::make_unique<nts::SelectorComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4514(const std::string &name)
{
    return std::make_unique<nts::DecoderComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create4801(const std::string &name)
{
    return std::make_unique<nts::RandomAccess>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::create2716(const std::string &name)
{
    return std::make_unique<nts::RomComponent>(name);
}

std::unique_ptr<nts::IComponent> nts::ComponentFactory::createLogger(const std::string &name)
{
    return std::make_unique<nts::LoggerComponent>(name);
}
