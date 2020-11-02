#pragma once

#include <optional>
#include <deque>
#include <memory>

namespace Huffman {

struct TrieNode final {
	std::optional<unsigned char> symbol;
	std::unique_ptr<TrieNode> left, right;
	TrieNode *go(std::deque<bool> &byte);
};

class Trie final {
private:
	std::unique_ptr<TrieNode> root;
public:
	TrieNode *get_root() const;
	void add_node(unsigned char symbol, std::deque<bool> code);
};

} //namespace Huffman