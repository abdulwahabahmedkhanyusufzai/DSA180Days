#include <iostream>
using namespace std;

void printName(string name){
    cout<<"hey "<<name<<endl;
}
void printSum(int num1,int num2){
     cout<<"Sum of "<<num1 <<" and "<<num2<<" is "<<num1+num2<<endl;
}
int main(){
  string name;
  getline(cin,name);
  printName(name);
  int num1,num2;
  cin>>num1>>num2;
  printSum(num1,num2);

}