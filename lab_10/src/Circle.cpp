#include "Circle.hpp"
#include <iostream>
#include <cstring>

Circle::Circle(int id, int cx, int cy, int radius, const char* cur_label) :
    Figure(id, cx, cy), radius(radius) {
    label = new char[strlen(cur_label) + 1];
    strcpy(label, cur_label);
}

Circle::~Circle() {
    delete [] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, cx, cy, radius, label);
}

bool Circle::is_inside(int x, int y) const {
    return (cx - x) * (cx - x) + (cy - y) * (cy - y) <= radius * radius;
}

void Circle::zoom(int factor) {
    radius *= factor;
}