#include <iostream>
#include <climits>
#include <random>
#include <algorithm>

#include "../commons/common.h"

#define STRICT 1

using namespace std;

int exch(int *a, int *b){
/* Swap a and b */
    
    int t = *a;
    *a = *b;
    *b = t;
}


/* The Knuth Shuffling algorithm for uniformly shuffling an array in linear time */
void knuth_shuffle(vector<int> &array, int size){
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    
    for(int i = 1; i < size; i++) exch(&array[i], &array[std::uniform_int_distribution<>(0, i)(gen)]);
}

class Sorting{
    public:

        static int less(int a, int b){
        /* Returns 1 if a < b;
         * 0 otherwwise;
         */
            if (a < b) return 1;
            
            return 0;
        }

        static int exch(int *a, int *b){
        /* Swap a and b */
            
            int t = *a;
            *a = *b;
            *b = t;
        }

        static void selection_sort(vector<int> &array, int size){
        /* At each iteration, select the smallest element from the unsorted half of the array and swap it with the 
         * first element in the unsorted half. Increment the size of the sorted half by one.
         */
            int min_index = 0;

            for(int pos = 0; pos < size; pos++){
                int min_value = INT_MAX;
                for(int i = pos; i < size; i++)
                    if(Sorting::less(array[i], min_value)){
                        min_value = array[i];
                        min_index = i;
                    }
                Sorting::exch(&array[pos], &array[min_index]);
            }
        }

        static void insertion_sort(vector<int> &array, int size, int h_value = 1){
            
            for(int pos = h_value; pos < size; pos++)
                for(int i = pos; i > 0; i -= h_value)
                    if(Sorting::less(array[i], array[i - h_value])) Sorting::exch(&array[i], &array[i - h_value]);
                    else break;
        
        }
        
        /* A utility for Shell sort that returns the h-sequence for a given array size */
        static void get_h_sequence(vector<int> &a, int n){
           
            for(int x = 0; (3 * x + 1) < n; x = 3 * x + 1) a.push_back(3 * x + 1); 
        }

        /* The Shell sort algorithm, as described in the Algorithms course on coursera by Princeton University. */
        static void shell_sort(vector<int> &array, int size){
            vector<int> h_sequence;

            Sorting::get_h_sequence(h_sequence, size);
            
            for(int h = 0; h < h_sequence.size(); h++)
                Sorting::insertion_sort(array, size, h_sequence[h]);
        }
        
        /* Bottom-up merge sort, a iterative version of merge sort */
        static void bottom_up_mergesort(vector<int> &array, int size){
       
            int N = array.size();

            for(int size = 1; size < N; size *= 2)
                for(int offset = 0; offset < (N - size); offset += (2 * size)){
                    cout << offset << ", " << offset + size - 1 << ", " << std::min(offset + 2 * size - 1, N - 1) << endl;
                    Sorting::_merge_sorted_halves(array, offset, offset + size - 1, std::min(offset + 2 * size - 1, N - 1));
                }
        }

        static void merge_sort(vector<int> &array, int size){
        /* The merge sort algorithm */
            Sorting::_split_array_and_sort(array, 0, size - 1);    
        }
        
        /* Quick Sort: In-place O(NlgN) sort which is slightly faster than merge sort.
         * Average case performance is O(N^2).
         * Does not work well for almost sorted arrays. 
         * Practical sorting methods rely on Quick Sort and shift to insertion sort for smaller sub-arrays.
         */
        static void quick_sort(vector<int> &array, int size){
            
            knuth_shuffle(array, size); // Shuffle the array for stability. For one, this helps avoid the case of the array being almost sorted.

            _quick_sort_split(array, 0, size - 1);
        }
        
        /* Quick Select: A probabilistically linear time algorithm to select the kth largest element in an array
         * Based on Quick sort
         */
        static int quick_select(vector<int> array, int size, int k){
            
            knuth_shuffle(array, size);
            common::display_vector(array, size);
            int lo = 0, hi = size - 1;
            int j;

            while(hi > lo){
                
                j = Sorting::_quick_sort_swap_subarray(array, lo, hi);
                if(j > k) hi = j - 1;
                else if(j < k) lo = j + 1;
                else return array[j];
            }

            return array[j];
        }

        private:

        static void _split_array_and_sort(vector<int> &array, int lo, int hi){
        /* Utility to split an array recursively into equal havles, sort each half and merge the sorted halves */

            if(hi <= lo) return; // Base condition for recursion
            
            int mid = (hi + lo) / 2;

            Sorting::_split_array_and_sort(array, lo, mid);
            Sorting::_split_array_and_sort(array, mid + 1, hi);

            Sorting::_merge_sorted_halves(array, lo, mid, hi);
        }

        static void _merge_sorted_halves(vector<int> &array, int lo, int mid, int hi){
        /* Utility for Merge sort to merge two sorted subhavles. */

            vector<int> subpart(array.cbegin() + lo, array.cbegin() + hi + 1); // Clone the subpart of the original array that is under consideration

            int  k = lo;
            int i = 0, j = mid - lo + 1;
            while( (i < (mid - lo + 1)) && (j < subpart.size()) ){
                if (subpart[i] > subpart[j])
                    array[k++] = subpart[j++];
                else array[k++] = subpart[i++];
            }

            while(i < (mid - lo + 1)) array[k++] = subpart[i++];
            while(j < subpart.size()) array[k++] = subpart[j++];
        }

        static void _quick_sort_split(vector<int> &a, int lo, int hi){
           
            if(lo >= hi) return;

            int j = _quick_sort_swap_subarray(a, lo, hi);
            Sorting::_quick_sort_split(a, lo, j - 1);
            Sorting::_quick_sort_split(a, j + 1, hi);
        }

        static int _quick_sort_swap_subarray(vector<int> &a, int lo, int hi){
            
            int key = a[lo];
            int i = lo + 1, j = hi;

            while(1){
                
                while(i < hi && a[i] <= key) i++;
                while(j > lo && a[j] >= key) j--;

                if(j <= i) break;

                Sorting:exch(&a[i], &a[j]);
            }

            Sorting::exch(&a[lo], &a[j]);

            return j;
        }
};

int main(int argc, char *argv[]){

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 1000);
    
    vector<int> array;
    int sz = 5;

    for (int n = 0; n < sz; n++) array.push_back(distrib(gen));
    

    // Sorting::selection_sort(array, sz);
    // Sorting::insertion_sort(array, sz);
    // Sorting::bottom_up_mergesort(array, sz);
    
    cout << "Original Array: " << endl;
    common::display_vector(array, sz);
    
    cout << "Element: " << Sorting::quick_select(array, sz, 0) << endl;

    cout << "Sorted Array: " << endl;
    common::display_vector(array, sz);
    
    if( is_sorted(array.begin(), array.end()) ) cout << "Array is sorted" << endl;
    else cout << "Array ain't sorted :(" << endl;
    /*
    Sorting::shell_sort(array, sz);
    cout << "Sorted Array: " << endl;
    common::display_vector(array, sz);
    
    knuth_shuffle(array, sz);
    cout << "Shuffled array: " << endl;
    common::display_vector(array, sz);
    */
    return 0;
}
