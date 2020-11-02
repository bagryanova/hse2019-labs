#include <iostream>
#include <deque>
#include <cassert>

#include "ByteWriter.hpp"

namespace IO {

ByteWriter::ByteWriter(std::ostream &out_) noexcept : out(out_) {}

ByteWriter::~ByteWriter() {
	assert(buffer.size() == 0);
}

std::deque<bool> ByteWriter::get_buffer() const noexcept {
	return buffer;
}

Statistics ByteWriter::get_statistics() const noexcept {
	return statistics;
}

void ByteWriter::pad_to_byte_and_write() {
	std::size_t remainder = buffer.size() % 8;
	if (remainder == 0) {
		return;
	}
	while (remainder < 8) {
		buffer.push_back(false);
		++remainder;
	}
	write_bytes_if_can();
	assert(buffer.size() == 0);
}

void ByteWriter::write_bytes_if_can() {
	while (buffer.size() >= 8) {
		uint8_t byte = 0;
		for (std::size_t ind = 0; ind < 8; ++ind) {
			byte |= (static_cast<uint8_t>(buffer.front()) << (8 - ind - 1));
			buffer.pop_front();
		}
		out.put(static_cast<char>(byte));
		++statistics.output_data;
	}
}

void ByteWriter::write(unsigned char symbol) {
	assert(buffer.size() == 0);
	uint8_t uint_symbol = static_cast<uint8_t>(symbol);
	for (std::size_t ind = 0; ind < 8; ++ind) {
		buffer.push_back(static_cast<bool>(uint_symbol & (1u << (8 - ind - 1))));
	}
	write_bytes_if_can();
}

void ByteWriter::write(const std::deque<bool> &code) {
	for (std::size_t ind = 0; ind < code.size(); ++ind) {
		buffer.push_back(code[ind]);
	}
	write_bytes_if_can();
}

void ByteWriter::write_text_size(std::size_t size) {
	std::deque<bool> byte_size;
	for (std::size_t ind = 0; ind < 32; ++ind) {
		byte_size.push_front(static_cast<bool>(size & (1u << ind)));
	}
	write(byte_size);
	assert(buffer.size() == 0);
}

void ByteWriter::finish_additional_data() noexcept {
	assert(statistics.input_data == 0);
	statistics.additional_data = statistics.output_data;
	statistics.output_data = 0;
}

} //namespace IO