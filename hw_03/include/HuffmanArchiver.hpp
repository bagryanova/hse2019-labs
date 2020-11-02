#pragma once

#include <string_view>
#include <iostream>
#include <deque>
#include <unordered_map>

#include "Statistics.hpp"
#include "ByteWriter.hpp"

namespace Huffman {

class HuffmanArchiver final {
public:
	explicit HuffmanArchiver(std::istream &in_, std::ostream &out_) noexcept;

	IO::Statistics compress();
	IO::Statistics extract();
private:
	std::istream &in;
	std::ostream &out;
	IO::Statistics statistics;

	std::unordered_map<unsigned char, std::size_t> count_symbols_frequency();
};

} //namespace Huffman