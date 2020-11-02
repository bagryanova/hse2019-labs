#pragma once 

#include "my_vector.hpp"

namespace my_vector {

namespace test {

int CNT_TESTS = 0;
int CNT_GOOD_TESTS = 0;

template <typename T>
void test_constructor() {
    ++CNT_TESTS;
    my_vector<T> vect;
    if (vect.size() != 0 || vect.capacity() != 0) {
        return;
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_constructor_with_size() {
    ++CNT_TESTS;
    size_t size = 10, capacity = 16;
    my_vector<T> vect(size);
    if (vect.size() != size || vect.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < 10; ++i) {
        if (vect[i] != T()) {
            return;
        }
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_copy_constructor(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> other;
    size_t size = 10, capacity = 16;
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(a);
    }
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(b);
    }
    my_vector<T> result(other);
    if (result.size() != size || result.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        if (result[i] != other[i]) {
            return;
        }
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_move_constructor(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> other;
    size_t size = 10, capacity = 16;
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(a);
    }
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(b);
    }
    my_vector<T> other_copy(other);
    my_vector<T> result(std::move(other));
    if (result.size() != size || result.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        if (result[i] != other_copy[i]) {
            return;
        }
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_operator_copy_assignment(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> other;
    size_t size = 10, capacity = 16;
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(a);
    }
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(b);
    }
    my_vector<T> result;
    result = other;
    if (result.size() != size || result.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        if (result[i] != other[i]) {
            return;
        }
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_operator_move_assignment(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> other;
    size_t size = 10, capacity = 16;
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(a);
    }
    for (size_t i = 0; i < 5; ++i) {
        other.push_back(b);
    }
    my_vector<T> other_copy(other);
    my_vector<T> result;
    result = std::move(other);
    if (result.size() != size || result.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        if (result[i] != other_copy[i]) {
            return;
        }
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_resize(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> vect;
    size_t size = 10, capacity = 16;
    for (size_t i = 0; i < 5; ++i) {
        vect.push_back(a);
    }
    for (size_t i = 0; i < 5; ++i) {
        vect.push_back(b);
    }
    my_vector<T> vect_copy(vect);
    vect.resize(12);
    if (vect.size() != 12 || vect.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        if (vect[i] != vect_copy[i]) {
            return;
        }
    }
    if (vect[10] != T() || vect[11] != T()) {
        return;
    }
    vect.resize(5);
    if (vect.size() != 5 || vect.capacity() != capacity) {
        return;
    }
    for (size_t i = 0; i < 5; ++i) {
        if (vect[i] != vect_copy[i]) {
            return;
        }
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_reserve(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> vect;
    vect.reserve(5);
    if (vect.size() != 0 || vect.capacity() != 8) {
        return;
    }
    vect.push_back(a);
    vect.push_back(b);
    if (vect.size() != 2 || vect.capacity() != 8 || vect[0] != a || vect[1] != b) {
        return;
    }
    vect.reserve(3);
    if (vect.size() != 2 || vect.capacity() != 8) {
        return;
    }
    vect.reserve(10);
    if (vect.size() != 2 || vect.capacity() != 16) {
        return;
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_get_set_operator(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> vect;
    vect.push_back(a);
    vect.push_back(b);
    if (vect[0] != a || vect[1] != b) {
        return;
    }
    vect[1] = a;
    if (vect[0] != a || vect[1] != a) {
        return;
    }
    try {
        vect[10] = a;
        return;
    } catch (...) {}
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_push_back(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> vect;
    vect.push_back(a);
    if (vect.size() != 1 || vect.capacity() != 1 || vect[0] != a) {
        return;
    }
    vect.push_back(b);
    if (vect.size() != 2 || vect.capacity() != 2 || vect[1] != b) {
        return;
    }
    T c = a;
    vect.push_back(std::move(c));
    if (vect.size() != 3 || vect.capacity() != 4 || vect[2] != a) {
        return;
    }
    ++CNT_GOOD_TESTS;
}  

template <typename T>
void test_pop_back(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> vect;
    for (size_t i = 0; i < 5; ++i) {
        vect.push_back(a);
    }
    vect[1] = b;
    vect[3] = b;
    vect.pop_back();
    if (vect.size() != 4 || vect.capacity() != 8 || vect[3] != b) {
        return;
    }
    vect.pop_back();
    if (vect.size() != 3 || vect.capacity() != 8 || vect[2] != a) {
        return;
    }

    vect.pop_back();
    if (vect.size() != 2 || vect.capacity() != 8 || vect[1] != b) {
        return;
    }
    vect.pop_back();
    if (vect.size() != 1 || vect.capacity() != 8 || vect[0] != a) {
        return;
    }
    vect.pop_back();
    if (vect.size() != 0 || vect.capacity() != 8) {
        return;
    }
    ++CNT_GOOD_TESTS;
}

template <typename T>
void test_clear(const T &a, const T &b) {
    ++CNT_TESTS;
    my_vector<T> vect;
    for (size_t i = 0; i < 5; ++i) {
        vect.push_back(a);
    }
    for (size_t i = 0; i < 5; ++i) {
        vect.push_back(b);
    }
    vect.clear();
    if (vect.size() != 0 || vect.capacity() != 0) {
        return;
    }
    ++CNT_GOOD_TESTS;
}


template <typename T>
void test_my_vector(const T &a, const T &b) {
    test_constructor<T>();
    test_copy_constructor<T>(a, b);
    test_move_constructor<T>(a, b);
    test_operator_copy_assignment<T>(a, b);
    test_operator_move_assignment<T>(a, b);
    test_reserve<T>(a, b);
    test_get_set_operator<T>(a, b);
    test_push_back<T>(a, b);
    test_pop_back<T>(a, b);
    test_clear<T>(a, b);
}

template <typename T>
void test_my_vector_default_constructible(const T &a, const T &b) {
    test_constructor_with_size<T>();
    test_resize<T>(a, b);
}

void print_result() {
    std::cout << CNT_TESTS << " were done, " << CNT_TESTS - CNT_GOOD_TESTS << " failed.\n";
}

} //namespace test
} //namespace my_vector

#include "my_vector_impl.hpp"
