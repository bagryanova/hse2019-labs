#pragma once

#include <iostream>
#include <deque>

#include "Statistics.hpp"

namespace IO {

class ByteWriter final {
public:
	explicit ByteWriter(std::ostream &out_) noexcept;
	~ByteWriter();
	std::deque<bool> get_buffer() const noexcept;
	Statistics get_statistics() const noexcept;

	void write(unsigned char symbol);
	void write(const std::deque<bool> &code);
	void pad_to_byte_and_write();
	void write_text_size(std::size_t size);
	void finish_additional_data() noexcept;
private:
	std::ostream &out;
	std::deque<bool> buffer;
	Statistics statistics;

	void write_bytes_if_can();
};

} //namespace IO