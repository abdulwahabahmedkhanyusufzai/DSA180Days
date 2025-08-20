#include <iostream>
#include <climits>
using namespace std;

int main(){
    //Initializtion of an array with size
    int marks[] = {5,2,1,-1,6,5};

    //lets found size of an array how can we find size of array
    int size = sizeof(marks) / sizeof(int);
    
    
    int target = 6,idx;//Output of array vales
    //Linear Search
    for(int i = 0;i < size; i++){
        if(marks[i] == target){
            idx = i;
        }

    }
}