/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-tekspice-quentin.desmettre
** File description:
** RandomAccess
*/

#ifndef RANDOMACCESS_HPP_
#define RANDOMACCESS_HPP_
#include "AComponent.hpp"
#include <map>

namespace nts {
    class RandomAccess: public AComponent<0, 0> {
        public:
            RandomAccess(const std::string &name);
            ~RandomAccess() = default;

            nts::PinType getPinType(std::size_t pin) const override;
            void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;
            nts::Tristate compute(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        protected:
        private:
            nts::Tristate computeInput(std::size_t pin) override;
            std::size_t getAddress();
            void writeData(std::size_t address);
            std::map<std::size_t, nts::Pin> _inputMap, _outputMap, _unusedMap;
            bool _hasWrittenData;

            nts::Tristate _ram[1024];
    };
};

/*

# 1024 Bytes RAM (4801)
#
#            addr_4 -4-+ +-3- addr_5
#          addr_3 -5-+ | | +-2- addr_6
#        addr_2 -6-+ | | | | +-1- addr_7
#      addr_1 -7-+ | | | | | | +-23- addr_8
#    addr_0 -8-+ | | | | | | | | +-22- addr_9
#              | | | | | | | | | |
#            +-v-v-v-v-v-v-v-v-v-v-+
#            |                     |
# enable -18->                ign -<-12-
#            |                     |
#  write -21->                ign -<-19-
#            |                     |
#   read -20->                ign -<-24-
#            | 4801 RAM            |
#            +---o-o-o-o-o-o-o-o---+
#                | | | | | | | |
#    in/out_0 -9-+ | | | | | | +-17- in/out_7
#     in/out_1 -10-+ | | | | +-16- in/out_6
#       in/out_2 -11-+ | | +-15- in/out_5
#         in/out_3 -13-+ +-15- in/out_4

pins 8-1 / 23-22 are address pins

18 - enable:
    0: All outputs are 0, do not write in RAM
    1: Normal behavior
    U: Do nothing

21 - write:
    0: Read RAM at address
    1: Write to RAM at address
    U: Do nothing

20 - read:
    0: Write to RAM at address
    1: Read RAM at address
    U: Do nothing

If read/write are incompatible -> Do nothing


A chaque simulate, si tick > 0, ecrire dans la RAM
Pour les compute, simplement read la RAM

Pour pouvoir gérer input/output sur les meme pins:
    getPinType(pin) -> INPUT / OUTPUT / BOTH
    en attributs:
        _inputMap: std::map<std::size_t pin, nts::Pin> = {
            9: {0x23456, 1},
            ...
        }
        _outputMap: std::map<std::size_t pin, nts::Pin> = {
            9: {0x23456, 1},
            ...
        }

    setLink:
        if getPinType(pin) == INPUT:
            _inputMap[pin] = {other, otherPin}
        else if getPinType(pin) == BOTH:
            if other.getPinType(otherPin) == INPUT:
                _outputMap[pin] = {other, otherPin}
            else:
                _inputMap[pin] = {other, otherPin}
        else:
            _usedUnusedPins[pin] = {other, otherPin}
*/

#endif /* !RANDOMACCESS_HPP_ */
