#include <iostream>
using namespace std;

int main(){
    //output
    cout<<"Hello World"<<endl;
    cout<<"Striver DSA"<<endl;
    //input
    int x;
    //cin>>x;
    cout<<x<<endl;
   // int range:            -2,147,483,648 to 2,147,483,647
// unsigned short range:  0 to 65,535
// long range (Win 32):   -2,147,483,648 to 2,147,483,647
// long range (Linux 64): -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
// unsigned long (Win 32): 0 to 4,294,967,295
// unsigned long (Linux 64): 0 to 18,446,744,073,709,551,615
// long long:             -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807

// float:  1.2E-38 to 3.4E+38
// double: 2.3E-308 to 1.7E+308
// long double (GCC x86): 3.4E-4932 to 1.1E+4932
// long double (MSVC):    same as double

    float time=16.57;
    string s1;
    string s2;
    //cin>>s1>>s2;
    string str;
    //getline(cin,str);
    cout<<str<<endl;

    char ch;
    
    int age=18;

    if(age>=18){
        cout<<"You are an adult";
    }else{
        cout<<"You are not an adult";
    }

    int marks;
    cin >> marks;
    if(marks<25){
        cout<<"F";
    }else if(marks >=25 and marks <= 44){
        cout<<"E";
    }else if(marks>=45 and marks <= 49){
        cout<<"D";
    }else if(marks >= 50 and marks >= 59){
        cout<<"C";
    }else if(marks >= 60 and marks <= 79){
        cout<<"B";
    }else if(marks >= 80 and marks <= 100){
        cout<<"A";
    }
    return 0;
}