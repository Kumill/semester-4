#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;


void divide(double** matrix, int row, double coefficient, int columns) /*1. Написать функцию divide, принимающую в качестве параметров двумер-
ный массив (матрицу), номер строчки и вещественное число (коэффициент).Функция должна разделить все элементы соответствующей строчки на соответствующий коэффициент.*/
{
  for (int i = 0; i < columns; i++)
  {
    matrix[row][i] /= coefficient;
  }
}

void subtract(double** matrix, int row1, int row2, double coefficient) /*2. Написать функцию subtract, принимающую в качестве параметров двумерный массив, два целых числа (номера строк) и вещественное число (коэффици-
ент), и вычитающую поэлементно в массиве-параметре строку с первым номером, умноженную на коэффициент, из строки со вторым номером.*/
{
  for (int i = 0; i < columns; i++)
  {
    matrix[row2][i] -= coefficient * matrix[row1][i];
  }
}

void transform(double** matrix, int rows, int columns) /*3. Написать функцию transform, приводящую матрицу из вещественных чисел к единичному виду при помощи элементарных преобразований над строками
(алгоритм описан в абзаце перед задачами; также нужно использовать функции из задач 1 и 2).*/
{
  for (int i = 0; i < rows; i++)
  {
    divide(matrix, i, matrix[i][i]);
    for (int j = 0; j < rows; j++)
    {
      if (j != i)
      {
        subtract(matrix, i, j, matrix[j][i], columns);
      }
    }
  }
}

void slau(double** matrix, int rows, int columns) /*4. Воспользовавшись результатами предыдущих задач, написать функцию, решающую систему линейных уравнений с заданной расширенной матрицей системы методом Гаусса-Жордана.*/
{
  transform(matrix, rows, columns - 1);
  
  cout << "Решение системы линейных уравнений:" << endl;
  for (int i = 0; i < rows; i++)
  {
    cout << "x" << i + 1 << " = " << matrix[i][columns - 1] << endl;
  }
}

void slaupar(double** matrix, int rows, int columns) /*5. Распараллелить полученную программу для решения системы линейных уравнений при помощи OpenMP, используя директиву parallel for.*/
{
  transform(matrix, rows, columns - 1);
  #pragma omp parallel for
  for (int i = 0; i < rows; i++)
  {
   cout << "x" << i + 1 << " = " << matrix[i][columns - 1] << endl;
  }
}

int main()
{
  const int n = 3;
  const int m = n + 1;
  
  // Создаем и заполняем матрицу случайными значениями
  double** matrix = new double*[n];
  for (int i = 0; i < n; i++)
  {
    matrix[i] = new double[m];
    for (int j = 0; j < m; j++)
    {
      matrix[i][j] = rand() % 10 + 1;
    }
  }
  
  // Выводим исходную матрицу
  cout << "Исходная матрица:" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout<<"Без паралелелелизма:"<<endl;
  // Выполняем функцию slau и замеряем время выполнения
  double t = omp_get_wtime();
  slau(matrix, n, m);
  cout << "Время выполнения функции slau: " << omp_get_wtime()-t << " секунд" << endl;
  cout<<"При параллелелелизме:"<<endl;
  // Выполняем функцию slaupar и замеряем время выполнения
  t = omp_get_wtime();
  slaupar(matrix, n, m);
  cout << "Время выполнения функции slaupar: " << omp_get_wtime()-t << " секунд" << endl;
    
  return 0;
}
