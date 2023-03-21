//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_POSTFIXOBSERVER_H
#define LOGISIMASSEMBLER_POSTFIXOBSERVER_H

#include "Observer.h"

class PostfixObserver : public Observer {
public:
    PostfixObserver(const Node &root);

    ~PostfixObserver() override = default;

protected:
    void traverse(const Node &node) override;

protected:
    uint32_t depth = 0;
};

#endif //LOGISIMASSEMBLER_PREFIXOBSERVER_H
