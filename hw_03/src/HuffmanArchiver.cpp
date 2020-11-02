#include <cassert>
#include <unordered_map>
#include <deque>

#include "HuffmanArchiver.hpp"
#include "Huffman.hpp"
#include "Trie.hpp"
#include "ByteWriter.hpp"
#include "ByteReader.hpp"

namespace Huffman {

HuffmanArchiver::HuffmanArchiver(std::istream &in_, std::ostream &out_) noexcept : in(in_), out(out_) {}

IO::Statistics HuffmanArchiver::compress() {
	std::unordered_map<unsigned char, std::size_t> symbols_frequency;
	IO::ByteReader reader(in);

	std::size_t text_size = 0;
	while (in.peek() != EOF) {
		unsigned char symbol = reader.read_symbol();
		symbols_frequency[symbol]++;
		++text_size;
	}
	reader.drop();

	IO::ByteWriter writer(out);
	writer.write_text_size(text_size);
	HuffmanTree tree(symbols_frequency);
	std::unordered_map<unsigned char, std::deque<bool> > symbols_code = tree.find_symbols_code();

	for (std::size_t ind = 0; ind < 256; ++ind) {
		unsigned char symbol = static_cast<unsigned char>(ind);
		if (symbols_code.count(symbol) == 0) {
			writer.write(static_cast<unsigned char>('0'));
		} else {
			writer.write(static_cast<unsigned char>('1'));
			writer.write(static_cast<unsigned char>(symbols_code[symbol].size()));
			writer.write(symbols_code[symbol]);
			writer.pad_to_byte_and_write();
		}
	}
	writer.finish_additional_data();
	while (in.peek() != EOF) {
		unsigned char symbol = reader.read_symbol();
		writer.write(symbols_code[symbol]);
	}
	writer.pad_to_byte_and_write();
	return writer.get_statistics() + reader.get_statistics();
}

IO::Statistics HuffmanArchiver::extract() {
	Trie trie{};
	IO::ByteReader reader(in);
	std::size_t text_size = reader.read_text_size();

	for (std::size_t ind = 0; ind < 256; ++ind) {
		unsigned char byte = reader.read_symbol();
		if (byte == static_cast<unsigned char>('0')) {
			continue;
		}
		assert(byte == static_cast<unsigned char>('1'));
		std::size_t bit_cnt = static_cast<std::size_t>(reader.read_symbol());
		std::size_t cur_bit_cnt = 0;
		std::deque<bool> code;
		while (cur_bit_cnt < bit_cnt) {
			auto byte = reader.read_byte();
			while (!byte.empty() && cur_bit_cnt < bit_cnt) {
				++cur_bit_cnt;
				code.push_back(byte.front()); 
				byte.pop_front();
			}
		}
		trie.add_node(static_cast<unsigned char>(ind), std::move(code));
	}
	reader.finish_additional_data();

	IO::ByteWriter writer(out);
	TrieNode *node = trie.get_root();
	std::size_t cnt_symbols = 0;
	while (in.peek() != EOF && cnt_symbols < text_size) {
		auto byte = reader.read_byte();
		while (!byte.empty() && cnt_symbols < text_size) {
			node = node->go(byte);
			assert(node != nullptr);
			if (node->symbol.has_value()) {
				writer.write(node->symbol.value());
				++cnt_symbols;
				node = trie.get_root();
			}
		}
	}
	return writer.get_statistics() + reader.get_statistics();
}

} //namespace Huffman