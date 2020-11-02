#include <string_view>
#include <sstream>

#include "doctest.h"
#include "HuffmanArchiver.hpp"

namespace Test {

void end_to_end_test(const std::string_view &text) {
	std::stringstream in;
	in << text;
	std::stringstream bin_out;
	Huffman::HuffmanArchiver compress_archiver(in, bin_out);
	IO::Statistics input_statistics = compress_archiver.compress();

	CHECK(bin_out.str().size() == input_statistics.output_data + input_statistics.additional_data);

	std::stringstream text_out;
	bin_out.seekg(0);
	Huffman::HuffmanArchiver extract_archiver(bin_out, text_out);
	IO::Statistics output_statistics = extract_archiver.extract();

	CHECK(text_out.str() == text);
	CHECK(input_statistics.input_data == output_statistics.output_data);
	CHECK(input_statistics.output_data == output_statistics.input_data);
	CHECK(input_statistics.additional_data == output_statistics.additional_data);

}

TEST_CASE("HuffmanArchiver end-to-end tests") {
	SUBCASE("Easy") {
		end_to_end_test("abacabad");
	}
	SUBCASE("One symbol") {
		std::string s = "";
		for (std::size_t ind = 0; ind < 1000; ++ind) {
			s += "a";
		}
		end_to_end_test(s);
	}
	SUBCASE("Long") {
		std::string s = "";
		for (std::size_t ind = 0; ind < 100000; ++ind) {
			if (ind & 1) {
				s += "a";
			} else {
				s += "b";
			}
		}
		end_to_end_test(s);
	}
	SUBCASE("Empty") {
		end_to_end_test("");
	}
	SUBCASE("Test") {
		end_to_end_test("abacabafkljdklvzscbkjshzbcv;dvlk.");
	}
}

} //namespace Test