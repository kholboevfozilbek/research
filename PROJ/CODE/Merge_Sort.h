
#pragma once
#ifndef MERGE_SORT_H_KNOWN
#define MERGE_SORT_H_KNOWN

#include <iostream>
#include <stdexcept>
#include <random>

using namespace std;

void Merge(int* arr, int const left, int const mid, int const right);

void Merge_Sort(int* arr, int const begin, int const end)
{
    if(begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    Merge_Sort(arr, begin, mid); //left part from 0 -> mid inclusive
    Merge_Sort(arr, mid+1, end); //right part from mid+1 to end
    Merge(arr, begin, mid, end);
}

void Merge(int* arr, int const left, int const mid, int const right)
{
    //let the hacking begiin ... 
    int number_subArrayOne = mid - left + 1;
    int number_subArraytwo = right - mid;

    int* leftSubArrayOne = new int[number_subArrayOne];
    int* rightSubArrayTwo = new int[number_subArraytwo];

    for(size_t i=0; i<number_subArrayOne; ++i)
        leftSubArrayOne[i] = arr[left+i];
    for(size_t j=0; j<number_subArraytwo; ++j)
        rightSubArrayTwo[j] = arr[mid+1 + j];

    int index_left_array = 0;
    int index_right_array = 0;
    int index_merged_array = left;
    


    while (index_left_array < number_subArrayOne && index_right_array < number_subArraytwo)
    {
        if(leftSubArrayOne[index_left_array] <= rightSubArrayTwo[index_right_array])
        {
            arr[index_merged_array] = leftSubArrayOne[index_left_array];
            ++index_left_array;
        }
        else
        {
            arr[index_merged_array] = rightSubArrayTwo[index_right_array];
            ++index_right_array;
        }
        ++index_merged_array;
    }

    //for possible leftovers

    while (index_left_array < number_subArrayOne)
    {
        arr[index_merged_array] = leftSubArrayOne[index_left_array];
        ++index_left_array;
        ++index_merged_array;
    }

    while (index_right_array < number_subArraytwo)
    {
        arr[index_merged_array] = rightSubArrayTwo[index_right_array];
        ++index_right_array;
        ++index_merged_array;
    }
    
    delete[] leftSubArrayOne;
    delete[] rightSubArrayTwo;
    
    
}


#endif