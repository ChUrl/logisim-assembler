//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_PRINTOBSERVER_H
#define LOGISIMASSEMBLER_PRINTOBSERVER_H

#include "../ast/PrefixObserver.h"

class PrintObserver : public PrefixObserver {
public:
    PrintObserver(const Node &node);

    ~PrintObserver() override = default;

protected:
    void action(const Node &node) override;
};

#endif //LOGISIMASSEMBLER_PRINTOBSERVER_H
