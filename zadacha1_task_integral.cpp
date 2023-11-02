
#include <iostream>
#include <functional>
#include <cmath>
#include <omp.h>

using namespace std;

double f(double x) 
{
    return 1 / (1 + x * x);
}

double integr(double a, double b, function <double(double)> f) 
{
    double h = (b - a) / 10; // Шаг разбиения
    double sum = 0.0;
    
    // Вычисляем интеграл по формуле трапеций
    for (int i = 0; i < 10; i++) 
{
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        sum+= (f(x1) + f(x2)) * h / 2;
    }
    
    return sum;
}

double integral(double a, double b, function<double(double)> f) 
{
    double integral1 = integr(a, b, f); // Интеграл на интересующем нас отрезке
    double integral2 = integr(a, (a + b) / 2, f) + integr((a + b) / 2, b, f); // Интегралы на половинках отрезка
    
    // Проверяем разность между интегралом на интересующем нас отрезке и суммой интегралов на половинках
    if (abs(integral1 - integral2) <= 1e-10) 
    {
        return integral1; // Возвращаем интеграл на интересующем нас отрезке
    } 
    else 
    {
        double integralLeft, integralRight;
        #pragma omp parallel
        {
          #pragma omp single
          {
            #pragma omp task 
            integralLeft = integral(a, (a + b) / 2, f);
            #pragma omp task 
            integralRight = integral((a + b) / 2, b, f);
          }
        }
        return integralLeft + integralRight; // Возвращаем сумму интегралов на половинках
    }
}

int main() 
{
    double a, b;
    cout << "Введите начало и конец отрезка: "<< endl;
    cin >> a >> b;
    
    double result = integral(a, b, f);
    cout << "Интеграл функции 1/(1+x*x) на отрезке [" << a << ", " << b << "] равен " << result << endl;
    
    return 0;
}
