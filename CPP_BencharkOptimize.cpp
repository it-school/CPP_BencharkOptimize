#include <iostream>
#include <chrono>

const long long OPERATIONS = 1000000000; // 1 000 000 000

/// <summary>
/// Comparing loops performance with diferent counter types, conditions and run format
/// </summary>
static void example1() {
	long long x = 0, y = 0;

	// ---------------------------------  1  ---------------------------------
	auto startTime = std::chrono::high_resolution_clock::now();
	for (long long i = 0; i < OPERATIONS; i++)
	{
		x++;
	}
	auto finishTime = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast <std::chrono::nanoseconds> (finishTime - startTime).count() / 1000000.0;

	std::cout << std::endl << "Calculation result: " << x << std::endl;
	std::cout << "Execution time: " << executionTime << " ms" << std::endl;

	// ---------------------------------  2  ---------------------------------
	startTime = std::chrono::high_resolution_clock::now();
	for (double i = OPERATIONS; i > 0; i--)
	{
		++y;
	}
	finishTime = std::chrono::high_resolution_clock::now();
	executionTime = std::chrono::duration_cast <std::chrono::nanoseconds> (finishTime - startTime).count() / 1000000.0;

	std::cout << std::endl << "Calculation result: " << y << std::endl;
	std::cout << "Execution time: " << executionTime << " ms" << std::endl;
}

/// <summary>
/// Let's solve the expression calculated in billion cycles loop and optimize it to improve the performance
/// y = 5*x^7 - 2.5*x^6 + 3*x^5 - 8.3*x^4 + 5*x^3 - 9*x^2 + 10*x-2;
/// </summary>
static void example2()
{
	double y, a, b;
	auto startTime = std::chrono::high_resolution_clock::now();
	for (char i = 0; i < 10; i++)
	{
		for (long long x = 0; x < OPERATIONS; x++)
		{
			// y = 5 * pow(x, 7) - 2.5 * pow(x, 6) + 3 * pow(x, 5) - 8.3 * pow(x, 4) + 5 * pow(x, 3) - 9 * pow(x, 2) + 10 * x - 2;  // 10470 ms
			// y = 5 * x*x*x*x*x*x*x - 2.5 * x*x*x*x*x*x + 3 * x*x*x*x*x - 8.3 * x*x*x*x + 5 * x*x*x - 9 * x*x + 10 * x - 2;  // 70 ms

// Optimization of calculations

// 1st way
//			a = x * x;
//			b = x * x * x;
//			y = 5 * b*b*x - 2.5 * b*b + 3 * b*a - 8.3 * b*x + 5 * b - 9 * a + 10 * x - 2;		// 36 ms
//			y = a * (a * (5 * b - 8.3) + 3 * b - 9) + b * (5 - 2.5 * b) + 10 * x - 2;			// 20 ms


// 2nd way
//			y = x * (5 * x * x * x * x * x * x - 2.5 * x * x * x * x * x + 3 * x * x * x * x - 8.3 * x * x * x + 5 * x * x - 9 * x + 10) - 2; //38 ms
//			y = x * (x * (5 * x * x * x * x * x - 2.5 * x * x * x * x + 3 * x * x * x - 8.3 * x * x + 5 * x - 9) + 10) - 2; //32 ms
//			y = x * (x * (x * (5 * x * x * x * x - 2.5 * x * x * x + 3 * x * x - 8.3 * x + 5) - 9) + 10) - 2;	// 28 ms
//			y = x * (x * (x * (x * (5 * x * x * x - 2.5 * x * x + 3 * x - 8.3) + 5) - 9) + 10) - 2;				// 23 ms
//			y = x * (x * (x * (x * (x * (5 * x * x - 2.5 * x + 3) - 8.3) + 5) - 9) + 10) - 2;					// 20 ms
			y = x * (x * (x * (x * (x * (x * (5 * x - 2.5) + 3) - 8.3) + 5) - 9) + 10) - 2;						// 18 ms
		}
	}
	auto finishTime = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast <std::chrono::nanoseconds> (finishTime - startTime).count() / 1000000.0;

	std::cout << std::endl << "Calculation result: " << y << std::endl;
	std::cout << "Execution time: " << executionTime << " ms" << std::endl;
}

int main()
{
	example1();
	// https://godbolt.org/z/813a9qWzz
	// https://quick-bench.com/q/D7Qx7zPaO-qS_dqv7uiZCuQsOmU
	// https://quick-bench.com/q/gOVXhfDs2bBwgTn6J41suDXO8pM
	example2();
}