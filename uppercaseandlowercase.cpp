#include <iostream>
using namespace std;

int main(){
  char grade;
  cin>>grade;

  if(grade >= 'A' and grade <='Z'){
    cout<<"Grade is UpperCase";
  }else if(grade >= 'a' and grade <= 'z'){
    cout<<"Grade is Lowercase";
  }

    return 0;
}