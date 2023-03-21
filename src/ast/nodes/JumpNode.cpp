//
// Created by christoph on 21.03.23.
//

#include "JumpNode.h"

JumpNode::JumpNode(JumpNode::JumpOperation operation) : operation(operation) {}

uint8_t JumpNode::compile() const {
    return (CONDITION & 0b11) << 6 | (operation & 0b111);
}
