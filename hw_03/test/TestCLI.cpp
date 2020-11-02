#include <string_view>

#include "doctest.h"
#include "CLI.hpp"

namespace Test {

TEST_CASE("CLI tests") {
	SUBCASE("correct input 1") {
		const char *argv[] = {"./hw_03", "-c", "-f", "myfile.txt", "-o", "result.bin"};
		CLI::CLI cli(std::size(argv), argv);
		CHECK(cli.input_file_name == "myfile.txt");
		CHECK(cli.output_file_name == "result.bin");
		CHECK(cli.archive_option == CLI::ArchiveOption::ARCHIVE);
	}
	SUBCASE("correct input 2") {
		const char *argv[] = {"./hw_03", "-u", "-f", "result.bin", "-o", "myfile.txt"};
		CLI::CLI cli(std::size(argv), argv);
		CHECK(cli.input_file_name == "result.bin");
		CHECK(cli.output_file_name == "myfile.txt");
		CHECK(cli.archive_option == CLI::ArchiveOption::UNARCHIVE);
	}
}

} //namespace Test