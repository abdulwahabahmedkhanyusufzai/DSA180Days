#include <iostream>

using namespace std;

int main(){
    //Initializtion of an array with size
    //data type + array name + size = {elements}
    int marks[5] = {1,2,3,4,5};

    //size can vary
    double prices[] = {100.87,42.76,54.76};

    //accessing an element in an array
    //now we can treat this element as a value as well
    marks[0];

    //now we can also change this array element
    marks[0] = 21;

    //this is out of bond
    marks[5];

    
}