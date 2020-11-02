#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <deque>

namespace Huffman {

struct HuffmanNode final {
	std::optional<unsigned char> symbol;
	std::size_t weight;
	std::unique_ptr<HuffmanNode> left, right;

	explicit HuffmanNode(unsigned char symbol_, std::size_t weight_) noexcept;
	explicit HuffmanNode(std::unique_ptr<HuffmanNode> left_, std::unique_ptr<HuffmanNode> right_) noexcept;
	explicit HuffmanNode(std::unique_ptr<HuffmanNode> left_) noexcept;
};

class HuffmanTree final {
public:
	explicit HuffmanTree(std::unordered_map<unsigned char, std::size_t> &symbols_frequency);
	std::unordered_map<unsigned char, std::deque<bool> > find_symbols_code() const;

private:
	std::unique_ptr<HuffmanNode> root;
	void go_and_find_code(HuffmanNode *node, std::deque<bool> &cur_code, std::unordered_map<unsigned char, std::deque<bool> > &symbols_code) const;
};

} //namespace Huffman