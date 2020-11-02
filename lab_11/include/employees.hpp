#pragma once

#include <stdint.h>
#include <vector>
#include <iostream>

class Employee {
public:
	Employee();
	virtual ~Employee();
	virtual int32_t salary() const = 0;
	friend std::ostream& operator << (std::ostream& out, const Employee& e);
	friend std::istream& operator >> (std::istream& in, Employee& e);
	friend std::ofstream& operator << (std::ofstream& out, const Employee& e);
	friend std::ifstream& operator >> (std::ifstream& in, Employee& e);

protected:
	char* _name;
	int32_t _base_salary;
	virtual void stream_write(std::ostream& out) const = 0;
	virtual void stream_read(std::istream& in) = 0;
	virtual void fstream_write(std::ofstream& out) const = 0;
	virtual void fstream_read(std::ifstream& in) = 0;
};

class Developer final : public Employee {
public:
	int32_t salary() const override;
private:
	bool _has_bonus;
	void stream_write(std::ostream& out) const override;
	void stream_read(std::istream& in) override;
	void fstream_write(std::ofstream& out) const override;
	void fstream_read(std::ifstream& in) override;
}; 

class SalesManager final : public Employee {
public:
	int32_t salary() const override;
private:
	int32_t _sold_nm, _price;
	void stream_write(std::ostream& out) const override;
	void stream_read(std::istream& in) override;
	void fstream_write(std::ofstream& out) const override;
	void fstream_read(std::ifstream& in) override;
};

class EmployeesArray final {
public:
	~EmployeesArray();
	void add(Employee* e);
	int32_t total_salary() const;
	friend std::ostream& operator << (std::ostream& out, const EmployeesArray& array);
	friend std::ofstream& operator << (std::ofstream& out, const EmployeesArray& array);
	friend std::ifstream& operator >> (std::ifstream& in, EmployeesArray& array);
private:
	std::vector<Employee*> _employees;
};

enum class Employees : int32_t {
	DEVELOPER = 1, 
	SALES_MANAGER = 2
};