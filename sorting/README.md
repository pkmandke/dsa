# Sorting

## Selection Sort


## Insertion Sort

1. Maintain a sorted half and an unsorted half of the array with only the first element in the sorted half to begin with.
2. For the first element in the unsorted half, *insert* it in the right place in the sorted half to maintain the invariance property. (the condition of the sorted half being sorted).
  * This step can potentially be implemented using binary search (?)
3. Repeat step 2 until the unsorted half is empty.

### Notes

1. Insertion sort is O(n^2/4). (Proof is mathematically rigorous)
2. If an array is partially sorted\*, insertion sort runs in linear time and is thus better than selection sort.

\* **Partially sorted arrays**: An array is said to be partially sorted when the number of inversions are less than or equal *cN*.
Two cases for this are 1) a sorted array is appended with a smaller unsorted one, or 2) an array has only a few elements that are out-of-place.

## Shell sort

1. Choose an [h-sequence](https://en.wikipedia.org/wiki/Shellsort#Gap_sequences) for the given array length.
2. For each h value in decreasing order, perform an h-insertion sort on the array.

## Shuffling - An application of sorting

Consider the problem of shuffling an array uniformly.
One idea is to pick a randim *real* number for each element of the array and sort the array using the random numbers as key.
The down side of this approach is that this requires a sort to be done (read at least O(NlogN)).
Can we do better and yet achieve uniform shuffling?

### Knuth Shuffle

A linear time uniform shuffling algorithm.
1. Iterate over the array, with current index denoted by i.
2. In each iteration, pick a random number between [0, i] *uniformly* denoted by *r*.
3. Swap array[i] with array[r].
4. Repeat

**Notes**
1. At iteration *i*, the random number must be picked between [0, i] and NOT [0, N-1].
The later does not lead to uniform shuffling.
2. In practice, use a hardware based random number generator that has passed certain compliance tests.
3. Even hardware random generators may fail silently, so be sure to validate them periodically.

## Convex Hull - An application
### Notes

1. Choosing an appropriate/optimal h-sequence is an open problem!
2. For an h-sequence of type 3x+1, the worst case complexity is O(n^1.5)
3. A practically useful, hardware friendly (due to small code footprint, it's basically just applying insertion sort a bunch of times) and fast (except for very huge arrays) sorting algorithm.

## Footnotes

1. **Invariant property**: A condition that must be satisfied at every instance by a given entity. In case of sorting, the invariant is that the sorted half must always be sorted.


