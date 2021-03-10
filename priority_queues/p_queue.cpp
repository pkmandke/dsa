#include <iostream>
#include <string>
#include "heaps.h"

using namespace std;

// #define MAX_SIZE 50

/* Implemented as a max heap */

priorityQueue::priorityQueue(){ }

priorityQueue::priorityQueue(int *arr, int capacity, string h){
	this->end = capacity;
	this->htype = h;
	for (int i = 1; i <= capacity ; i++) heap[i] = arr[i - 1];
}

priorityQueue::priorityQueue(int capacity, string h){
	this->htype = h;
	this->end = 0;
}
	
void priorityQueue::show_queue(){
	for (int i = 0; i <= this->end; i++) cout << heap[i] << " ";
	cout << endl;
}
	
bool priorityQueue::insert(int key){

        cout << "end " << this->end << endl;

	if (this->end >= MAX_SIZE) return false;

	heap[++this->end] = key;

	//cout << "end " << this->end << endl;
		
	this->swim(key);

	return true;
}

int priorityQueue::remove(){
	if (this->end == 0) return -1;

	int heap_top = heap[1];

	heap[1] = heap[this->end--];
		
	sink();

	return heap_top;
}

bool priorityQueue::isEmpty(){
	if(this->end) return false;
	return true;
}
	
int priorityQueue::getLength(){
	return this->end;
}

int priorityQueue::peek(){
	return this->heap[1];
}

void priorityQueue::swap_int(int p, int q){

	int temp = heap[p];
	heap[p] = heap[q];
	heap[q] = temp;
}
	
/* swim the max element to the top */
void priorityQueue::swim(int key){
		
	int pos = this->end;

	while( pos >= 1 ){
		if(!this->htype.compare(string("max"))){
			if (heap[pos] > heap[pos/2]) swap_int(pos, pos/2);
			else return;
		}
		else if(!this->htype.compare("min")){
			if (heap[pos] < heap[pos/2]) swap_int(pos, pos/2);
                        else return;
		}
		pos /= 2;
	}
}
	
/* Sink the top element downwards */
void priorityQueue::sink(){		
	this->sink(1);	
}

void priorityQueue::sink(int pos){

	int lr = 0; // which of left or right child is larger (or smaller if it's a min heap)
		
	if (this->end == 2){ // If only 2 elements exist in the heap
		if (heap[pos] < heap[2 * pos] && !this->htype.compare("max")){
			swap_int(pos, pos + 1);
			return;
		}
		if (heap[pos] > heap[2 * pos] && !this->htype.compare("min")){
                        swap_int(pos, pos + 1);
                        return;
		}
	}	

        while ((2 * pos + 1) <= this->end){
              	if (heap[2 * pos] >= heap[2 * pos + 1] && !this->htype.compare("max")) lr = 2 * pos;
		else if (heap[2 * pos] <= heap[2 * pos + 1] && !this->htype.compare("min")) lr = 2 * pos;
		else lr = 2 * pos + 1;
                        
		if(!this->htype.compare("max")){
                       	if (heap[pos] < heap[lr]) swap_int(pos, lr); // Swap parent with l/r child (whichever is bigger/smaller). If no swap needed then stop.
                       	else break;
		}
		else if(!this->htype.compare("min")){
			if (heap[pos] > heap[lr]) swap_int(pos, lr); // Swap parent with l/r child (whichever is bigger/smaller). If no swap needed then stop.
                        else break;
		}

                pos = lr; // Update position to follow the sinking element.
	}
}


/* Heap Sort sorts an array in O(N logN) **in-place** as opposed to merge or quick sort */
/* The heap is built (from a random array) in O(N logN). The sorting from the heap happens in O(N) */
int * heap_sort(int *arr, int len){
	priorityQueue *heap = new priorityQueue(arr, len, string("max"));
	
	// Construct Heap in O(N logN)
	for (int i = (len + 1)/2 ; i >= 1; i--) heap->sink(i);
 	
	int k =0;
	
	// Pop top of heap (max element followed by sink())
	for(int i = 1; i <= len; k++, i++){
		arr[k] = heap->remove();
	}

	delete heap;

	return arr;
}

/*
int main(){
	priorityQueue obj(30, string("max"));
	
	int arr[] = {1, 3, 5, 2, 9, 7, 6, 10, 0, 4, 8};

	int * res;
	res = heap_sort(arr, 11);

	for (int i = 0; i < 11; i++) cout << res[i] << " ";

	cout << endl << endl;


	for (int i = 0; i < 10; i += 2) obj.insert(i);
	for (int i = 1; i < 10; i += 2) obj.insert(i);

	obj.show_queue();

	obj.remove();
	obj.show_queue();

	obj.remove();
	obj.show_queue();

	obj.remove();
	obj.show_queue();

	return 0;
}*/
