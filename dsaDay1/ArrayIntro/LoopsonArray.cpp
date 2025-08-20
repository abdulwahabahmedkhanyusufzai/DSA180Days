#include <iostream>

using namespace std;

int main(){
    //Initializtion of an array with size
    int marks[5] = {1,2,3,4,5};

    //lets found size of an array how can we find size of array
    int size = sizeof(marks) / sizeof(int);
    //Generally we use loops on array for performing opreations
    //For the loop:The array size would go from zero index to size -1
    //Input of array values
    for(int i = 0;i < size;i++){
        cin >> marks[i];
    }

    //Output of array vales
    for(int i = 0;i < size; i++){
        cout << marks[i] << endl;
    }

    //now we can also change this array element
    marks[0] = 21;

    //this is out of bond
    marks[5];

    
}