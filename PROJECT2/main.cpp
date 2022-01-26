
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <chrono>
#include "CODE/BST.h"
#include "CODE/AVL.h"
#include "utility.h"

using namespace std;
using std::chrono::nanoseconds; 

constexpr int maxlen = 10000;
constexpr int sizes = 0;


int main(int argc, char* args[])
{
    std::random_device rd;
    std:mt19937 gen(time(NULL));
    std::uniform_int_distribution<int> dist(-2 * maxlen, maxlen*2);

    
    int* arr = new int[maxlen];
    int* ordered_data = new int[maxlen];
    int* low_entropy = new int[maxlen];

    BinarySearchTree bst, bst_ordered_tree, bst_low_tree;
    AVL_Tree avl, avl_ordered_tree, avl_low_tree;

    fstream bst_random_file("DATA/BST/insert/random.txt", ios::out);
    fstream bst_ordered_file("DATA/BST/insert/ordered.txt", ios::out);
    fstream bst_low_file("DATA/BST/insert/low_entropy.txt", ios::out);

    fstream avl_random_file("DATA/AVL/insert/random.txt", ios::out);
    fstream avl_ordered_file("DATA/AVL/insert/ordered.txt", ios::out);
    fstream avl_low_file("DATA/AVL/insert/low_entropy.txt", ios::out);

    fstream bst_search_random("DATA/BST/search/search_random.txt", ios::out);
    fstream bst_search_ordered("DATA/BST/search/search_ordered.txt", ios::out);
    fstream avl_search_random("DATA/AVL/search/search_random.txt", ios::out);
    fstream avl_search_ordered("DATA/AVL/search/search_ordered.txt", ios::out);

    fstream bst_search_low("DATA/BST/search/search_low.txt", ios::out);
    fstream avl_search_low("DATA/AVL/search/search_low.txt", ios::out);

    

    

    //1. Pseudo-Random Generation
    for(int i=0; i<maxlen; ++i)
        arr[i] = dist(gen);

    //2.Ordered Data Generation
    copy_arr(arr, ordered_data, maxlen);
    std::sort(ordered_data, ordered_data+maxlen);

    //3. Low Entropy Data
    copy_arr(ordered_data, low_entropy, maxlen);
    make_low_entropy(low_entropy, maxlen, gen);

   
    // FOR RANDOM DATA LOOP
    for(int i=0; i<maxlen; ++i)
    {
        nanoseconds bst_random(0);
        nanoseconds avl_random(0);

        nanoseconds bst_search_IN(0);
        nanoseconds bst_search_NOT(0);

        nanoseconds avl_search_IN(0);
        nanoseconds avl_search_NOT(0);

        bst_random = timeit(bst, arr[i]);
        bst_search_IN = timeit_search(bst, arr[i]); // IN
        if(i != maxlen-1)
        bst_search_NOT = timeit_search(bst, arr[i + 1]); // NOT IN
        
        avl_random = timeit(avl, arr[i]);
        avl_search_IN = timeit_search(avl, arr[i]); // IN
        if(i != maxlen-1 )
            avl_search_NOT = timeit_search(avl, arr[i + 1]); // NOT

        bst_random_file << i << "  " << bst_random.count() << endl;
        avl_random_file << i << "  " << avl_random.count() << endl;   

        bst_search_random << i << "  " << bst_search_IN.count() << "  " << bst_search_NOT.count() << endl;   
        avl_search_random << i << "  " << avl_search_IN.count() << "  " << avl_search_NOT.count() << endl; 
    }

    //FOR ORDERED DATA LOOP
    for(int i=0; i<maxlen; ++i)
    {
        nanoseconds bst_ordered(0);
        nanoseconds avl_ordered(0);

        nanoseconds bst_search_IN(0);
        nanoseconds bst_search_NOT(0);

        nanoseconds avl_search_IN(0);
        nanoseconds avl_search_NOT(0);

        bst_ordered = timeit(bst_ordered_tree, ordered_data[i]);
        bst_search_IN = timeit_search(bst, ordered_data[i]); // IN

        bst_search_NOT = timeit_search(bst, ordered_data[i + 1]); //NOT


        avl_ordered = timeit(avl_ordered_tree, ordered_data[i]);

        avl_search_IN = timeit_search(avl, ordered_data[i]);
        avl_search_NOT = timeit_search(avl, ordered_data[i + 1]);

        bst_ordered_file << i << "  " << bst_ordered.count() << endl;
        avl_ordered_file << i << "  " << avl_ordered.count() << endl;

        bst_search_ordered << i << "  " << bst_search_IN.count() << "  " << bst_search_NOT.count() << endl;
        avl_search_ordered << i << "  " << avl_search_IN.count() << "  " << avl_search_NOT.count() << endl;
    }

    // FOR LOW ENTROPY DATA
    for(int i=0; i<maxlen; ++i)
    {
        nanoseconds bst_low(0);
        nanoseconds avl_low(0);

        nanoseconds bst_search_IN(0);
        nanoseconds bst_search_NOT(0);

        nanoseconds avl_search_IN(0);
        nanoseconds avl_search_NOT(0);

        bst_low = timeit(bst_low_tree, low_entropy[i]);

        bst_search_IN = timeit_search(bst, low_entropy[i]); // IN
        bst_search_NOT = timeit_search(bst, low_entropy[i + 1]); //NOT
        
        avl_low = timeit(avl_low_tree, low_entropy[i]);

        avl_search_IN = timeit_search(avl, low_entropy[i]);
        avl_search_NOT = timeit_search(avl, low_entropy[i + 1]);

        bst_low_file << i << "  " << bst_low.count() << endl;
        avl_low_file << i << "  " << avl_low.count() << endl; 

        bst_search_low << i << "  " << bst_search_IN.count()  << "  " << bst_search_NOT.count() << endl;
        avl_search_low << i << "  " << avl_search_IN.count()  << "  " << avl_search_NOT.count() << endl;
    }

    
    bst.clear(bst.get_root());
    avl.clear(avl.get_root());

    delete[] arr;
    delete[] ordered_data;
    delete[] low_entropy;

    bst_random_file.close();
    bst_ordered_file.close();
    bst_low_file.close();
    avl_random_file.close();
    avl_ordered_file.close();
    avl_low_file.close();
    bst_search_random.close();
    bst_search_ordered.close();
    bst_search_low.close();
    avl_search_random.close();
    avl_search_ordered.close();
    avl_search_low.close();
    return 0;
}







