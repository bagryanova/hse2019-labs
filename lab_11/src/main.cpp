#include "bin_manip.hpp"
#include "employees.hpp"
#include <string>
#include <fstream>
#include <assert.h>

void add(EmployeesArray& array) {
    int32_t type_int;
    assert(std::cin.good());
    std::cin >> type_int;
    assert(!std::cin.fail());
    Employees type = static_cast<Employees>(type_int);
    if (type == Employees::DEVELOPER) {
        Developer* cur = new Developer();
        assert(std::cin.good());
        std::cin >> *cur;
        assert(!std::cin.fail());
        array.add(cur);
    } else if (type == Employees::SALES_MANAGER) {
        SalesManager* cur = new SalesManager();
        assert(std::cin.good());
        std::cin >> *cur;
        assert(!std::cin.fail());
        array.add(cur);
    } else {
        assert(("Not valid type") && false);
    }
}

int main() {
    EmployeesArray array;
    while (true) {
        std::string type;
        assert(std::cin.good());
        std::cin >> type;
        assert(!std::cin.fail());
        if (type == "exit") {
            break;
        }
        if (type == "load") {
            std::string file_name;
            assert(std::cin.good());
            std::cin >> file_name;
            assert(!std::cin.fail());
            std::ifstream in(file_name, std::ios::binary | std::ios::in);
            assert(in.good());
            in >> array;
            assert(!in.fail());
        }
        if (type == "save") {
            std::string file_name;
            assert(std::cin.good());
            std::cin >> file_name;
            assert(!std::cin.fail());
            std::ofstream out(file_name, std::ios::binary | std::ios::out);
            assert(out.good());
            out << array;
            assert(!out.fail());
        }
        if (type == "add") {
            add(array);
        }
        if (type == "list") {
            assert(std::cout.good());
            std::cout << array << std::endl;
            assert(!std::cout.fail());
        }

    }
}