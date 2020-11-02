#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <assert.h>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;

template<typename T>
class drop_enumerator;

template<typename T>
class take_enumerator;

template<typename T, typename U, typename F>
class select_enumerator;

template<typename T, typename F>
class until_enumerator;

template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
    virtual const T &operator*() = 0;
    virtual void operator++() = 0;
    virtual operator bool() const noexcept = 0;

    auto drop(std::size_t count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(std::size_t count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, std::move(func));
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, std::move(func));
    }

    auto until_eq(const T &elem) {
        return until([&elem] (const T &cur_elem) {
            return elem == cur_elem;
        });
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, std::move(func));
    }

    auto where_neq(const T &elem) {
        return where([&elem] (const T &cur_elem) {
            return elem != cur_elem;
        });
    }

    std::vector<T> to_vector() {
        std::vector<T> result;
        while (static_cast<bool>(*this)) {
            result.push_back(*(*this));
            ++(*this);
        }
        return result;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (static_cast<bool>(*this)) {
            *it = *(*this);
            ++it;
            ++(*this);
        }
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

    const T &operator*() override {
        assert(static_cast<bool>(*this));
        return *begin_;
    }

    void operator++() override {
        assert(static_cast<bool>(*this));
        ++begin_;
    }

    operator bool() const noexcept override {
        return begin_ != end_;
    }

private:
    Iter begin_, end_;
};

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, std::size_t count) : parent_(parent) {
        while (static_cast<bool>(parent_) && count > 0) {
            ++parent_;
            --count;
        }
    }

    const T &operator*() override {
        assert(static_cast<bool>(*this));
        return *parent_;
    }

    void operator++() override {
        assert(static_cast<bool>(*this));
        ++parent_;
    }

    operator bool() const noexcept override {
        return static_cast<bool>(parent_);
    }



private:
    enumerator<T> &parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, std::size_t count) : count_(count), parent_(parent) {}

    const T &operator*() override {
        assert(static_cast<bool>(*this));
        return *parent_;
    }

    void operator++() override {
        assert(static_cast<bool>(*this));
        --count_;
        if (count_ > 0) {
            ++parent_;
        }
    }

    operator bool() const noexcept override {
        return (count_ > 0 && static_cast<bool>(parent_));
    }

private:
    std::size_t count_;
    enumerator<T> &parent_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {
        if (static_cast<bool>(*this)) {
            result = func_(*parent_);
        }
    }

    const T &operator*() override {
        assert(static_cast<bool>(*this));
        return result;
    }

    void operator++() override {
        assert(static_cast<bool>(*this));
        ++parent_;
        if (static_cast<bool>(*this)) {
            result = func_(*parent_);
        }
    }

    operator bool() const noexcept override {
        return static_cast<bool>(parent_);
    }

private:
    enumerator<U> &parent_;
    F func_;
    T result;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent),  predicate_(std::move(predicate)) {
        if (static_cast<bool>(parent_) && predicate_(*parent_)) {
            terminated = true;
        }
    }

    const T &operator*() override {
        assert(static_cast<bool>(*this));
        return *parent_;
    }

    void operator++() override {
        assert(static_cast<bool>(*this));
        ++parent_;
        if (static_cast<bool>(parent_) && predicate_(*parent_)) {
            terminated = true;
        }
    }

    operator bool() const noexcept override {
        return (static_cast<bool>(parent_) && !terminated);
    }

private:
    enumerator<T> &parent_;
    F predicate_;
    bool terminated = false;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent),  predicate_(std::move(predicate)) {
        while (static_cast<bool>(parent_) && !predicate_(*parent_)) {
            ++parent_;
        }
    }

    const T &operator*() override {
        assert(static_cast<bool>(*this));
        return *parent_;
    }

    void operator++() override {
        assert(static_cast<bool>(*this));
        ++parent_;
        while (static_cast<bool>(parent_) && !predicate_(*parent_)) {
            ++parent_;
        }
    }

    operator bool() const noexcept override {
        return static_cast<bool>(parent_);
    }

private:
    enumerator<T> &parent_;
    F predicate_;
};

} // namespace impl

template<typename T>
auto from(T begin, T end) {
    return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

} // namespace linq

#endif