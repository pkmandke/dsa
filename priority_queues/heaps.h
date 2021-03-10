#ifndef _HEAPS_H_
#define _HEAPS_H_

#include <string>

#define MAX_SIZE 100

class priorityQueue{

	public:
                int heap[MAX_SIZE];
                int end;
		std::string htype;
		
		priorityQueue();
		priorityQueue(int, std::string);
		priorityQueue(int *, int, std::string);

	        void show_queue();
		
		bool insert(int key);

		int remove();

		bool isEmpty();

		int getLength();

		int peek();
		
		void swim(int key);

		void sink();

		void sink(int);

	private:

		void swap_int(int p, int q);
};

#endif
