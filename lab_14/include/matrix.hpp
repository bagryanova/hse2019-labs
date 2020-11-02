#pragma once

#include <array>
#include <vector>
#include <iostream>

class Matrix {
public:
	Matrix() = default;
	Matrix(const size_t row, const size_t col);
	int get_element(const int row, const int col) const;
	void load(const std::string& filename);
	void print() const;

	Matrix& operator+=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
private:
	size_t sz_row, sz_col;
	std::vector<std::vector<int> > data;
};

class MatrixException final : public std::logic_error {
public:
	MatrixException(const char* message);
};