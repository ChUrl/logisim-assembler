//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_MOVNODE_H
#define LOGISIMASSEMBLER_MOVNODE_H

#include "../Node.h"

class MovNode : public Node {
public:
    MovNode(uint8_t source, uint8_t target);

    ~MovNode() override = default;

    [[nodiscard]] auto compile() const -> uint8_t override;

private:
    uint8_t source;
    uint8_t target;
};

#endif //LOGISIMASSEMBLER_MOVNODE_H
