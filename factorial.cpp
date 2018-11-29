#include <iostream>

typedef unsigned int uint_type;

template <uint_type n>
class factorial {
public:
	enum { value = n * factorial<n - 1>::value };
};

template<> class factorial<1> {
public:
	enum { value = 1 };
};

template <uint_type n, uint_type k>
class bin {
public:
	enum { value = bin<n-1, k-1>::value + bin<n-1, k>::value };
};

template<uint_type n>
struct bin<n, 0> {
	enum { value = 1 };
};

template<uint_type n>
struct bin <n, n> {
	enum { value = 1 };
};

int main() {
	std::cout << factorial<4>::value << std::endl << bin<4, 3>::value <<std::endl;
	return 0;
}
