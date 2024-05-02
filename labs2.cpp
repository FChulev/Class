#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

void FindSum(int*, int, int);

void QFind(int*, int, int);

int main()
{
    ofstream out("C:/Projects/data2.txt", std::ios::app);
    int N, what, ind_1, ind_2;
    int *array;
    unsigned seed = 1001;
    default_random_engine rng(seed);
    uniform_int_distribution<int> dstr(0, 1000);

    auto begin = chrono::steady_clock::now();
    auto middle = begin;
    auto end = middle;
    auto time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);
    for (N = 100; N < 100001; N *= 10) {
        array = new int[N];
        uniform_int_distribution<int> dstr_w(0, N - 1);
        for (int i = 0; i < 5; ++i){
            array[0] = dstr(rng);
            for (int i = 1; i < N; ++i) {
                array[i] = dstr(rng) + array[i - 1];
            }
            ind_1 = dstr_w(rng);
            what = array[dstr_w(rng)];
            ind_2 = dstr_w(rng);
            if (ind_1 == ind_2 && ind_2 != N - 1)
                ++ind_2;
            else
                --ind_1;
            what = array[ind_1] + array[ind_2];
            begin = chrono::steady_clock::now();
            FindSum(array, N, what);
            middle = chrono::steady_clock::now();
            time_span = chrono::duration_cast<chrono::microseconds>(middle - begin);
            out << time_span.count();
            out << "  ";
            middle = chrono::steady_clock::now();
            QFind(array, N, what);
            end = chrono::steady_clock::now();
            time_span = chrono::duration_cast<chrono::microseconds>(end - middle);
            out << time_span.count() << "    ";
        }
        out << endl;
        delete[] array;
    }
    out.close();
    return 0;
}

void FindSum(int array[], int N, int what) {
    int i, j, flag = 1;
    for (i = 0; i < N; ++i) {
        for (j = i + 1; j < N; ++j) {
            if(array[i] + array[j] == what) {
                flag = 0;
                break;
            }
        }
        if (!flag)
            break;
    }
}

void QFind(int array[], int N, int what) {
    int l = 0, r = N - 1;
    while(array[l] + array[r] != what) {
        if(array[l] + array[r] > what)
            --r;
        else
            ++l;
    }
}
