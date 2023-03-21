//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_REGNODE_H
#define LOGISIMASSEMBLER_REGNODE_H

#include "../Node.h"

class RegNode : public Node {
public:
    RegNode(uint8_t reg);

    ~RegNode() override = default;

    [[nodiscard]] auto compile() const -> uint8_t override;

private:
    uint8_t reg;
};

#endif //LOGISIMASSEMBLER_REGNODE_H
