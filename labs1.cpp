#include <iostream>
#include <chrono>
#include <random>

using namespace std;

void Lfind(int*, int, int);

void Bfind(int*, int, int);

int main()
{
    int N = 1000000, what;
    int *array = new int[N];
    unsigned seed = 1005;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, 1000);
    uniform_int_distribution<int> dstr_w(0, N - 1);
    array[0] = dstr(rng);
    for (int i = 1; i < N; ++i) {
        array[i] = dstr(rng) + array[i - 1];
    }
    what = array[dstr_w(rng)];
    auto begin = chrono::steady_clock::now();
    Lfind(array, N, what);
    auto middle = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);
    cout << "\n\n";
    cout << time_span.count() << endl;
    middle = chrono::steady_clock::now();
    Bfind(array, N, what);
    auto end = chrono::steady_clock::now();
    time_span = chrono::duration_cast<chrono::microseconds>(end - middle);
    cout << "\n\n";
    cout << time_span.count() << endl;
    delete[] array;
    return 0;
}

void Lfind(int array[], int N, int what) {
    int i = 0;
    for (; i < N; ++i) {
        if(array[i] == what) {
            break;
        }
    }
    cout << i << endl;
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
    cout << mid << endl;
}
