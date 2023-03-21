//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_MOVNODE_H
#define LOGISIMASSEMBLER_MOVNODE_H

#include "../Node.h"

class MovNode : public Node {
public:
    MovNode(std::unique_ptr<Node> source, std::unique_ptr<Node> target);

    ~MovNode() override = default;

    auto source() const -> Node &;

    auto target() const -> Node &;

    [[nodiscard]] auto compile() const -> uint8_t override;
};

#endif //LOGISIMASSEMBLER_MOVNODE_H
