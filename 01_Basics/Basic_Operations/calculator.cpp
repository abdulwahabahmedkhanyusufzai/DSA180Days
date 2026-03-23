#include <iostream>
using namespace std;

int main(){
    int a,b;
    cout<<"Enter first number";
    cin>>a;
    char sign;
    cout<<"Enter operator";
    cin>>sign;
    cout<<"Enter second number";
    cin>>b;
    if (sign == '+'){
    int sum = a + b;
    cout << "Sum of " <<a <<" and "<<b <<" is "<<sum<<endl;
}else if(sign == '-'){
    int minus = a-b;
    cout << "Minus of " <<a <<" and "<<b <<" is "<<minus<<endl;
}else if(sign == '*'){
    int product = a*b;
    cout << "Product of " <<a <<" and "<<b <<" is "<<product<<endl;
}else if(sign == '/'){
    int divison = a/b;
    cout << "Division of " <<a <<" and "<<b <<" is "<<divison<<endl;
}else if(sign == '%'){
    int divison = a%b;
    cout << "Modulo of " <<a <<" and "<<b <<" is "<<divison<<endl;
}


    return 0;
}