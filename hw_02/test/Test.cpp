#include "Test.hpp"

#include <iostream>
#include <cassert>

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
	++totalNum;
	if (!expr) {
		std::cout << "Test failed in file " << filename << " in function " << func << " in line " << lineNum << "\n";
		++failedNum;
	}
}

bool Test::show_final_result() {
	std::cout << totalNum << " tests were done, " << failedNum << " failed\n";
	return failedNum == 0;
}