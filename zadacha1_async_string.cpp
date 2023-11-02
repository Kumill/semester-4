/*1. (4 балла) Напишите функцию, принимающую строку из 10000 цифр, число
параллельных потоков и вычисляющую остаток от деления числа, образованного
такой последовательностью цифр, на 17*/

#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <random>

using namespace std;

 int count(const string& digits, int startIndex, int endIndex) 
{
      int result = 0;
      for (int j = startIndex; j < endIndex; ++j) 
      {
          result = (result * 10 + (digits[j] - '0')) % 17;
      }
      return result;
 } 
int calculateRemainder(const string& digits, int numThreads)
{
    int n = digits.size();
    int termsPerThread = n / numThreads; //количество частей, на которые будет разбита строка для каждого потока
    int remainingTerms = n % numThreads; //количество оставшихся частей, которые не укладываются в целое число потоков

    vector<future<int>> futures(numThreads);

    for (int i = 0; i < numThreads; i++) 
    {
        int startIndex = i * termsPerThread; //индекс начала части для потока
        int endIndex = startIndex + termsPerThread;

        if (i == numThreads - 1) 
        {
            endIndex += remainingTerms;
        }

        futures[i] = async(count, digits, startIndex, endIndex);
    }

    int remainder = 0;

    for (int i = 0; i < numThreads; ++i) 
    {
        remainder = (remainder * 10 + futures[i].get()) % 17;
    }

    return remainder;
}

int main()
{
    string digits;
    cout << "Enter a string of 10000 digits: ";
    cin >> digits;

    int numThreads;
    cout << "Enter the number of threads: ";
    cin >> numThreads;

    int remainder = calculateRemainder(digits, numThreads);

    cout << "Remainder: " << remainder << endl;

    return 0;
}
