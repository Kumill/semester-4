/*0. (1 балл) Вычисление числа π*/

#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include <iosream>

using namespace std;
using namespace std::chrono;

const int n = 10000000;

double f(double x)
{
    return 1 / (1 + x * x);
}

double integral(double (*f)(double), int A, int B)
{
    double sum = 0;
    for (int i = A; i <= B; i++)
        sum += f((2 * i - 1.0) / (2 * n));
    return sum / n;
}

int main()
{
    auto future = async(integral, f, 1, n);

    cout << future.get() * 4 << endl;
    return 0;
}
