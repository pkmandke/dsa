#include <iostream>

#include "common.h"

using namespace std;

void common::display_vector(vector<int> a, int size){
    
    for(int i = 0; i < size; i++) cout << a[i] << "  ";

    cout << endl;
}
