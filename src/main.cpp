#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <iomanip>
#include "lexer/Lexer.h"
#include "ast/Node.h"
#include "parser/Parser.h"
#include "codegen/PrintObserver.h"
#include "codegen/CodegenObserver.h"

namespace po = boost::program_options;

auto read(const std::string& input_file, std::string &input_string) -> bool {
    std::ifstream ifs;
    ifs.open(input_file, std::ios_base::in);
    if (!ifs) {
        std::cout << "Failed to open input stream!" << std::endl;
        return false;
    }

    while (!ifs.eof()) {
        std::string line;
        getline(ifs, line);
        input_string += line + '\n';
    }

    ifs.close();
    return true;
}

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

auto write(const std::string &output_file, const std::vector<std::string> &output_string) -> bool {
    if (output_string.size() > 255) {
        std::cout << "Program too large!" << std::endl;
        return false;
    }

    std::ofstream ofs;
    ofs.open(output_file, std::ios_base::out);
    if (!ofs) {
        std::cout << "Failed to open output stream!" << std::endl;
        return false;
    }

    ofs << "v3.0 hex words addressed";
    for (uint32_t i = 0; i <= 255; ++i) {
        if (i % 16 == 0) {
            ofs << std::endl;
            // Print Address
            std::string address = (boost::format("%x") % i).str();
            ofs << (address == "0" ? "00" : address) << ": ";
        }

        if (i < output_string.size()) {
            ofs << output_string[i] << " ";
        } else {
            ofs << "00 ";
        }
    }

    ofs.flush();
    ofs.close();
    return true;
}

auto main(int argc, char **argv) -> int {
    // Argument parsing straight from the Boost manual: https://www.boost.org/doc/libs/1_60_0/doc/html/program_options/tutorial.html
    po::options_description desc("Allowed options");
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
    std::string input_string;
    if (!read(vm["input"].as<std::string>(), input_string)) {
        std::cout << "File Error: Couldn't read file!" << std::endl;
        return -1;
    }

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
    PrintObserver(*ast).Observer::traverse(); // Print the AST

    // Codegen
    std::cout << "Codegen:" << std::endl;
    std::vector<std::string> output_string;
    CodegenObserver(*ast, output_string).Observer::traverse();
    for (const auto &instruction : output_string) {
        std::cout << instruction << std::endl;
    }

    // Write the output file
    if (!write(vm["output"].as<std::string>(), output_string)) {
        std::cout << "File Error: Couldn't write file!" << std::endl;
        return -1;
    }

    return 0;
}
