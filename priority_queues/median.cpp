#include <iostream>
#include <string>
#include "heaps.h"

#define MAX_S 100

using namespace std;

class medianHeaps{
	
	public:
		priorityQueue *min_h, *max_h;

		medianHeaps(){
			cout << "enter constructor" << endl;
			priorityQueue *min_h = new priorityQueue(-1, std::string("min"));
			priorityQueue *max_h = new priorityQueue(-1, std::string("max"));
			cout << "exit" << endl;
		}

		void build_heaps(int *arr, int len){
			
			this->max_h->insert(arr[0]);

			for(int i = 1; i < len; i++){
				cout << "Inserting " << arr[i] << endl;
				if(arr[i] < this->max_h->peek()) this->max_h->insert(arr[i]);
				else this->min_h->insert(arr[i]);
			}
			cout << endl;
		}

		int get_median(){
			cout << this->max_h->getLength() << " " << this->min_h->getLength() << endl;
			if( (this->max_h->getLength() + this->min_h->getLength()) % 2){
				cout << "hereh" << endl;
				if(this->max_h->getLength() > this->min_h->getLength()) return this->max_h->remove();
				else return this->min_h->remove();
			}
			cout << "keys are indeed even" << endl;
			return this->max_h->remove();				
		}

		~medianHeaps(){
			delete this->min_h;
			delete this->max_h;		}
};

int main(){
	
	medianHeaps m;

	int arr[] = {1, 4, 0, 9, 5, 2, 8, 7, 6, 3};

	m.build_heaps(arr, 10);
	cout << "back" << endl;

	cout << m.get_median() << endl;
	
	return 0;
}
