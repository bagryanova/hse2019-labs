#pragma once

#include <cstddef>
#include <stdexcept>
#include <cstdint>
#include <cassert>
#include <string>
#include <cstring>

namespace lab_13 {

template <typename T, std::size_t N>
class my_array final {
public:
    constexpr const T &at(std::size_t index) const;
    constexpr T &at(std::size_t index);
    constexpr const T &operator[](std::size_t index) const noexcept;
    constexpr T &operator[](std::size_t index) noexcept;

    constexpr bool empty() const noexcept;
    constexpr std::size_t size() const noexcept;

    constexpr void fill(const T &val);
private:
	T data[N];
};

template <std::size_t N>
class my_array<bool, N> final {
private:
	constexpr static std::size_t SIZE = N / 8 + (N % 8 > 0);
	std::uint8_t data[SIZE];

	struct proxy final {
		std::uint8_t &value;
		std::size_t index;

		constexpr proxy(std::uint8_t &value, std::size_t index) noexcept;
		constexpr proxy(const proxy &other) noexcept;
		constexpr proxy(proxy &&other) noexcept;
		constexpr proxy &operator=(const proxy &other) noexcept;
		constexpr proxy &operator=(proxy &&other) noexcept;

		constexpr operator bool() const noexcept;
		constexpr proxy &operator=(bool val) noexcept;
	};

public:
	constexpr my_array();
	constexpr bool at(std::size_t index) const;
    constexpr proxy at(std::size_t index);
    constexpr bool operator[](std::size_t index) const noexcept;
    constexpr proxy operator[](std::size_t index) noexcept;

    constexpr bool empty() const noexcept;
    constexpr std::size_t size() const noexcept;

    constexpr void fill(bool val);
};

template <typename T, std::size_t N>
constexpr const T &my_array<T, N>::at(std::size_t index) const {
	if (index >= N) {
		throw std::out_of_range("Out of range. Attempt to access at index " + std::to_string(index) + " when except an index less than " + std::to_string(N) + ".");
	}
	return data[index];
}

template <typename T, std::size_t N>
constexpr T &my_array<T, N>::at(std::size_t index) {
	if (index >= N) {
		throw std::out_of_range("Out of range. Attempt to access at index " + std::to_string(index) + " when except an index less than " + std::to_string(N) + ".");
	}
	return data[index];
}

template <typename T, std::size_t N>
constexpr const T &my_array<T, N>::operator[](std::size_t index) const noexcept {
	assert(index < N);
	return data[index];
}

template <typename T, std::size_t N>
constexpr T &my_array<T, N>::operator[](std::size_t index) noexcept {
	assert(index < N);
	return data[index];
}

template <typename T, std::size_t N>
constexpr bool my_array<T, N>::empty() const noexcept {
	return size() == 0;
}

template <typename T, std::size_t N>
constexpr std::size_t my_array<T, N>::size() const noexcept {
	return N;
}

template <typename T, std::size_t N>
constexpr void my_array<T, N>::fill(const T &val) {
	for (std::size_t i = 0; i < N; ++i) {
		data[i] = val;
	}
}


template <std::size_t N>
constexpr my_array<bool, N>::my_array() {
	fill(false);
}


template <std::size_t N>
constexpr bool my_array<bool, N>::at(std::size_t index) const {
	if (index >= N) {
		throw std::out_of_range("Out of range. Attempt to access at index " + std::to_string(index) + " when except an index less than " + std::to_string(N) + ".");
	}
	return operator[](index);
}

template <std::size_t N>
constexpr auto my_array<bool, N>::at(std::size_t index) -> proxy {
	if (index >= N) {
		throw std::out_of_range("Out of range. Attempt to access at index " + std::to_string(index) + " when except an index less than " + std::to_string(N) + ".");
	}
	return operator[](index);
}

template <std::size_t N>
constexpr bool my_array<bool, N>::operator[](std::size_t index) const noexcept {
	assert(index < N);
	return ((data[index / 8] >> (index % 8)) & 1u);
}

template <std::size_t N> 
constexpr auto my_array<bool, N>::operator[](std::size_t index) noexcept -> proxy {
	assert(index < N);
	return proxy(data[index / 8], index % 8);
}

template <std::size_t N>
constexpr bool my_array<bool, N>::empty() const noexcept {
	return size() == 0;
}

template <std::size_t N>
constexpr std::size_t my_array<bool, N>::size() const noexcept {
	return N;
}

template <std::size_t N>
constexpr void my_array<bool, N>::fill(bool val) {
	std::uint8_t value = 0;
	if (val) {
		value = (1u  << 8) - 1u;
	}
	std::memset(data, value, SIZE);
}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::proxy(std::uint8_t &value, std::size_t index) noexcept : value(value), index(index) {}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::proxy(const proxy &other) noexcept : value(other.value) {
	*this = other;
}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::proxy(proxy &&other) noexcept : value(other.value) {
	*this = other;
}

template <std::size_t N>
constexpr auto my_array<bool, N>::proxy::operator=(const proxy &other) noexcept -> proxy & {
	*this = static_cast<bool>(other);
	return *this;
}

template <std::size_t N>
constexpr auto my_array<bool, N>::proxy::operator=(proxy &&other) noexcept -> proxy & {
	return operator=(other);
}

template <std::size_t N>
constexpr auto my_array<bool, N>::proxy::operator=(bool val) noexcept -> proxy & {
	value &= ~(1u << index);
	if (val) {
		value |= (1u << index);
	}
	return *this;
}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::operator bool() const noexcept {
	return ((value >> index) & 1u); 
}

}  // namespace lab_13