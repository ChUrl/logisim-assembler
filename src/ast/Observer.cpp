//
// Created by christoph on 21.03.23.
//

#include "Observer.h"

Observer::Observer(const Node &root) : root(root) {}

void Observer::traverse() {
    traverse(root);
}
