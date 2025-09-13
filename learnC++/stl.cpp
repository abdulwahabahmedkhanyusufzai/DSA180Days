#include <iostream>
#include <vector>
using namespace std;

int main(){
 //vector 
 //vector declartion
 vector<int> vec = {1,2,3};
 //vector<int> vec(3,10);
 //vector<int> vec2(vec);
 //add element into the array 
 vec.push_back(3);
 //vector size
 cout<<vec.size()<<endl;
 //vector capacity
 cout<<vec.capacity()<<endl;

  //erase vector
 vec.erase(vec.begin()+2);
  //insert vector
 vec.insert(vec.begin()+2,100);

 //vector delete
 //loop on vector
 for(int val:vec){
    cout<<val<<" ";
 }
 cout<<endl;

 cout<<"value at the idx 2 is "<< vec[2] << " or " << vec.at(2)<<endl;
 cout<<"front of array "<<vec.front() <<" and back of " << vec.back() << endl;

 
}