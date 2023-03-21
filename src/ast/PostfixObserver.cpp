//
// Created by christoph on 20.03.23.
//

#include "PostfixObserver.h"

PostfixObserver::PostfixObserver(const Node &root) : Observer(root) {}

// TODO: Shouldn't be recursive
void PostfixObserver::traverse(const Node &node) {
    for (const auto &child : node.getChildren()) {
        depth++;
        traverse(*child);
        depth--;
    }

    action(node);
}
