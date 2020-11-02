#include "Statistics.hpp"

namespace IO {

std::ostream& operator<<(std::ostream &out, const Statistics &statistics) {
	out << statistics.input_data << std::endl << statistics.output_data << std::endl << statistics.additional_data;
	return out;
}

Statistics operator+(const Statistics &left, const Statistics &right) {
	Statistics result;
	result.input_data = left.input_data + right.input_data;
	result.output_data = left.output_data + right.output_data;
	result.additional_data = left.additional_data + right.additional_data;
	return result;
}

} //namespace IO