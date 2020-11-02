#pragma once

#include <iostream>
#include <stdint.h>

class write_bool final {
public:
    explicit write_bool(bool x);
    friend std::ostream& operator << (std::ostream& out, write_bool data);
private:
    bool x;
};

class read_bool final {
public:
    explicit read_bool(bool& x);
    friend std::istream& operator >> (std::istream& in, read_bool data);
private:
    bool& x;
};

class write_le_int32 final {
public:
    explicit write_le_int32(int32_t x);
    friend std::ostream& operator << (std::ostream& out, write_le_int32 data);
private:
    int32_t x;
};

class read_le_int32 final {
public:
    explicit read_le_int32(int32_t& x);
    friend std::istream& operator >> (std::istream& in, read_le_int32 data);
private:
    int32_t& x;
};

class write_c_str final {
public:
    explicit write_c_str(char* x);
    friend std::ostream& operator << (std::ostream& out, write_c_str data);
private:
    char* x;
};

class read_c_str final {
public:
    explicit read_c_str(char* x, size_t sz);
    friend std::istream& operator >> (std::istream& in, read_c_str data);
private:
    char* x;
    size_t sz;
};
