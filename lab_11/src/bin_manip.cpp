#include "bin_manip.hpp"
#include <string.h>
#include <assert.h>

write_bool::write_bool(bool x) : x(x) {}

std::ostream& operator << (std::ostream& out, write_bool data) {
	char c = static_cast<char>(data.x);
	assert(out.good());
	out.put(c);
	assert(!out.fail());
	return out;
}

read_bool::read_bool(bool& x) : x(x) {}

std::istream& operator >> (std::istream& in, read_bool data) {
	char c;
	assert(in.good());
	in.get(c);
	assert(!in.fail());
	data.x = static_cast<bool>(c);
	return in;
}

write_le_int32::write_le_int32(int32_t x) : x(x) {}

std::ostream& operator << (std::ostream& out, write_le_int32 data) {
	for (int i = 0; i < 4; ++i) {
		char c = static_cast<char>(data.x % (1 << 8));
		assert(out.good());
		out.put(c);
		assert(!out.fail());
		data.x /= (1 << 8);
	}
	return out;
}

read_le_int32::read_le_int32(int32_t& x) : x(x) {}

std::istream& operator >> (std::istream& in, read_le_int32 data) {
	data.x = 0;
	for (int i = 0; i < 4; ++i) {
		char c;
		assert(in.good());
		in.get(c);
		data.x += static_cast<uint32_t>(static_cast<unsigned char>(c)) << (8 * i);
	}
	assert(!in.fail());
	return in;
}

write_c_str::write_c_str(char* x): x(x) {}

std::ostream& operator << (std::ostream& out, write_c_str data) {
	assert(out.good());
	out.write(data.x, strlen(data.x) + 1);
	assert(!out.fail());
	return out;
}

read_c_str::read_c_str(char* x, size_t sz): x(x), sz(sz) {}

std::istream& operator >> (std::istream& in, read_c_str data) {
	assert(in.good());
	in.getline(data.x, data.sz, '\0');
	assert(!in.fail());
	return in;
}