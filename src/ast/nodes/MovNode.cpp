//
// Created by christoph on 21.03.23.
//

#include "MovNode.h"

MovNode::MovNode(uint8_t source, uint8_t target) : source(source), target(target) {}

auto MovNode::compile() const -> uint8_t {
    return (COPY & 0b11) << 6 | (source & 0b111) << 3 | (target & 0b111);
}
