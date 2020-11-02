#include <string_view>

#include "CLI.hpp"

namespace CLI {

CLI::CLI(int argc, const char *argv[]) {
	int ind = 1;
	while (ind < argc) {
		std::string_view option(argv[ind]);
		if (option == "-c") {
			if (archive_option == ArchiveOption::NOTHING) {
				archive_option = ArchiveOption::ARCHIVE;
			} else {
				throw CLIException("Extra flag.");
			}
		} else if (option == "-u") {
			if (archive_option == ArchiveOption::NOTHING) {
				archive_option = ArchiveOption::UNARCHIVE;
			} else {
				throw CLIException("Extra flag.");
			}
		} else if (option == "-f" || option == "--file") {
			if (input_file_name.length() > 0) {
				throw CLIException("Extra flag.");
			}
			++ind;
			if (ind == argc) {
				throw CLIException("Missing input file name.");
			}
			input_file_name = argv[ind];
		} else if (option == "-o" || option == "--output") {
			if (output_file_name.length() > 0) {
				throw CLIException("Extra flag.");
			}
			++ind;
			if (ind == argc) {
				throw CLIException("Missing output file name.");
			}
			output_file_name = argv[ind];
		} else {
			throw CLIException("Unknow flag.");
		}
		++ind;
	}
	if (archive_option == ArchiveOption::NOTHING) {
		throw CLIException("Missing archive flag.");
	}
	if (input_file_name.length() == 0) {
		throw CLIException("Missing input file name flag.");
	}
	if (output_file_name.length() == 0) {
		throw CLIException("Missing output file name flag.");
	}
}

} //namespace CLI
