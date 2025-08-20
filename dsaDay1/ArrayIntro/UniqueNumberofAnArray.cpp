#include <iostream>
#include <climits>
using namespace std;

int main(){
    //Initializtion of an array with size
    int marks[] = {5,2,2,6,5};

    //lets found size of an array how can we find size of array
    int size = sizeof(marks) / sizeof(int);
    
    
    int uniqueNum = 0;
    //Output of array vales
     for(int val:marks){
        uniqueNum ^= val;
     }   
    cout<<uniqueNum;
}