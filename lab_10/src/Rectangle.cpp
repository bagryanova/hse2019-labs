#include "Rectangle.hpp"
#include <iostream>
#include <cmath>

Rectangle::Rectangle(int id, int cx, int cy, int width, int height) :
    Figure(id, cx, cy), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, cx, cy, width, height);
}

bool Rectangle::is_inside(int x, int y) const {
    return abs(cx - x) <= width / 2 && abs(cy - y) <= height / 2;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}