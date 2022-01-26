

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <random>
#include <cassert>
#include <assert.h>
#include <algorithm>
#include <fstream>
#include "CODE/Quick_Sort.h"
#include "CODE/Merge_Sort.h"
#include "CODE/Heap_Sort.h"
#include "utility_lib.h"


using namespace std;
using std::chrono::nanoseconds;

constexpr int step = 100;
constexpr int maxlen = 10000;
constexpr int times = 100;



int main(int argc, char* args[])
{
    std::random_device rd;
    std:mt19937 gen(time(NULL));
    

    fstream quickoutfile("DATA/Quicksort/quick.txt", ios::out);
    fstream mergeoutfile("DATA/Merge_sort/merge.txt", ios::out);
    fstream heapoutfile("DATA/Heapsort/heap.txt", ios::out);
    


    for(int len = step; len < maxlen; len += step)
    {
        std::uniform_int_distribution<int> dist(-len, len);
        nanoseconds quick(0);	
        nanoseconds quick_sorted(0);
        nanoseconds merge(0);
        nanoseconds merge_sorted(0);
        nanoseconds heap(0);
        nanoseconds heap_sorted(0);
        
           
        for(int t=0; t<times; ++t)
        {
            int* arr = new int[len];
            for(int i=0; i <len; ++i)
                arr[i] = dist(gen);

            quick += timeit(arr, len, &QuickSort);
            quick_sorted += timeit_sorted(arr, len, &QuickSort);

            delete[] arr;
            arr = new int[len];
            for(int i=0; i <len; ++i)
                arr[i] = dist(gen);

            merge += timeit(arr, len, &Merge_Sort);
            merge_sorted += timeit_sorted(arr, len, &Merge_Sort);

            delete[] arr;
            arr = new int[len];
            for(int i=0; i <len; ++i)
                arr[i] = dist(gen);

            heap += timeit_Heap(arr, len, &Heapsort);
            heap_sorted += timeit_heap_sorted(arr, len, &Heapsort);
            delete[] arr;
        }
        cout << len << "  " << quick.count() / times  << "  " << merge.count() / times << "  " << heap.count()/times << endl;
        quickoutfile << len << " " << quick.count() / times  << " " << quick_sorted.count() / times << endl;
        mergeoutfile << len << " " << merge.count() / times  << "  " << merge_sorted.count() / times  << endl;
        heapoutfile << len  << " " << heap.count() / times   << "  " << heap_sorted.count() / times << endl;
        
    }
    quickoutfile.close();
    mergeoutfile.close();
    heapoutfile.close();
    return 0;
}

