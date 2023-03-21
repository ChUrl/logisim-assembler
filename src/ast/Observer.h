//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_OBSERVER_H
#define LOGISIMASSEMBLER_OBSERVER_H

#include "Node.h"
#include <memory>

class Observer {
public:
    Observer(const Node &root);

    virtual ~Observer() = default;

    void traverse();

protected:
    virtual void traverse(const Node &node) = 0;

    virtual void action(const Node &node) = 0;

private:
    const Node &root;
};

#endif //LOGISIMASSEMBLER_OBSERVER_H
