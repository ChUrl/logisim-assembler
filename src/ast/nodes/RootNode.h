//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_ROOTNODE_H
#define LOGISIMASSEMBLER_ROOTNODE_H

#include "../Node.h"

class RootNode : public Node {
public:
    RootNode() = default;

    ~RootNode() override = default;

    [[nodiscard]] auto compile() const -> uint8_t override;
};

#endif //LOGISIMASSEMBLER_ROOTNODE_H
