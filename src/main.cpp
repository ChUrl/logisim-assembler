#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <iomanip>
#include "lexer/Lexer.h"
#include "ast/Node.h"
#include "parser/Parser.h"
#include "codegen/PrintObserver.h"

namespace po = boost::program_options;

auto lex(std::string_view input_string, std::vector<Token> &tokens) -> bool {
    Lexer lexer(input_string);
    while (true) {
        Token token = lexer.next();
        std::cout << std::setw(10) << token.getTypeName() << ": " << static_cast<std::string_view>(token) << std::endl;

        if (token.getType() == Token::UNEXPECTED) {
            return false;
        }

        tokens.push_back(std::move(token));

        if (tokens.back().getType() == Token::END) {
            return true;
        }
    }
}

auto parse(std::vector<Token> &tokens) -> std::unique_ptr<Node> {
    Parser parser(tokens);
    return std::move(parser.parse());
}

auto main(int argc, char **argv) -> int {
    // Argument parsing straight from the Boost manual: https://www.boost.org/doc/libs/1_60_0/doc/html/program_options/tutorial.html

    // Declare the supported options.
    po::options_description desc("Allowed options");

    // TODO: What the fuck is this syntax?
    desc.add_options()
            ("help,h", "Show this help message")
            ("input,i", po::value<std::string>(), "Input file")
            ("output,o", po::value<std::string>(), "Output file");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }
    if (!vm.count("input")) {
        std::cout << "Did not provide input file!" << std::endl;
        return -1;
    }
    if (!vm.count("output")) {
        std::cout << "Did not provide output file!" << std::endl;
        return -1;
    }

    std::cout << "Input File: " << vm["input"].as<std::string>() << std::endl;
    std::cout << "Output File: " << vm["output"].as<std::string>() << std::endl;

    // Read the input file
    std::ifstream ifs;
    std::string input_string;
    ifs.open(vm["input"].as<std::string>(), std::ios_base::in);
    if (!ifs) {
        std::cout << "Failed to read input file!" << std::endl;
        return -1;
    }
    while (!ifs.eof()) {
        std::string line;
        getline(ifs, line);
        input_string += line + '\n';
    }
    ifs.close();

    // Lexing
    std::cout << "Lexing:" << std::endl;
    std::vector<Token> tokens;
    if (!lex(input_string, tokens)) {
        std::cout << "Lexer Error: Unexpected Token!" << std::endl;
        return -1;
    }

    // Parsing
    std::cout << "Parsing:" << std::endl;
    const std::unique_ptr<Node> ast = parse(tokens);

    PrintObserver(*ast).Observer::traverse();

    return 0;
}
