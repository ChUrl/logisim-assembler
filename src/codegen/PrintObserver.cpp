//
// Created by christoph on 21.03.23.
//

#include <iostream>
#include "PrintObserver.h"

PrintObserver::PrintObserver(const Node &node) : PrefixObserver(node) {}

void PrintObserver::action(const Node &node) {
    // Print a simple indent guide
    std::string depth_padding(depth * 2, '|');
    if (depth > 0) {
        for (uint32_t i = 0; i < depth_padding.length(); ++i) {
            if (i % 2 == 1) {
                depth_padding[i] = ' ';
            }
        }
        depth_padding[(depth * 2) - 1] = '-';
    }

    std::cout << depth_padding << typeid(node).name() << std::endl;
}
