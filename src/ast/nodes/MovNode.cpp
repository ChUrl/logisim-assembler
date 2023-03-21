//
// Created by christoph on 21.03.23.
//

#include "MovNode.h"

MovNode::MovNode(std::unique_ptr<Node> source, std::unique_ptr<Node> target) {
    children.push_back(std::move(source));
    children.push_back(std::move(target));
}

auto MovNode::source() const -> Node & {
    return *children[0];
}

auto MovNode::target() const -> Node & {
    return *children[1];
}

auto MovNode::compile() const -> uint8_t {
    return (COPY & 0b11) << 6 | (source().compile() & 0b111) << 3 | (target().compile() & 0b111);
}
