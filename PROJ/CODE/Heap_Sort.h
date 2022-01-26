
#pragma once
#ifndef HEAP_SORT_H_KNOWN
#define HEAP_SORT_H_KNOWN

void heapify(int* arr, int n, int i);
void swap_h(int* arr, int x, int y);

void Heapsort(int* arr, int n)
{
    for(int i= n/2 -1; i >= 0; --i)
        heapify(arr, n, i);
    
    for(int i= n-1; i >= 0; --i)
    {
        swap_h(arr, 0, i);

        heapify(arr, i, 0);
    }
}

void heapify(int* arr, int n, int i)
{
    int largest = i;
    int left = 2*i +1;
    int right = 2*i +2;

    if(left < n && arr[left] > arr[largest])
        largest = left;
    if(right < n && arr[right] > arr[largest])
        largest = right;
    
    if(largest != i)
    {
        swap_h(arr, i, largest);
        heapify(arr, n, largest);
    }
}

void swap_h(int* arr, int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}


#endif