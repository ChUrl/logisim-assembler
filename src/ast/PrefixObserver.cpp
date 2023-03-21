//
// Created by christoph on 20.03.23.
//

#include "PrefixObserver.h"

PrefixObserver::PrefixObserver(const Node &root) : Observer(root) {}

// TODO: Shouldn't be recursive
void PrefixObserver::traverse(const Node &node) {
    action(node);

    for (const auto &child : node.getChildren()) {
        depth++;
        traverse(*child);
        depth--;
    }
}
