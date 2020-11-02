#include "Scheme.hpp"
#include <assert.h>
#include <algorithm>

Scheme::Scheme(int capacity):
    capacity(capacity), sz(0) {
    figures_ = new Figure*[capacity]();
}

Scheme::~Scheme() {
    for (int i = 0; i < sz; ++i) {
        delete figures_[i];
    }
    delete [] figures_;   
}

void Scheme::push_back_figure(Figure* fg) {
    assert(sz < capacity);
    figures_[sz] = fg;
    ++sz;
}

void Scheme::remove_figure(int id) {
    assert(sz > 0);
    for (int i = 0; i < sz - 1; ++i) {
        if (figures_[i]->get_id() == id) {
            std::swap(figures_[i], figures_[i + 1]);
        }
    }
    assert(figures_[sz - 1]->get_id() == id);
    delete figures_[sz - 1];
    figures_[sz - 1] = nullptr;
    --sz;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < sz; ++i) {
        figures_[i]->print();
    }
}

Figure* Scheme::get_from_id(int id) {
    for (int i = 0; i < sz; ++i) {
        if (figures_[i]->get_id() == id) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::zoom_figure(int id, int factor) {
    Figure* fg = get_from_id(id);
    assert(fg != nullptr);
    fg->zoom(factor);
}

void Scheme::move(int id, int new_x, int new_y) {
    Figure* fg = get_from_id(id);
    assert(fg != nullptr);
    fg->move(new_x, new_y);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < sz; ++i) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

