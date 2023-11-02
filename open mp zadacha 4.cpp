/*(3 балла) Напишите последовательную функцию, принимающую массив коор-
динат точек в трехмерном пространстве и вычисляющую диаметр указанного

множества точек, т. е. наибольшее расстояние между двумя точками из ука-
занного набора. Распараллельте эту функцию на а) 2 б) 4 в) 3 потока (да, пра-
вильное распараллеливание на 3 потока сложнее, чем на 2 и даже на 4).

Для задания координат точки можно завести структуру Point, а набор точек хра-
нить в переменной типа vector <Point>. Напишите также функцию dist, вычисляющую

расстояние между двумя точками.*/
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <omp.h>

using namespace std;

const int N = 10000;

struct Point
{
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
};

double dist(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
}

double d(vector<Point>& points)
{
	double x = 0;
	double s1 = 0;
	Point p1, p2;
	x = dist(points[0], points[1]);

	for (int i = 0; i < points.size(); ++i)
	{
		p1 = points[i];
		for (int j = i + 1; j < points.size(); ++j)
		{
			s1++;
			p2 = points[j];
			double d = dist(p1, p2);
			if (d > x)
			{
				x = d;
			}
		}
	}
	//cout << s1 << endl;

	return x;
}

int main()
{
	double t = omp_get_wtime();
	int n = 0;
	double dia = 0, x = 0, y = 0, z = 0;
	vector <Point> points;
	/*
	cout << "Enter the number of points: ";
	cin >> n;

	for (int i = 0; i < n; ++i)
	{
		cout << "Enter the x: ";
		cin >> x;
		cout << "Enter the y: ";
		cin >> y;
		cout << "Enter the z: ";
		cin >> z;
		Point p(x, y, z);
		points.push_back(p);
	}
	*/
	for (int i = 0; i < N; i++)
	{
		x = (double)rand();
		y = (double)rand();
		z = (double)rand();
		//cout << x << " " << y << " " << z << endl;
		Point p(x, y, z);
		points.push_back(p);
	}
	dia = d(points);
	cout << dia << endl;
	/*
	for (int i = 0; i < n; ++i)
	{
		cout << points[i].x << " " << points[i].y << " " << points[i].z << endl;
	}
	*/
	cout << "Time: " << omp_get_wtime() - t << endl;
	return EXIT_SUCCESS;
}
