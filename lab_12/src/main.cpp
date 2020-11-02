#include <iostream>
#include <cstring>

#include "my_vector.hpp"
#include "test.hpp"

namespace product {

class Product final {
public:
    explicit Product(const char *name, int quantity, double price);
    Product(const Product &other);
    Product(Product &&other);
    ~Product();
    Product &operator=(const Product &other);
    Product &operator=(Product &&other);
    bool operator!=(const Product &other);

    friend std::ostream &operator << (std::ostream &out, const Product &p);


private:
    char *name_;  // Указатель владеет C-style строкой, на которую указывает.
    int quantity_;
    double price_;
};

Product::Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price) {
	name_ = new char[strlen(name) + 1];
	strcpy(name_, name);
}

Product::Product(const Product &other) : quantity_(other.quantity_), price_(other.price_){
	name_ = new char[strlen(other.name_) + 1];
	strcpy(name_, other.name_);
}

Product::Product(Product &&other) {
	name_ = nullptr;
	*this = std::move(other);
}

Product::~Product() {
	delete [] name_;
}

Product &Product::operator=(const Product &other) {
	Product cur(other);
	*this = std::move(cur);
	return *this;
}

Product &Product::operator=(Product &&other) {
	std::swap(name_, other.name_);
	std::swap(quantity_, other.quantity_);
	std::swap(price_, other.price_);
	return *this;
}

bool Product::operator!=(const Product &other) {
	return !(strcmp(name_, other.name_) == 0 && quantity_ == other.quantity_ && price_ == other.price_);
}

std::ostream &operator << (std::ostream &out, const Product &p) {
	out << p.name_ << " " << p.quantity_ << " " << p.price_;
	return out;
}

}  // namespace product



int main() {
    my_vector::test::test_my_vector<int>(5, 10);
    my_vector::test::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    my_vector::test::test_my_vector_default_constructible<int>(5, 10);

    my_vector::test::print_result();
    return 0;
}

#include "my_vector_impl.hpp"