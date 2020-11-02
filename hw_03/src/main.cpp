#include <iostream>
#include <fstream>
#include <exception>

#include "CLI.hpp"
#include "HuffmanArchiver.hpp"
#include "Statistics.hpp"

int main(int argc, const char *argv[]) {
	try {
    	CLI::CLI cli(argc, argv);
    	std::ifstream in(std::string(cli.input_file_name), std::istream::binary);
    	std::ofstream out(std::string(cli.output_file_name), std::ostream::binary);

    	Huffman::HuffmanArchiver archiver(in, out);
        IO::Statistics statistics;
    	if (cli.archive_option == CLI::ArchiveOption::ARCHIVE) {
    		statistics = archiver.compress();
    	} else {
    		statistics = archiver.extract();
    	}
    	std::cout << statistics << std::endl;
    } catch (const std::exception &e) {
    	std::cout << e.what() << std::endl;
    	return 1;
    } catch (...) {
    	std::cout << "Unknown error." << std::endl;
    	return 1;
    }
    return 0;
}