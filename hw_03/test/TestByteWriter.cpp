#include <sstream>
#include <deque>

#include "doctest.h"
#include "ByteWriter.hpp"

namespace Test {

TEST_CASE("ByteWriter tests") {
	SUBCASE("write symbol") {
		unsigned char symbol = 'a';
		std::stringstream ss;
		IO::ByteWriter writer(ss);
		CHECK(writer.get_statistics().output_data == 0);
		CHECK(writer.get_statistics().additional_data == 0);
		CHECK(writer.get_statistics().input_data == 0);
		writer.write(symbol);
		char result;
		ss.get(result);
		CHECK(static_cast<unsigned char>(result) == symbol);
		CHECK(ss.peek() == EOF);
		CHECK(writer.get_statistics().output_data == 1);
		CHECK(writer.get_statistics().additional_data == 0);
		CHECK(writer.get_statistics().input_data == 0);
		CHECK(writer.get_buffer().empty());
	}
	SUBCASE("write additional symbol") {
		unsigned char symbol = 'a';
		std::stringstream ss;
		IO::ByteWriter writer(ss);
		CHECK(writer.get_statistics().output_data == 0);
		CHECK(writer.get_statistics().additional_data == 0);
		CHECK(writer.get_statistics().input_data == 0);
		writer.write(symbol);
		writer.finish_additional_data();
		char result;
		ss.get(result);
		CHECK(static_cast<unsigned char>(result) == symbol);
		CHECK(ss.peek() == EOF);
		CHECK(writer.get_statistics().output_data == 0);
		CHECK(writer.get_statistics().additional_data == 1);
		CHECK(writer.get_statistics().input_data == 0);
		CHECK(writer.get_buffer().empty());
	}
	SUBCASE("pad to byte and write") {
		std::deque<bool> code = {0, 0, 0, 1, 1, 1};
		std::stringstream ss;
		IO::ByteWriter writer(ss);
		writer.write(code);
		writer.pad_to_byte_and_write(); 
		uint8_t must_int = 0b000'111'00;
		std::stringstream must;
		must << must_int;
		CHECK(ss.str() == must.str());
		CHECK(writer.get_buffer().size() == 0);
		CHECK(writer.get_statistics().output_data == 1);
		CHECK(writer.get_statistics().additional_data == 0);
		CHECK(writer.get_statistics().input_data == 0);
	}
	SUBCASE("write code") {
		std::deque<bool> code = {0, 0, 0, 1, 1, 1};
		std::stringstream ss;
		IO::ByteWriter writer(ss);
		writer.write(code);
		writer.write(code);
		uint8_t must_int = 0b000'111'00;
		std::stringstream must;
		must << must_int;
		CHECK(ss.str() == must.str());
		CHECK(writer.get_buffer() == std::deque<bool>{0, 1, 1, 1});
		CHECK(writer.get_statistics().output_data == 1);
		CHECK(writer.get_statistics().additional_data == 0);
		CHECK(writer.get_statistics().input_data == 0);
		writer.pad_to_byte_and_write(); 
	}
}

} //namespace Test