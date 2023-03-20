#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include "lexer/Lexer.h"

namespace po = boost::program_options;

int main(int argc, char **argv) {
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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
