#pragma once

#include <string_view>
#include <stdexcept>

namespace CLI {

enum class ArchiveOption {
	ARCHIVE,
	UNARCHIVE, 
	NOTHING
};

struct CLI final {
public:
	ArchiveOption archive_option = ArchiveOption::NOTHING;
	std::string_view input_file_name;
	std::string_view output_file_name;

	CLI(int argc, const char *argv[]);
};

class CLIException final : public std::logic_error {
	using std::logic_error::logic_error;
};

} //namespace CLI