#include <algorithm>
#include <cmath>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
using namespace std::chrono;

ifstream fin ("date.in");
ofstream fout ("date.out");

void generator_vector(long long v[], int nr, long long mx) {
    for (int i = 0; i < nr; i++)
        v[i] = rand() % mx;
}

bool TestSort(long long vector_initial[], long long vector_sortat[], int n) {
    sort(vector_initial, vector_initial + n);
    for (int i = 0; i < n; i++)
        if (vector_initial[i] != vector_sortat[i])
            return 0;
    return 1;
}

void BubbleSort(long long v[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (v[i] > v[j])
                swap(v[i], v[j]);
}

void CountingSort(long long v[], int n, long long mx) {
    int poz = 0;
    int count[mx + 1];
    for (int i = 0; i <= mx; i++)
        count[i] = 0;
    for (int i = 1; i <= n; i++)
        count[v[i]]++;
    for (int i = 0; i < +mx; i++)
        for (int j = 0; j < count[i]; j++)
            v[poz++] = i;

}

void RadixSort(long long v[], int n, long long m) {
    int i, b[100001], exp = 1;
    while (m / exp > 0) {
        int bucket[10] = {0};
        for (i = 0; i < n; i++)
            bucket[v[i] / exp % 10]++;
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (i = n - 1; i >= 0; i--)
            b[--bucket[v[i] / exp % 10]] = v[i];
        for (i = 0; i < n; i++)
            v[i] = b[i];
        exp *= 10;

    }
}

void Merge(long long v[], int p, int q, int r) {

    int n1, n2, i, j, k;
    n1 = q - p + 1;
    n2 = r - q;
    long long Stanga[n1], Dreapta[n2];
    for (i = 0; i < n1; i++)
        Stanga[i] = v[p + i];
    for (j = 0; j < n2; j++)
        Dreapta[j] = v[q + j + 1];
    i = 0, j = 0;
    for (k = p; i < n1 && j < n2; k++) {
        if (Stanga[i] < Dreapta[j]) {
            v[k] = Stanga[i++];
        } else {
            v[k] = Dreapta[j++];
        }
    }
    while (i < n1) {
        v[k++] = Stanga[i++];
    }
    while (j < n2) {
        v[k++] = Dreapta[j++];
    }
}

void MergeSort(long long v[], long long p, int r) {
    int q;
    if (p < r) {
        q = (p + r) / 2;
        MergeSort(v, p, q);
        MergeSort(v, q + 1, r);
        Merge(v, p, q, r);
    }
}

void quickSort(long long v[], int st, int dr) {
    int temp, mn, mx;
    long long mijl = v[st + (dr - st) / 2];
    mn = st;
    mx = dr;
    do {
        while (v[mn] < mijl)
            mn++;
        while (v[mx] > mijl)
            mx--;
        if (mn <= mx) {
            temp = v[mn];
            v[mn++] = v[mx];
            v[mx--] = temp;
        }
    } while (mn <= mx);

    if (st < mx)
        quickSort(v, st, mx);
    if (dr > mn)
        quickSort(v, mn, dr);
}

int main() {
    long long vector_initial[100001], vector_functie[100001], nr_maxim;
    int nr_elem, nr_teste;
    fout << "Introduceti numarul de teste:" << '\n';
    fin >> nr_teste;
    srand(time(NULL));
    for (int j = 1; j <= nr_teste; j++) {
        fout << "Testul " << j << '\n';
        nr_elem = rand() % 100000;
        fout << "Numarul de elemente:" << nr_elem << '\n';
        nr_maxim = rand();
        fout << "Valoarea maxima a elementelor :" << nr_maxim << '\n';

        generator_vector(vector_initial, nr_elem, nr_maxim);

        for (int i = 0; i < nr_elem; i++)
            vector_functie[i] = vector_initial[i];

        if (nr_elem <= 10000) {
            auto start = high_resolution_clock::now();
            BubbleSort(vector_functie, nr_elem);
            auto stop = high_resolution_clock::now();
            auto durata = duration_cast<nanoseconds>(stop - start);
            if (TestSort(vector_initial, vector_functie, nr_elem) == 1)
                fout << "Sortarea Bubble a durat: " << double(durata.count()) / 1000000000 << " secunde.\n";
            else fout << "Sortare Bubble a esuat \n";
        } else fout << "Numarul de elemente este prea mare pentru o sortare Bubble \n";


        for (int i = 0; i < nr_elem; i++)
            vector_functie[i] = vector_initial[i];

        if (nr_maxim <= 100000) {
            auto start1 = high_resolution_clock::now();
            CountingSort(vector_functie, nr_elem, nr_maxim);
            auto stop1 = high_resolution_clock::now();
            auto durata1 = duration_cast<nanoseconds>(stop1 - start1);
            if (TestSort(vector_initial, vector_functie, nr_elem) == 1)
                fout << "Sortarea Counting a durat: " << double(durata1.count()) / 1000000000 << " secunde.\n";
            else fout << "Sortarea Counting a esuat \n";
        } else fout << "Numarul de elemente este prea mare pentru o sortare Counting \n";


        for (int i = 0; i < nr_elem; i++)
            vector_functie[i] = vector_initial[i];

        auto start2 = high_resolution_clock::now();
        RadixSort(vector_functie, nr_elem, nr_maxim);
        auto stop2 = high_resolution_clock::now();
        auto durata2 = duration_cast<nanoseconds>(stop2 - start2);
        if (TestSort(vector_initial, vector_functie, nr_elem) == 1)
            fout << "Sortarea Radix a durat: " << double(durata2.count()) / 1000000000 << " secunde.\n";
        else fout << "Sortarea Radix a esuat \n";

        for (int i = 0; i < nr_elem; i++)
            vector_functie[i] = vector_initial[i];

        auto start3 = high_resolution_clock::now();
        MergeSort(vector_functie, 0, nr_elem - 1);
        auto stop3 = high_resolution_clock::now();
        auto durata3 = duration_cast<nanoseconds>(stop3 - start3);
        if (TestSort(vector_initial, vector_functie, nr_elem) == 1)
            fout << "Sortarea Merge a durat: " << double(durata3.count()) / 1000000000 << " secunde.\n";
        else fout << "Sortarea Merge a esuat \n";


        for (int i = 0; i < nr_elem; i++)
            vector_functie[i] = vector_initial[i];

        auto start4 = high_resolution_clock::now();
        quickSort(vector_functie, 0, nr_elem - 1);
        auto stop4 = high_resolution_clock::now();
        auto durata4 = duration_cast<nanoseconds>(stop4 - start4);
        if (TestSort(vector_initial, vector_functie, nr_elem) == 1)
            fout << "Sortarea Quick a durat: " << double(durata4.count()) / 1000000000 << " secunde.\n";
        else fout << "Sortarea Quick a esuat \n";
        fout <<"\n\n";
    }
    return 0;
}