//
// Created by christoph on 20.03.23.
//

#ifndef LOGISIMASSEMBLER_PREFIXOBSERVER_H
#define LOGISIMASSEMBLER_PREFIXOBSERVER_H

#include "Observer.h"

class PrefixObserver : public Observer {
public:
    PrefixObserver(const Node &root);

    ~PrefixObserver() override = default;

protected:
    void traverse(const Node &node) override;

protected:
    uint32_t depth = 0;
};

#endif //LOGISIMASSEMBLER_PREFIXOBSERVER_H
