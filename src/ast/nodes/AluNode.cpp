//
// Created by christoph on 21.03.23.
//

#include "AluNode.h"

AluNode::AluNode(AluNode::AluOperation operation) : operation(operation) {}

auto AluNode::compile() const -> uint8_t {
    if (operation > SUB) {
        throw "Compile Error: Invalid ALU Operation!";
    }

    return (ALU & 0b11) << 6 | (operation & 0b111);
}
