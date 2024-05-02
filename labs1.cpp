#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

void Lfind(int*, int, int);

void Bfind(int*, int, int);

int main()
{
    ofstream out("data1.txt", std::ios::app);
    int N, what;
    int *array;
    unsigned seed = 1001;

    auto begin = chrono::steady_clock::now();
    auto middle = begin;
    auto end = middle;
    auto time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);

    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, 1000);
    for (N = 100; N < 1000001; N *= 10) {
        array = new int[N];
        uniform_int_distribution<int> dstr_w(0, N - 1);
        for (int i = 0; i < 5; ++i) {
            array[0] = dstr(rng);
            for (int i = 1; i < N; ++i) {
                array[i] = dstr(rng) + array[i - 1];
            }
            what = array[dstr_w(rng)];
            begin = chrono::steady_clock::now();
            Lfind(array, N, what);
            middle = chrono::steady_clock::now();
            time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);
            out << time_span.count();
            out << " ";
            middle = chrono::steady_clock::now();
            Bfind(array, N, what);
            end = chrono::steady_clock::now();
            time_span = chrono::duration_cast<chrono::microseconds>(end - middle);
            out << time_span.count();
            out << "    ";
        }
        out << endl;
        delete[] array;
    }
    out.close();
    return 0;
}

void Lfind(int array[], int N, int what) {
    int i = 0;
    for (; i < N; ++i) {
        if(array[i] == what) {
            break;
        }
    }
}

void Bfind(int array[], int N, int what) {
    int l = 0, r = N - 1, mid;
    mid = (l + r) / 2;
    if (array[r] == what) {
        l = r;
        mid = r;
    }
    while(array[mid] != what && r - l > 0) {
        if (array[mid] < what)
            l = mid;
        else
            r = mid;
        mid = (l + r) / 2;
    }
}
