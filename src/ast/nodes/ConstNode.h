//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_CONSTNODE_H
#define LOGISIMASSEMBLER_CONSTNODE_H

#include "../Node.h"

class ConstNode : public Node {
public:
    ConstNode(uint8_t value);

    ~ConstNode() override = default;

    [[nodiscard]] auto compile() const -> uint8_t override;

private:
    uint8_t value;
};

#endif //LOGISIMASSEMBLER_CONSTNODE_H
