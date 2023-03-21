//
// Created by christoph on 21.03.23.
//

#ifndef LOGISIMASSEMBLER_CODEGENOBSERVER_H
#define LOGISIMASSEMBLER_CODEGENOBSERVER_H

#include "../ast/PostfixObserver.h"

class CodegenObserver : public PostfixObserver {
public:
    CodegenObserver(const Node &node, std::vector<std::string> &output_string);

    ~CodegenObserver() override = default;

protected:
    void action(const Node &node) override;

private:
    std::vector<std::string> &output_string;
};

#endif //LOGISIMASSEMBLER_CODEGENOBSERVER_H
