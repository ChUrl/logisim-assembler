//
// Created by christoph on 20.03.23.
//

#include "Node.h"

void Node::addChild(std::unique_ptr<Node> child) {
    children.push_back(std::move(child));
}

auto Node::getChildren() const -> const std::vector<std::unique_ptr<Node>> & {
    return children;
}
