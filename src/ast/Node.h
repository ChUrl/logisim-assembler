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

    // TODO: For more complex instructions, compile needs to return a vector<uint8_t>
    // TODO: In this case, the Observer may not traverse all nodes...
    //       The Observer is the wrong choice for compilation.
    //       I can just call compile on the root, and the root compiles its children.
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
    // TODO: Currently the AST degrades to a list, but someday we'll need a real tree
    std::vector<std::unique_ptr<Node>> children;
};

#endif //LOGISIMASSEMBLER_NODE_H
