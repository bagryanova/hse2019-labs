#pragma once

#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int cx, int cy, int width, int height);
    ~Rectangle() override = default;

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

protected:
    int width;
    int height;
};