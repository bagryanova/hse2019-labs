#include "matrix.hpp"

#include <iostream>
#include <fstream>

Matrix::Matrix(const size_t row, const size_t col) : sz_row(row), sz_col(col) {
	data.resize(sz_row, std::vector<int> (sz_col));
}

int Matrix::get_element(const int row, const int col) const {
	if (row < 0 || col < 0 || row >= static_cast<int>(sz_row) || col >= static_cast<int>(sz_col)) {
		throw MatrixException("ACCESS: bad index.");
	}
	return data[row][col];
}

void Matrix::load(const std::string& filename) {
	std::fstream in(filename);
	if (!in.is_open()) {
		throw MatrixException("LOAD: unable to open file.");
	}
	size_t row, col;
	if (!(in >> row >> col)) {
		throw MatrixException("LOAD: invalid file format.");
	}
	Matrix result(row, col);
	for (size_t i = 0; i < result.sz_row; ++i) {
		for (size_t j = 0; j < result.sz_col; ++j) {
			if (!(in >> result.data[i][j])) {
				throw MatrixException("LOAD: invalid file format.");
			}
		}
	}
	*this = result;
}

void Matrix::print() const {
	for (size_t i = 0; i < sz_row; ++i) {
		for (size_t j = 0; j < sz_col; ++j) {
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix& Matrix::operator+=(const Matrix& other) {
	if (sz_row != other.sz_row || sz_col != other.sz_col) {
		throw MatrixException("ADD: dimensions do not match.");
	}
	for (size_t i = 0; i < sz_row; ++i) {
		for (size_t j = 0; j < sz_col; ++j) {
			data[i][j] += other.data[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
	if (sz_col != other.sz_row) {
		throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
	}
	Matrix result(sz_row, other.sz_col);
	for (size_t i = 0; i < sz_row; ++i) {
		for (size_t j = 0; j < other.sz_col; ++j) {
			for (size_t k = 0; k < sz_col; ++k) {
				result.data[i][j] += data[i][k] * other.data[k][j];
			}
		}
	}
	return *this = result;
}

MatrixException::MatrixException(const char* message) : std::logic_error(message) {}
