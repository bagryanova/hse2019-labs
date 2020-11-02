#include <string_view>
#include <string>
#include <deque>

#include "doctest.h"
#include "Trie.hpp"

namespace Test {

TEST_CASE("Trie tests") { //abacabad
	Huffman::Trie trie{};
	trie.add_node(static_cast<unsigned char>('a'), std::deque<bool>{0});
	trie.add_node(static_cast<unsigned char>('c'), std::deque<bool>{1, 1, 0});
	trie.add_node(static_cast<unsigned char>('d'), std::deque<bool>{1, 1, 1});
	trie.add_node(static_cast<unsigned char>('b'), std::deque<bool>{1, 0});

	std::deque<bool> bin_text = {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1};

	std::string text;
	while (!bin_text.empty()) {
		Huffman::TrieNode *node = trie.get_root()->go(bin_text);
		CHECK(node->symbol.has_value());
		text += node->symbol.value();
	}
	CHECK(text == "abacabad");
}

} //namespace Test