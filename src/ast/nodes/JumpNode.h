//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_JUMPNODE_H
#define LOGISIMASSEMBLER_JUMPNODE_H

#include "../Node.h"

class JumpNode : public Node {
public:
    enum JumpOperation : uint8_t {
        NEVER,
        EQUAL_ZERO,
        LESS_ZERO,
        LESS_EQUAL_ZERO,
        ALWAYS,
        NOT_ZERO,
        GREATER_ZERO,
        GREATER_EQUAL_ZERO
    };

public:
    JumpNode(JumpOperation operation);

    ~JumpNode() override = default;

    [[nodiscard]] auto compile() const -> uint8_t override;

private:
    JumpOperation operation;
};

#endif //LOGISIMASSEMBLER_JUMPNODE_H
