#include "Figure.hpp"

Figure::Figure(int id, int cx, int cy) :
    id(id), cx(cx), cy(cy) {}

void Figure::move(int new_x, int new_y) {
    cx = new_x;
    cy = new_y;
}

int Figure::get_id() {
    return id;
}

