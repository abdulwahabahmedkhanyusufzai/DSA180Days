#include <iostream>
#include <climits>
using namespace std;

int main(){
    //Initializtion of an array with size
    int marks[] = {5,2,1,-1,6,5};

    //lets found size of an array how can we find size of array
    int size = sizeof(marks) / sizeof(int);
    
    
    int min_idx = 0,max_idx = 0;
    //Output of array vales
    for(int i = 0;i < size; i++){
        if(marks[i] < marks[min_idx]){
            min_idx= i;
        }

        if(marks[i]>marks[max_idx]){
            max_idx= i;
        }
    }


        swap(marks[min_idx],marks[max_idx]);
    
     for(int val:marks){
        cout<<val << " ";
     }   
}