
#include <iostream>
#include <map>

using namespace std;

/*1. Написать функцию, вводящую с клавиатуры набор целых чисел (в любом
порядке, конец ввода − Ctrl Z на пустой строчке) и выводящую числа из этого
набора в порядке возрастания и без повторений, с указанием того, сколько каждое
число раз встретилось в этом наборе.*/
void foo1 ()
{
  int x;
  map<int, int> M;
  while (cin>>x)
  {
    M[x] ++;
  }
  for (auto t : M)
  {
    cout << t.first << " -> " << t.second <<" "<<M.count(t.first)<< endl;
  }
}

/*2. Написать функцию, вводящую с клавиатуры отображение из целых чисел

в целые числа (вводятся число пар и пары из двух целых чисел, первое из кото-
рых− ключ, а второе − данные), и возвращающую это отображение как результат

типа map<int, int>.*/
void foo2 ()
{
  int x, y, n;
  int i =0;
  map<int, int> N;
  cin>>n;
  while (i<n)
  {
    cin>>x>>y
    N.insert(make_pair(x, y));
    i++;
  }
  for (auto t : M)
  {
    cout << t.first << " -> " << t.second << endl;
  }
}

/*3. Написать функцию, вводящую отображение (с помощью решения преды-
дущей задачи), и затем набор чисел, и выводящее для каждого введенного числа

его образ при введенном отображении, если введенное отображение определено
на этом числе, и само введенное число без изменений, если не определено.*/
void foo3 ()
{
  int x, y, n;
  int i =0;
  map<int, int> N;
  cin>>n;
  while (i<n)
  {
    cin>>x>>y
    N.insert(make_pair(x, y));
    i++;
  }
  int r;
  while(cin>>r)
  {
    for (auto t : M)
    {
      if (t.first == r)
      {
        cout << t.first << " -> " << t.second << endl;
      }
      else
      {
        cout<<r;
      }
    }
  }
}

/*4. Написать шаблонную функцию, вычисляющую сумму двух отображений
(можно предполагать, что их области определения совпадают, и типы значений
одинаковы).*/
template <class T1, class T2>
map <T1, T2> foo4 (map <T1, T2> m1, map <T1, T2> m2)
{
  for (auto [f1,s1] : m1)
  {
    for (auto [f2,s2] : m2)
    {
       if (f1==f2)
       {
         s1 +=s2;
       }
    }
  }
  return m1;
}

/*5. Написать шаблонную функцию, вычисляющую композицию двух отобра-
жений.*/
template <class T1, class T2, class T3>
map<T1, T3> foo5 (map<T1, T2> m1, map<T2, T3> m2)
{
  map<int, int> N;
  for (auto [f1,s1] : m1)
  {
    for (auto [f2,s2] : m2)
    {
       if (s1==f2)
       {
         N.insert(make_pair(f1, s2))
       }
    }
  }
  return N;
}

int main ()
{
  foo1();
  foo2();
  foo3();
  map <int, int> G = { {5, 45}, {3, 27}, {2, 18}, {4, 36} };
  map <int, int> D = { {5, 25}, {3, 15}, {2, 10}, {4, 20} };
  cout<<"multiplying by 14"<<foo4(G, D)<<endl;
  map <string, int> T = { {"Father", 45}, {"Mother", 42}, {"Sister", 20}, {"Brother", 15} };
  map <int, int> S = { {45, 1978}, {42, 1981}, {20, 2003}, {15, 2008} };
  cout<<"when were we born?"<< foo5(T, S)<< endl;
  return EXIT_SUCCESS;
}
