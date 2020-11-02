#include <cassert>

#include "Trie.hpp"

namespace Huffman {

TrieNode *Trie::get_root() const {
	return root.get();
}

void Trie::add_node(unsigned char symbol, std::deque<bool> code) {
	if (root == nullptr) {
		root = std::make_unique<TrieNode>();
	}
	TrieNode* cur = root.get();
	while(!code.empty()) {
		if (code.front() == false) {
			if (cur->left == nullptr) {
				cur->left = std::make_unique<TrieNode>();
			}
			cur = cur->left.get();
		} else {
			if (cur->right == nullptr) {
				cur->right = std::make_unique<TrieNode>();
			}
			cur = cur->right.get();
		}
		code.pop_front();
	}
	cur->symbol = std::make_optional(symbol);
}

TrieNode *TrieNode::go(std::deque<bool> &byte) {
	if (symbol.has_value() || byte.empty()) {
		return this;
	}
	if (byte.front()) {
		byte.pop_front();
		assert(right != nullptr);
		return right.get()->go(byte);
	} else {
		byte.pop_front();
		assert(left != nullptr);
		return left.get()->go(byte);
	}
}

} //namespace Huffman