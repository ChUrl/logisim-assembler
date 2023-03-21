//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_NODE_H
#define LOGISIMASSEMBLER_NODE_H

#include <vector>
#include <memory>
#include "../lexer/Token.h"

class Node {
public:
    Node() = default;

    Node(const Node &copy) = default;

    auto operator=(const Node &copy) -> Node & = default;

    Node(Node &&move) = default;

    auto operator=(Node &&move) -> Node & = default;

    virtual ~Node() = default;

    void addChild(std::unique_ptr<Node> child);

    [[nodiscard]] virtual auto compile() const -> uint8_t = 0;

    [[nodiscard]] auto getChildren() const -> const std::vector<std::unique_ptr<Node>> &;

protected:
    enum Operation : uint8_t {
        CONSTANT,
        ALU,
        COPY,
        CONDITION
    };

protected:
    std::vector<std::unique_ptr<Node>> children;
};

#endif //LOGISIMASSEMBLER_NODE_H
