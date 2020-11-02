#include "employees.hpp"
#include "bin_manip.hpp"
#include <fstream>
#include <assert.h>
#include <string.h>

const int NAMESZ = 101;

Employee::Employee() : _base_salary(0) {
	_name = new char[NAMESZ];
}

Employee::~Employee() {
	delete [] _name;
}

std::ostream& operator << (std::ostream& out, const Employee& e) {
	e.stream_write(out);
	return out;
}

std::istream& operator >> (std::istream& in, Employee& e) {
	e.stream_read(in);
	return in;
}

std::ofstream& operator << (std::ofstream& out, const Employee& e) {
	e.fstream_write(out);
	return out;
}

std::ifstream& operator >> (std::ifstream& in, Employee& e) {
	e.fstream_read(in);
	return in;
}

int32_t Developer::salary() const {
	int32_t salary = _base_salary;
	if (_has_bonus) salary += 1000;
	assert(salary >= 0);
	return salary;
}

void Developer::stream_write(std::ostream& out) const {
	assert(out.good());
	out << "Developer\nName: ";
	assert(out.good());
	out << _name;
	assert(out.good());
	out << "\nBase Salary: ";
	assert(out.good());
	out << _base_salary;
	assert(out.good());
	out << "\nHas bonus: ";
	assert(out.good());
	out << (_has_bonus ? '+' : '-');
	assert(out.good());
	out << "\n";
	assert(!out.fail());
}

void Developer::stream_read(std::istream& in) {
	assert(in.good());
	in >> _name;
	assert(in.good());
	in >> _base_salary;
	assert(_base_salary >= 0);
	assert(in.good());
	in >> _has_bonus;
	assert(!in.fail());
}

void Developer::fstream_write(std::ofstream& out) const {
	out << write_le_int32(static_cast<int32_t>(Employees::DEVELOPER))
	    << write_c_str(_name) << write_le_int32(_base_salary) << write_bool(_has_bonus);
}

void Developer::fstream_read(std::ifstream& in) {
	in >> read_c_str(_name, NAMESZ) >> read_le_int32(_base_salary) >> read_bool(_has_bonus);
	assert(_base_salary >= 0);
}

int32_t SalesManager::salary() const {
	int result = _base_salary + _sold_nm * _price * 0.01;
	assert(result >= 0);
	return result; 
}

void SalesManager::stream_write(std::ostream& out) const {
	assert(out.good());
	out << "Sales Manager\nName: ";
	assert(out.good());
	out << _name;
	assert(out.good());
	out << "\nBase Salary: ";
	assert(out.good());
	out << _base_salary;
	assert(out.good());
	out << "\nSold items: ";
	assert(out.good());
	out << _sold_nm;
	assert(out.good());
	out << "\nItem price: ";
	assert(out.good());
	out << _price;
	assert(out.good());
	out << "\n";
	assert(!out.fail());
}

void SalesManager::stream_read(std::istream& in) {
	assert(in.good());
	in >> _name;
	assert(in.good());
	in >> _base_salary;
	assert(_base_salary >= 0);
	assert(in.good());
	in >> _sold_nm;
	assert(_sold_nm >= 0);
	assert(in.good());
	in >> _price;
	assert(_price >= 0);
	assert(!in.fail());
}

void SalesManager::fstream_write(std::ofstream& out) const {
	out << write_le_int32(static_cast<int32_t>(Employees::SALES_MANAGER))
	    << write_c_str(_name) << write_le_int32(_base_salary) << write_le_int32(_sold_nm) << write_le_int32(_price);
}

void SalesManager::fstream_read(std::ifstream& in) {
	in >> read_c_str(_name, NAMESZ) >> read_le_int32(_base_salary) >> read_le_int32(_sold_nm) >> read_le_int32(_price);
	assert(_base_salary >= 0);
	assert(_sold_nm >= 0);
	assert(_price >= 0);
}

EmployeesArray::~EmployeesArray() {
	for (size_t i = 0; i < _employees.size(); ++i) {
		delete _employees[i];
	}
}

int32_t EmployeesArray::total_salary() const {
	int32_t result = 0;
	for (size_t i = 0; i < _employees.size(); ++i) {
		result += _employees[i]->salary();
	}
	return result;
}

void EmployeesArray::add(Employee* e) {
	_employees.push_back(e);
}

std::ostream& operator << (std::ostream& out, const EmployeesArray& array) {
	for (size_t i = 0; i < array._employees.size(); ++i) {
		assert(out.good());
		out << i + 1;
		assert(out.good());
		out << ". ";
		assert(out.good());
		out << *(array._employees[i]);
	}
	assert(out.good());
	out << "== Total salary: ";
	assert(out.good());
	out << array.total_salary();
	assert(out.good());
	out << "\n";
	assert(!out.fail());
	return out;
}

std::ofstream& operator << (std::ofstream& out, const EmployeesArray& array) {
	size_t sz = array._employees.size();
	out << write_le_int32(static_cast<int32_t>(sz));
	for (size_t i = 0; i < sz; ++i) {
		assert(out.good());
		out << *(array._employees[i]);
	}
	assert(!out.fail());
	return out;
}

std::ifstream& operator >> (std::ifstream& in, EmployeesArray& array) {
	int sz;
	in >> read_le_int32(sz);

	for (size_t i = 0; i < static_cast<size_t>(sz); ++i) {
		int32_t type_int;
		in >> read_le_int32(type_int);
		Employees type = static_cast<Employees>(type_int);
		if (type == Employees::DEVELOPER) {
			Developer* cur = new Developer();
			assert(in.good());
			in >> *cur;
			assert(!in.fail());
			array.add(cur);
		} else if (type == Employees::SALES_MANAGER) {
			SalesManager* cur = new SalesManager();
			assert(in.good());
			in >> *cur;
			assert(!in.fail());
			array.add(cur);
		} else {
			assert(("Not valid type") && false);
		}
	}
	return in;
}