//
// Created by christoph on 21.03.23.
//

#include "CodegenObserver.h"
#include <boost/format.hpp>
#include <iostream>

CodegenObserver::CodegenObserver(const Node &node, std::string &output_string)
        : PostfixObserver(node), output_string(output_string) {}

void CodegenObserver::action(const Node &node) {
    const uint8_t opcode = node.compile();
    const uint8_t INVALID = -1;

    if (opcode != INVALID) {
        output_string += (boost::format("%x") % static_cast<uint32_t>(opcode)).str(); // uint8_t is always interpreted as char
        output_string += ' ';
    }
}
