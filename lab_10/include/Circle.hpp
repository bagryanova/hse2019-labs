#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int cx, int cy, int radius, const char* cur_label);
    ~Circle() override;

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

protected: 
    int radius;
    char* label;
};