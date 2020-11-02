#pragma once

#include <iostream>

namespace IO {

struct Statistics {
	std::size_t input_data = 0;
	std::size_t output_data = 0;
	std::size_t additional_data = 0;
};

std::ostream& operator<<(std::ostream &out, const Statistics &statistics);

Statistics operator+(const Statistics &left, const Statistics &right);

} //namespace IO