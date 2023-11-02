/*1. (1 балл) Вычисление таблицы синусов. Вычислите параллельно и последова-
тельно таблицу синусов на отрезке [0,π/2] с шагом pi/2n , где n – параметр задачи.*/
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <omp.h>

using namespace std;

const int N = 100000000;
const double pi = 3.1415926;
double a[N] = { 0 };

int main()
{
	double t = omp_get_wtime();

	for (int i = 0; i < N / 2; i++)
	{
		a[i] = sin(i * pi / (2 * N));
	}

	for (int i = N / 2; i < N; i++)
	{
		a[i] = sin(i * pi / (2 * N));
	}
	cout << "Time: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime(); //время перед началом работы 2х потоков

#pragma omp parallel sections
		{
#pragma omp section
			{
				for (int i = 0; i < N / 2; i++)
				{
					a[i] = sin(i * pi / (2 * N));
				}
			}
#pragma omp section
			{
				for (int i = N / 2; i < N; i++)
				{
					a[i] = sin(i * pi / (2 * N));
				}
			}
		}

	cout << "Time for 2: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime(); //время перед началом работы 4х потоков

	#pragma omp parallel sections
		{
	#pragma omp section
			{
				for (int i = 0; i < (N / 4); i++)
	      {
					a[i] = sin(i * pi / (2 * N));
				}
			}
	#pragma omp section
			{
				for (int i = N / 4; i < (N/2); i++)
	      {
					a[i] = sin(i * pi / (2 * N));
				}
			}

	#pragma omp section
			{
				for (int i = N/2; i < (3 * N/4); i++)
	      {
					a[i] = sin(i * pi / (2 * N));
				}
			}
	#pragma omp section
			{
				for (int i = (3 * N/4); i <= N ; i++)
	      {
					a[i] = sin(i * pi / (2 * N));
				}
			}
		}
		cout << "Time for 4: " << omp_get_wtime() - t << endl;


	for (int i = 0; i < N; i++) //проверка самой таблицы
	{
		cout << i << a[i] << endl;
	}

	return EXIT_SUCCESS;
}
