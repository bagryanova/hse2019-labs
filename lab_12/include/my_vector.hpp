#pragma once

#include <cstddef>
#include <iostream>

namespace my_vector {

template<typename T>
class my_vector final {
public:
    explicit my_vector() noexcept;
    explicit my_vector(size_t n);
    my_vector(const my_vector &other);
    my_vector(my_vector &&other) noexcept;
    my_vector &operator=(const my_vector &other);
    my_vector &operator=(my_vector &&other) noexcept;
    ~my_vector();

    void swap(my_vector &other) noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    void resize(size_t n);
    void reserve(size_t n);

    const T &operator[](size_t index) const;
    T &operator[](size_t index);

    void push_back(const T &t);
    void push_back(T &&t);
    void pop_back();
    void clear() noexcept;

private:
    size_t capacity_;
    size_t size_;
    T *array_;

    static my_vector allocate(size_t capacity_, size_t size_);
    void get_good_capacity();
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const my_vector<T> &vect);


} //namespace my_vector
