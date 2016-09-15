#include <iostream>

template<uint32_t X, uint32_t N>
struct pow
{
	static constexpr uint32_t value = X * pow<X, N - 1>::value;
};

template<uint32_t X>
struct pow<X, 0>
{
	static constexpr uint32_t value = 1;
};

template<uint32_t X, uint32_t N>
struct series
{
	static_assert(N % 2 == 1, "N must be odd");

	static constexpr double value = static_cast<double>(1)/(N * pow<2*X+1, N>::value) + series<X, N - 2>::value;
};

template<uint32_t X>
struct series<X, static_cast<uint32_t>(-1)>
{
	static constexpr double value = static_cast<double>(0);
};


template<uint32_t N, uint32_t X>
struct ln;

template<uint32_t N>
struct ln<N, 1>
{
	static constexpr double value = 0;

	static void print()
	{
		std::cout << "ln(1)\t= 0" << std::endl;				
	}
};

template<uint32_t N, uint32_t X>
struct ln
{
	static_assert(X > 0, "X must be more then 0");

	static constexpr double value = ln<N, X-1>::value + 2 * series<X-1, N>::value;

	static void print()
	{
		ln<N, X-1>::print();
		std::cout << "ln(" << X << ")\t= " << value << std::endl;	
	}
};

static constexpr uint32_t N = 15;

int main()
{
	static_assert(pow<2, 0>::value == 1, "");
	static_assert(pow<2, 1>::value == 2, "");
	static_assert(pow<2, 2>::value == 4, "");
	static_assert(pow<2, 10>::value == 1024, "");
	static_assert(pow<5, 5>::value == 3125, "");

	static_assert(series<2, -1>::value == 0, "");
	static_assert(series<2, 1>::value == 0.2, "");

	static_assert(ln<N, 1>::value == 0, "");
	static_assert(ln<N, 2>::value > 0.693 && ln<N, 2>::value < 0.694, "");
	static_assert(ln<N, 3>::value > 1.098 && ln<N, 3>::value < 1.099, "");

	ln<N, 100>::print();

	return 0;
}
