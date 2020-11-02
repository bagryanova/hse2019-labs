#include <deque>

#include "doctest.h"
#include "Huffman.hpp"

namespace Test {

TEST_CASE("Huffman tests") { //abacabad
	std::unordered_map<unsigned char, std::size_t> symbols_frequency;
	symbols_frequency['a'] = 4;
	symbols_frequency['b'] = 2;
	symbols_frequency['c'] = 1;
	symbols_frequency['d'] = 1;

	Huffman::HuffmanTree tree(symbols_frequency);
	auto symbols_code = tree.find_symbols_code();

	CHECK(symbols_code['a'] == std::deque<bool>{0});
	CHECK(symbols_code['b'] == std::deque<bool>{1, 0});
	CHECK(symbols_code['c'] == std::deque<bool>{1, 1, 0});
	CHECK(symbols_code['d'] == std::deque<bool>{1, 1, 1});
}

} //namespace Test