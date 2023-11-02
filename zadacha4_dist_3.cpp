/*(3 балла) Напишите последовательную функцию, принимающую массив коор-
динат точек в трехмерном пространстве и вычисляющую диаметр указанного

множества точек, т. е. наибольшее расстояние между двумя точками из ука-
занного набора. Распараллельте эту функцию на а) 2 б) 4 в) 3 потока (да, пра-
вильное распараллеливание на 3 потока сложнее, чем на 2 и даже на 4).*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <omp.h>
#include <ctime>

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
	double x1 = 0, x2 = 0, x3 = 0;
	int s1 = 0, s2 = 0, s3 = 0; //количество иттераций в каждой секции

#pragma omp parallel sections
	{
#pragma omp section
		{
			Point p1, p2;
			x1 = dist(points[0], points[1]);
			for (int i = 0; i < points.size(); i++)
			{
				p1 = points[i];
				for (int j = i + 1; j < points.size(); j += 3)
				{
					s1++;
					p2 = points[j];
					double d = dist(p1, p2);
					if (d > x1)
					{
						x1 = d;
					}

				}
			}
		
		}
#pragma omp section
		{
			Point p1, p2;
			x2 = dist(points[0], points[1]);
			for (int i = 0; i < points.size(); ++i)
			{
				p1 = points[i];
				for (int j = i + 2; j < points.size(); j += 3)
				{
					s2++;
					p2 = points[j];
					double d = dist(p1, p2);
					if (d > x2)
					{
						x2 = d;
					}

				}
			}
			
		}
#pragma omp section
		{
			Point p1, p2;
			x3 = dist(points[0], points[1]);
			for (int i = 0; i < points.size(); ++i)
			{
				p1 = points[i];
				for (int j = i + 3; j < points.size(); j += 3)
				{
					s3++;
					p2 = points[j];
					double d = dist(p1, p2);
					if (d > x3)
					{
						x3 = d;
					}

				}
			}
			
		}
	}
	cout << "s1 = " << s1 << " s2 = " << s2 << " s3 = " << s3 << endl;
	double m[4]{ x1, x2, x3 };
	x = m[0];
	for (int i = 0; i < 3; ++i)
	{
		if (m[i] < x)
		{
			x = m[i];
		}
	}

	return x;
}

int main()
{
	double t = omp_get_wtime();
	int n = 0;
	double dia = 0, x = 0, y = 0, z = 0;
	vector <Point> points;
	srand(time(NULL));

	for (int i = 0; i < N; i++)
	{
		x = (double)rand();
		y = (double)rand();
		z = (double)rand();
		Point p(x, y, z);
		points.push_back(p);
	}

	dia = d(points);
	cout << dia << endl;
	
	cout << "Time: " << omp_get_wtime() - t << endl;
	return EXIT_SUCCESS;
}
