//
// Created by christoph on 21.03.23.
//

#include "ConstNode.h"

ConstNode::ConstNode(uint8_t value) : value(value) {}

auto ConstNode::compile() const -> uint8_t {
    if (value > 0b00111111) {
        throw "Compile Error: Constant too large!";
    }

    return (CONSTANT & 0b11) << 6 | (value & 0b111111);
}
