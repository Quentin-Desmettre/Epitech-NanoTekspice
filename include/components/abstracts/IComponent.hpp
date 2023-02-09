/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

namespace nts {
    class IComponent;
}

using UniqueIComponent = std::unique_ptr<nts::IComponent>;
using SharedIComponent = std::shared_ptr<nts::IComponent>;

namespace nts
{
    enum Tristate
    {
        Undefined = (-true),
        True = true,
        False = false
    };

    enum PinType {
        INPUT,
        OUTPUT,
        UNUSED,
        ERROR,
        BOTH
    };

    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual void simulate(std::size_t tick) = 0;
        virtual nts::Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
        virtual std::string getName() const = 0;
        virtual nts::PinType getPinType(std::size_t pin) const = 0;
    };

    class Pin {
    public:
        Pin() {
            component = nullptr;
            nb = 0;
        };
        void setComponent(IComponent *component) {
            if (this->component)
                throw std::runtime_error("Pin::setComponent: component already set");
            this->component = component;
            this->nb = nb;
        }
        void setPin(std::size_t nb) {
            this->nb = nb;
        }

        IComponent *getComponent() const {
            return component;
        }
        std::size_t getPin() const {
            return nb;
        }
    private:
        IComponent *component;
        std::size_t nb;
    };

    struct InputOutputRest {
        std::vector<UniqueIComponent> input;
        std::vector<UniqueIComponent> output;
        std::vector<UniqueIComponent> log;
        std::vector<UniqueIComponent> other;
    };
}

#endif /* !ICOMPONENT_HPP_ */
