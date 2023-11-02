/*4. (5 баллов) Напишите программу, вводящую с клавиатуры координаты 50 точек на плоскости, число параллельных потоков и вычисляющую сумму всех площадей треугольников с вершинами в этих точках.*/
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <cmath>
#include <future>

using namespace std;

const double eps = 10e-5;

struct Point
{
    double x;
    double y;
};

double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3)
{
    return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2);
}

double calculateTotalArea(const vector<Point>& points, int numThreads)
{
    int numPoints = points.size();
    int numTriangles = numPoints / 3;
    double totalArea = 0;

    vector<future<double>> futures(numTriangles);
    // количество занятых потоков
    int tmp = 0;
    for (int i = 0; i < numPoints; i++)
    {
        for (int j = 0; j < numPoints; j++)
        {
            for (int z = 0; z < numPoints; z++)
            {
                if (tmp != numThreads) {
                    futures[tmp] = async(calculateTriangleArea, points[i], points[j], points[z]);
                    ++tmp;
                } else {
                    for (int t = 0; t < numThreads; t++)
                        totalArea += futures[t].get();
                    tmp = 0;
                }
            }
        }
    }
    return totalArea;
}

vector<Point> gen_data(int n) //функция, которая генерит точки
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(-10000, 10000);
    vector<Point> vec;
    for (int i = 0; i < n; ++i)
        vec.push_back({dist(gen), dist(gen)});
    return vec;
}

int main() 
{
    int numPoints = 50;
    vector<Point> points = gen_data(numPoints);

    int numThreads;
    cout << "Введите количество параллельных потоков: ";
    cin >> numThreads;

    double totalArea = calculateTotalArea(points, numThreads);

    cout << "Сумма площадей всех треугольников: " << totalArea << endl;

    return 0;
}
