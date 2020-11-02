#include "matrix.hpp"

#include <string>

static constexpr size_t REGSZ = 10;

int main() {
	std::vector<Matrix> regs(REGSZ);
	while (true) {
		try {
			std::string type;
			std::cin >> type;
			if (type == "load") {
				char c;
				size_t reg;
				std::string filename;
				std::cin >> c >> reg >> filename;
				regs[reg].load(filename);
			}
			if (type == "print") {
				char c;
				size_t reg;
				std::cin >> c >> reg;
				regs[reg].print();
			}
			if (type == "add") {
				char c;
				size_t reg1, reg2;
				std::cin >> c >> reg1 >> c >> reg2;
				regs[reg1] += regs[reg2];
			}
			if (type == "mul") {
				char c;
				size_t reg1, reg2;
				std::cin >> c >> reg1 >> c >> reg2;
				regs[reg1] *= regs[reg2];
			}
			if (type == "elem") {
				char c;
				size_t reg1;
				int row, col;
				std::cin >> c >> reg1 >> row >> col;
				std::cout << regs[reg1].get_element(row, col) << std::endl;
			}
			if (type == "exit") {
				break;
			}
		} catch (const MatrixException& e) {
			std::cout << e.what() << std::endl;
		} catch (const std::bad_alloc& e) {
			std::cout << "Unable to allocate memory." << std::endl;
		}
	}
}

