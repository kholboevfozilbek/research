


#ifndef UTILITY_LIB_H_KNOWN
#define UTILITY_LIB_H_KNOWN

#include <iostream>
#include <chrono>
#include <assert.h>
#include <algorithm>

using namespace std;
using std::chrono::nanoseconds;

nanoseconds timeit(int* arr, int len, void function(int* , int const , int const ))
{
    auto begin = std::chrono::steady_clock::now();
    function(arr, 0, len-1);
    auto end = std::chrono::steady_clock::now();

    assert(is_sorted(arr, arr + len));
    nanoseconds total(end - begin);
    return total;
}

nanoseconds timeit_sorted(int* arr, int len, void function(int* , int const , int const ))
{
    std::sort(arr, arr + len);
    assert(is_sorted(arr, arr+len));
    auto begin = std::chrono::steady_clock::now();
    function(arr, 0, len-1);
    auto end = std::chrono::steady_clock::now();

    nanoseconds total(end - begin);
    return total;
}

nanoseconds timeit_Heap(int* arr, int len, void function(int* , int))
{
    auto begin = std::chrono::steady_clock::now();
    function(arr, len);
    auto end = std::chrono::steady_clock::now();

    assert(is_sorted(arr, arr + len));
    nanoseconds total(end - begin);
    return total;
}

nanoseconds timeit_heap_sorted(int* arr, int len, void function(int* , int ))
{
    std::sort(arr, arr + len);
    assert(is_sorted(arr, arr+len));
    auto begin = std::chrono::steady_clock::now();
    function(arr, len);
    auto end = std::chrono::steady_clock::now();

    nanoseconds total(end - begin);
    return total;
}

void display(int* arr, int len)
{
    for(int i=0; i< len; ++i)
        cout << arr[i] << " ";
    
}


#endif