#pragma once

#include "my_vector.hpp"
#include <memory>
#include <algorithm>
#include <exception>
#include <iostream>

namespace my_vector {

template <typename T>
my_vector<T>::my_vector() noexcept : capacity_(0), size_(0), array_(nullptr) {}

template <typename T>
my_vector<T>::my_vector(size_t n) : my_vector() {
	my_vector<T> result;
	for (size_t i = 0; i < n; ++i) {
		result.push_back(T());
	}
	*this = std::move(result);
}

template <typename T>
my_vector<T>::my_vector(const my_vector<T> &other) : my_vector() {
	my_vector<T> result;
	for (size_t i = 0; i < other.size_; ++i) {
		result.push_back(other.array_[i]);
	}
	*this = std::move(result);
}

template <typename T>
my_vector<T>::my_vector(my_vector<T> &&other) noexcept : capacity_(other.capacity_), size_(other.size_), array_(other.array_) {
	other.size_ = 0;
	other.capacity_ = 0;
	other.array_ = nullptr;
}

template <typename T>
my_vector<T>::~my_vector<T>() {
	clear();
}

template <typename T>
void my_vector<T>::swap(my_vector<T> &other) noexcept {
	std::swap(capacity_, other.capacity_);
	std::swap(size_, other.size_);
	std::swap(array_, other.array_);
}

template <typename T>
my_vector<T> &my_vector<T>::operator=(const my_vector<T> &other) {
	if (this == &other) {
		return *this;
	}
	my_vector<T> cur(other);
	*this = std::move(cur);
	return *this;

}

template <typename T>
my_vector<T> &my_vector<T>::operator=(my_vector &&other) noexcept {
	if (this == &other) {
		return *this;
	}
	swap(other);
	return *this;
}

template <typename T>
size_t my_vector<T>::size() const noexcept {
	return size_;
}

template <typename T>
size_t my_vector<T>::capacity() const noexcept {
	return capacity_;
}

template <typename T>
bool my_vector<T>::empty() const noexcept {
	return size_ == 0;
}

template <typename T>
void my_vector<T>::resize(size_t n) {
	if (n <= size_) {
		while (n < size_) {
			pop_back();
		}
	} else {
		my_vector<T> result;
		result.reserve(n);
		for (size_t i = 0; i < size_; ++i) {
			result.array_[i] = std::move(array_[i]);
		}
		result.size_ = size_;
		for (size_t i = size_; i < n; ++i) {
			result.push_back(T());
		}
		*this = result;
	}
}

template <typename T>
void my_vector<T>::reserve(size_t n) {
	if (n <= capacity_) {
		return;
	}
	my_vector<T> result = allocate(n, 0);
	for (size_t i = 0; i < size_; ++i) {
		result.push_back(std::move(array_[i]));
	}
	*this = std::move(result);
}

template <typename T>
const T &my_vector<T>::operator[](size_t index) const {
	if (index > size_) {
		throw std::range_error("Out of range.");
	}
	return array_[index];
}

template <typename T>
T &my_vector<T>::operator[](size_t index) {
	if (index > size_) {
		throw std::range_error("Out of range.");
	}
	return array_[index];
}

template <typename T>
void my_vector<T>::push_back(const T &t) {
	push_back(T(t));
}

template <typename T>
void my_vector<T>::push_back(T &&t) {
	if (size_ == capacity_) {
		reserve(capacity_ + 1);
	}
	new (&array_[size_++]) T(std::move(t));
}

template <typename T>
void my_vector<T>::pop_back() {
	if (empty()) {
		throw std::logic_error("Cannot pop because the vector is empty.");
	}
	array_[--size_].~T();
}

template <typename T>
void my_vector<T>::clear() noexcept {
	for (size_t i = 0; i < size_; ++i) {
		array_[i].~T();
	}
	delete [] reinterpret_cast<char *>(array_);
	capacity_ = 0;
	size_ = 0;
	array_ = nullptr;
}

template <typename T>
my_vector<T> my_vector<T>::allocate(size_t capacity_, size_t size_)  {
	my_vector<T> result;
	result.capacity_ = capacity_;
	result.get_good_capacity();
	result.size_ = size_;
	char *cur = new char[result.capacity_ * sizeof(T)];
	result.array_ = reinterpret_cast<T *>(cur);
	return result;
}

template <typename T>
void my_vector<T>::get_good_capacity() {
	if (capacity_ == 0) {
		return;
	}
	size_t pow_of_two = 1;
	while (capacity_ > pow_of_two) {
		pow_of_two <<= 1;
	}
	capacity_ = pow_of_two;
}

template <typename T>
std::ostream &operator << (std::ostream &out, const my_vector<T> &vect) {
    for (size_t i = 0; i < vect.size(); ++i) {
        out << vect[i] << " ";
    }
    return out;
}

} //namespace my_vector