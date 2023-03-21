//
// Created by christoph on 21.03.23.
//

#include "RegNode.h"

RegNode::RegNode(uint8_t reg) : reg(reg) {}

auto RegNode::compile() const -> uint8_t {
    if (reg > 0b110) {
        throw "Compile Error: Invalid Register!";
    }

    return -1;
}

auto RegNode::getRegister() const -> uint8_t {
    return reg;
}
