
#pragma once
#ifndef QUICK_SORT_H_KNOWN
#define QUICK_SORT_H_KNOWN

int Partition(int* arr, int left, int right);
void swapp(int* arr, int i, int pIndex);

void QuickSort(int* arr, int const begin, int const end)
{
    if (begin >= end)
        return;
    int pIndex = Partition(arr, begin, end);

    QuickSort(arr, begin, pIndex-1);
    QuickSort(arr, pIndex+1, end);

}

int Partition(int* arr, int left, int right)
{
    int pivot = arr[right];
    int pIndex = left;

    for(int i=left; i < right; ++i)
    {
        if (arr[i] <= pivot)
            {
                if (i != pIndex)  
                    swapp(arr, i, pIndex);
                ++pIndex;
            }
    }

    swapp(arr, right, pIndex);
    return pIndex;
}

void swapp(int* arr, int i, int pIndex)
{
    int temp = arr[pIndex];
    arr[pIndex] = arr[i];
    arr[i] = temp;
}



#endif