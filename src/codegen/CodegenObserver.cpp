//
// Created by christoph on 21.03.23.
//

#include "CodegenObserver.h"
#include <boost/format.hpp>
#include <iostream>

CodegenObserver::CodegenObserver(const Node &node, std::vector<std::string> &output_string)
        : PostfixObserver(node), output_string(output_string) {}

void CodegenObserver::action(const Node &node) {
    const uint8_t dec = node.compile();
    const uint8_t INVALID = -1;

    if (dec != INVALID) {
        // uint8_t is always interpreted as char, so cast to uint32_t
        const std::string hex = (boost::format("%x") % static_cast<uint32_t>(dec)).str();
        if (hex.empty() || hex.size() > 2) {
            throw "Compile Error: Resulting instruction has invalid size!";
        }
        output_string.push_back(hex.length() == 2 ? hex : "0" + hex);
    }
}
