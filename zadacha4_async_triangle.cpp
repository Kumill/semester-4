/*4. (5 баллов) Напишите программу, вводящую с клавиатуры координаты 50 точек на плоскости, число параллельных потоков и вычисляющую сумму всех площадей треугольников с вершинами в этих точках.*/
#include <iostream>
#include <vector>
#include <cmath>
#include <future>

struct Point 
{
    double x;
    double y;
};

double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3) //Вычисление площади 1 треугольника по формуле герона
{
    return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2);
}

double calculateTotalArea(const vector<Point>& points, int numThreads) 
{
    int numPoints = points.size();
    int numTriangles = numPoints / 3;
    double totalArea = 0;

    vector<future<double>> futures(numTriangles);

    for (int i = 0; i < numTriangles; i++) 
    {
        futures[i] = async(calculateTriangleArea, points[i * 3], points[i * 3 + 1], points[i * 3 + 2]);
    }

    for (int i = 0; i < numTriangles; i++) 
    {
        totalArea += futures[i].get();
    }

    return totalArea;
}

int main() {
    int numPoints = 50;
    std::vector<Point> points(numPoints);

    std::cout << "Введите координаты 50 точек на плоскости:" << std::endl;
    for (int i = 0; i < numPoints; ++i) {
        std::cout << "Точка " << i + 1 << ":" << std::endl;
        std::cout << "x = ";
        std::cin >> points[i].x;
        std::cout << "y = ";
        std::cin >> points[i].y;
    }

    int numThreads;
    std::cout << "Введите количество параллельных потоков: ";
    std::cin >> numThreads;

    double totalArea = calculateTotalArea(points, numThreads);

    std::cout << "Сумма площадей всех треугольников: " << totalArea << std::endl;

    return 0;
}
```

В этой программе мы создаем структуру `Point`, которая представляет собой точку на плоскости с координатами `x` и `y`. Затем у нас есть функция `calculateTriangleArea`, которая вычисляет площадь треугольника по трем его вершинам с помощью формулы Герона.

Функция `calculateTotalArea` принимает вектор точек и количество параллельных потоков в качестве параметров. Она разбивает вектор точек на тройки и для каждой тройки точек запускает асинхронную задачу для вычисления площади треугольника. Затем она ожидает завершения всех задач и суммирует полученные площади.

В функции `main` мы сначала создаем вектор точек и заполняем его с помощью ввода с клавиатуры. Затем мы запрашиваем количество параллельных потоков. После этого вызываем функцию `calculateTotalArea` и выводим результат на экран.
