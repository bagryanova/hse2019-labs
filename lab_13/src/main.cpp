#include "my_array.h"
#include <cstddef>
#include <iostream>

namespace lab_13 {

namespace test {

int CHECK_CNT = 0;
int GOOD_CHECK_CNT = 0;

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());

    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
}

void check(bool expr) {
    ++CHECK_CNT;
    if (expr) {
        ++GOOD_CHECK_CNT;
    }
}

template<typename T, std::size_t N>
void test_with_data(const T& first, const T& second, std::size_t cnt) {
    try {
        my_array<T, N> a;

        check(a.size() == N);

        size_t ind = 0;
        bool type = false;
        while (ind < N) {
            for (size_t i = ind; i < ind + cnt && i < N; ++i) {
                if (type) {
                    a[i] = second;
                    check(a[i] == second);
                } else {
                    a[i] = first;
                    check(a[i] == first);
                }
            }
            type ^= true;
            ind += cnt;
        }

        my_array<T, N> ca = a;
        check(ca.size() == a.size());

        for (size_t i = 0; i < ca.size(); ++i) {
            check(a[i] == ca[i]);
        }

        check(!a.empty());
        check(!ca.empty());

        check(a.at(0) == first);
        check(ca.at(0) == first);
        check(a.at(cnt) == second);
        check(ca.at(cnt) == second);

        check(a[0] == first);
        check(ca[0] == first);
        check(a[cnt] == second);
        check(ca[cnt] == second);

        a.fill(second);
        for (size_t i = 0; i < N; ++i) {
            check(a[i] == second);
        }

        a[0] = ca[0];
        check(a[0] == ca[0]);
        check(a.at(0) == ca[0]);

        a[cnt] = first;
        check(a[cnt] == first);
        check(a.at(cnt) == first);

        a[cnt] = ca[cnt];
        check(a[cnt] == second);
        check(a.at(cnt) == second);

        try {
            ++CHECK_CNT;
            a.at(N) = first;

        } catch (const std::out_of_range &e) {
            ++GOOD_CHECK_CNT;
        }

        try {
            ++CHECK_CNT;
            a[0] = a.at(N);
        } catch (const std::out_of_range &e) {
            ++GOOD_CHECK_CNT;
        }
    } catch (const std::out_of_range &e) {
        ++CHECK_CNT;
    }
}

template<typename T, std::size_t N>
void test_with_random_elements() {
    try {
        my_array<T, N> a;
        check(a.size() == N);

        const my_array<T, N> &ca = a;
        check(ca.size() == a.size());
        for (size_t i = 0; i < ca.size(); ++i) {
            check(a[i] == ca[i]);
        }

        check(!a.empty());
        check(!ca.empty());

        try {
            ++CHECK_CNT;
            a.at(N);
        } catch (const std::out_of_range &e) {
            ++GOOD_CHECK_CNT;
        }
    } catch (const std::out_of_range &e) {
        ++CHECK_CNT;
    }

}

class NonCopyable {
public:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

} //namespace test

} //namespace lab_13

int main() {
    lab_13::test::test_core<int, 10>();
    lab_13::test::test_core<bool, 10>();
    lab_13::test::test_core<lab_13::test::NonCopyable, 10>();

    lab_13::test::test_assign<int, 10>();
    lab_13::test::test_assign<bool, 10>();

    lab_13::test::test_with_data<int, 12>(1, 2, 5);
    lab_13::test::test_with_data<bool, 6>(true, false, 5);
    lab_13::test::test_with_data<int, 15>(3, 2, 5);
    lab_13::test::test_with_data<bool, 15>(true, false, 5);

    lab_13::test::test_with_random_elements<int, 12>();

    std::cout << lab_13::test::CHECK_CNT << " checks done, " << lab_13::test::CHECK_CNT - lab_13::test::GOOD_CHECK_CNT << " failed." << std::endl;
    return 0;   
}