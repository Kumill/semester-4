#include <chrono>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;
using namespace chrono_literals;

mutex m;
int object; // ╨║╨╛╨┤ ╤В╨╛╨▓╨░╤А╨░
bool flag = false; // true -- ╤Б╨║╨╗╨░╨┤ ╨╖╨░╨┐╨╛╨╗╨╜╨╡╨╜, false -- ╤Б╨║╨╗╨░╨┤ ╨┐╤Г╤Б╤В
bool work1 = true, work2 = true;
vector<int> v1, v2;

void factory() {
    mt19937 mt;
    uniform_int_distribution<> dist(0, 100);
    while (work2) {
        if (flag)
            this_thread::sleep_for(chrono::milliseconds(dist(mt)));
        else {
            object = mt();
            v1.push_back(object);
            flag = true;
        }
    }
}

void consumer() {
    mt19937 mt;
    uniform_int_distribution<> dist(0, 100);
    while (work2) {
        if (!flag)
            this_thread::sleep_for(chrono::milliseconds(dist(mt)));
        else {
            v2.push_back(object);
            flag = false;
        }
    }
}

void check_all() {
    thread f1(factory);
    thread f2(factory);
    thread c1(consumer);
    thread c2(consumer);
    thread c3(consumer);
    this_thread::sleep_for(1s);
    work1 = false;
    work2 = false;
    f1.join();
    f2.join();
    c1.join();
    c2.join();
    c3.join();
    cout << "first vector\n"; 
    for (auto x : v1)
        cout << x << " ";
    cout << "\nsecond vector\n";
    for (auto x : v2)
        cout << x << " ";
}

void factory_m() {
    mt19937 mt;
    uniform_int_distribution<> dist(0, 100);
    while (work2) { 
        m.lock();
        if (flag) {
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(dist(mt)));
        } else {
            object = mt();
            v1.push_back(object);
            flag = true;
            m.unlock();
        }
    }
}

void consumer_m() {
    mt19937 mt;
    uniform_int_distribution<> dist(0, 100);
    while (work2) {
        m.lock();
        if (!flag) {
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(dist(mt)));
        } else {
            v2.push_back(object);
            flag = false;
            m.unlock();
        }
    }
}

void check_all_m() {
    thread f1(factory_m);
    thread f2(factory_m);
    thread c1(consumer_m);
    thread c2(consumer_m);
    thread c3(consumer_m);
    this_thread::sleep_for(1s);
    work1 = false;
    work2 = false;
    f1.join();
    f2.join();
    c1.join();
    c2.join();
    c3.join();
    cout << "first vector\n"; 
    for (auto x : v1)
        cout << x << " ";
    cout << "\nsecond vector\n";
    for (auto x : v2)
        cout << x << " ";
}
int main() {
    //check_all();
    check_all_m();
}
