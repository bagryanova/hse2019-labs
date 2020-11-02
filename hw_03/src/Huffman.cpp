#include <set>
#include <cassert>

#include "Huffman.hpp"

namespace Huffman {

HuffmanNode::HuffmanNode(unsigned char symbol_, std::size_t weight_) noexcept : symbol(symbol_), weight(weight_) {} 

HuffmanNode::HuffmanNode(std::unique_ptr<HuffmanNode> left_, std::unique_ptr<HuffmanNode> right_) noexcept
	: symbol(std::nullopt)
	, weight(left_->weight + right_->weight)
	, left(std::move(left_))
	, right(std::move(right_)) 
	{}

HuffmanNode::HuffmanNode(std::unique_ptr<HuffmanNode> left_) noexcept
	: symbol(std::nullopt)
	, weight(left_->weight)
	, left(std::move(left_))
	{}
													 
struct HuffmanNodeWeightComparator {
	bool operator()(const std::pair<std::unique_ptr<HuffmanNode>, std::size_t> &a, const std::pair<std::unique_ptr<HuffmanNode>, std::size_t> &b) const {
		if (a.first->weight == b.first->weight) {
			return a.second < b.second;
		}
		return a.first->weight < b.first->weight;
	}
};

HuffmanTree::HuffmanTree(std::unordered_map<unsigned char, std::size_t> &symbols_frequency) {
	if (symbols_frequency.empty()) {
		return;
	}
	std::set<std::pair<std::unique_ptr<HuffmanNode>, std::size_t> , HuffmanNodeWeightComparator> sorted_symbols;
	for (auto &[symbol, frequency]: symbols_frequency) {
		sorted_symbols.insert({std::make_unique<HuffmanNode>(symbol, frequency), static_cast<std::size_t>(symbol)});
	}
	std::size_t index = 256;
	while (sorted_symbols.size() > 1) {
		auto first_node = std::move(sorted_symbols.extract(sorted_symbols.begin()).value().first);
		auto second_node = std::move(sorted_symbols.extract(sorted_symbols.begin()).value().first);
		auto new_node = std::make_unique<HuffmanNode>(std::move(first_node), std::move(second_node));
		sorted_symbols.insert({std::move(new_node), index});
		++index;
	}
	if (symbols_frequency.size() == 1) {
		auto first_node = std::move(sorted_symbols.extract(sorted_symbols.begin()).value().first);
		auto new_node = std::make_unique<HuffmanNode>(std::move(first_node));
		sorted_symbols.insert({std::move(new_node), index});
		++index;
	}
	assert(sorted_symbols.size() == 1);
	root = std::move(sorted_symbols.extract(sorted_symbols.begin()).value().first);
}

void HuffmanTree::go_and_find_code(HuffmanNode *node, std::deque<bool> &cur_code, std::unordered_map<unsigned char, std::deque<bool> > &symbols_code) const {
	if (node == nullptr) {
		return;
	}
	if (node->symbol.has_value()) {
		symbols_code[node->symbol.value()] = cur_code;
		return;
	}
	cur_code.push_back(false);
	go_and_find_code(node->left.get(), cur_code, symbols_code);
	cur_code.pop_back();
	cur_code.push_back(true);
	go_and_find_code(node->right.get(), cur_code, symbols_code);
	cur_code.pop_back();
}

std::unordered_map<unsigned char, std::deque<bool> > HuffmanTree::find_symbols_code() const {
	std::unordered_map<unsigned char, std::deque<bool> > symbols_code;
	std::deque<bool> code;
	go_and_find_code(root.get(), code, symbols_code);
	return symbols_code;
}

} //namespace Huffman

