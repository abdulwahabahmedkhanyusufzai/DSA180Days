#include <iostream>
#include <climits>
using namespace std;

int main(){
    //Initializtion of an array with size
    int marks[] = {5,2,1,-1,6,5};

    //lets found size of an array how can we find size of array
    int size = sizeof(marks) / sizeof(int);
    
    
    int minimum_Num = INT_MAX,maximum_Num = INT_MIN,minimum_idx = 0,maximum_idx = 0;
    //Output of array vales
    for(int i = 0;i < size; i++){
        if(marks[i] < minimum_Num){
            minimum_Num = min(minimum_Num,marks[i]);
            minimum_idx = i;
        }

        if(marks[i]>maximum_Num){
            maximum_Num = max(maximum_Num,marks[i]);
            maximum_idx = i;
        }
    }
    
    cout<<"Minimum num is: "<<minimum_Num << "is on index" << minimum_idx << endl;
    cout << "Maximum num is: " << maximum_Num << "is on index" << maximum_idx << endl;
    
}