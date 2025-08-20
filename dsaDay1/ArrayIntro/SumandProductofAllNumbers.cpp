#include <iostream>
#include <climits>
using namespace std;

int main(){
    //Initializtion of an array with size
    int marks[] = {5,2,1,-1,6,5};

    //lets found size of an array how can we find size of array
    int size = sizeof(marks) / sizeof(int);
    
    int add=0,product=1;
    //Two pointers
    int left = 0,right = size-1;
    while(left < right){
    add += marks[left]+marks[right];
    product *= marks[left] * marks[right];
        left++,right--;

    }

    cout << add << " " << product ;
    
}