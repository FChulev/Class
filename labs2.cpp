#include <iostream>
#include <chrono>
#include <random>

using namespace std;

void Lfind(int*, int, int);

void FilterSwap(int*, int, int);

void FilterShift(int*, int, int);

void FilterCount(int*, int);

void Swap(int*, int*);

int main()
{
    int N = 100000, spec, i, a;
    int what[20];
    int *array = new int[N];
    int *array_sw = new int[N];
    int *array_sh = new int[N];
    int *array_cu = new int[N];
    unsigned seed = 1002;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, 10000);
    uniform_int_distribution<int> dstr_w(0, N - 1);
    spec = dstr(rng);
    for (int i = 0; i < N; ++i) {
        a = dstr_w(rng);
        if (a%2 == 0)
            array[i] = dstr(rng);
        else
            array[i] = spec;
        array_sw[i] = array[i];
        array_sh[i] = array[i];
        array_cu[i] = array[i];
    }
    for (int i = 0; i < 15; ++i) {
        a = dstr_w(rng);
        if (a%2 == 0)
            what[i] = array[dstr_w(rng)];
        else
            what[i] = spec;
    }
    for (int i = 15; i < 20; ++i) {
        what[i] = dstr(rng);
    }
    FilterSwap(array_sw, N, spec);
    FilterShift(array_sh, N, spec);
    FilterCount(array_cu, N);
    auto begin = chrono::steady_clock::now();
    auto middle = begin;
    auto middle_2 = middle;
    auto middle_3 = middle_2;
    auto end = middle_3;
    auto time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);

    for (i = 0; i < 20; ++i) {
        begin = chrono::steady_clock::now();
        Lfind(array, N, what[i]);
        middle = chrono::steady_clock::now();
        time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);
        cout << "  ";
        cout << time_span.count();
        middle = chrono::steady_clock::now();
        Lfind(array_sw, N, what[i]);
        middle_2 = chrono::steady_clock::now();
        time_span = chrono::duration_cast<chrono::microseconds>(middle_2 - middle);
        cout << "  ";
        cout << time_span.count();
        middle_2 = chrono::steady_clock::now();
        Lfind(array_sh, N, what[i]);
        middle_3 = chrono::steady_clock::now();
        time_span = chrono::duration_cast<chrono::microseconds>(middle_3 - middle_2);
        cout << "  ";
        cout << time_span.count();
        middle_3 = chrono::steady_clock::now();
        Lfind(array_cu, N, what[i]);
        end = chrono::steady_clock::now();
        time_span = chrono::duration_cast<chrono::microseconds>(end - middle_3);
        cout << "  ";
        cout << time_span.count() << " ["  << (what[i] == spec) << "]\n";
    }
    delete[] array;
    return 0;
}

void Swap(int *a, int *b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

void Lfind(int array[], int N, int what) {
    int i = 0;
    for (; i < N; ++i) {
        if(array[i] == what) {
            break;
        }
    }
}

void FilterSwap(int array_sw[], int N, int spec) {
    int ctr = 0, i;
    for (i = 0; i < N; ++i) {
        if (array_sw[i] == spec)
            Swap(array_sw + i, array_sw + ctr++);
    }
}

void FilterShift(int array_sh[], int N, int spec) {
    int i;
    for (i = 1; i < N; ++i) {
        if (array_sh[i] == spec)
            Swap(array_sh + i, array_sh + i - 1);
    }
}

void FilterCount(int array_cu[], int N) {
    int ctr[10000];
    int i;
    for (i = 0; i < 10000; ++i) {
        ctr[i] = 0;
    }
    ctr[array_cu[0]]++;
    for (i = 1; i < N; ++i) {
        ctr[array_cu[i]]++;
        if (ctr[array_cu[i]] > ctr[array_cu[i - 1]])
            Swap(array_cu + i, array_cu + i - 1);
    }
}
