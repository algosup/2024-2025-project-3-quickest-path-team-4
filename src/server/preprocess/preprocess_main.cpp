#include <iostream>
#include <fstream>
#include <string>
#include "csv_parser.h"
#include "binary_writer.h"
#include "preprocess_main.h" // Include the header file

#ifndef SERVER_MODE
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_csv_file> <output_binary_file>" << std::endl;
        return 1;
    }

    // Specify the path to the CSV file in the server directory
    const std::string input_csv_file = std::string(argv[1]);
    // Specify the path to the output binary file in the server directory
    const std::string output_binary_file = "../" + std::string(argv[2]);

    // Debugging output to verify file paths
    std::cout << "Input CSV file: " << input_csv_file << std::endl;
    std::cout << "Output binary file: " << output_binary_file << std::endl;

    return preprocess_main(argc, argv);
}
#endif