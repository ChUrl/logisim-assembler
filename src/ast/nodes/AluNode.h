//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_ALUNODE_H
#define LOGISIMASSEMBLER_ALUNODE_H

#include "../Node.h"

class AluNode : public Node {
public:
    enum AluOperation : uint8_t {
        AND,
        OR,
        NAND,
        NOR,
        ADD,
        SUB
    };

public:
    AluNode(AluOperation operation);

    ~AluNode() override = default;

    [[nodiscard]] auto compile() const -> uint8_t override;

private:
    AluOperation operation;
};

#endif //LOGISIMASSEMBLER_ALUNODE_H
