#include <iostream>

using namespace std;

int main(){
 int marks;
    cin >> marks;
    if(marks<25){
        cout<<"F";
    }else if(marks >=25 and marks <= 44){
        cout<<"E";
    }else if(marks>=45 and marks <= 49){
        cout<<"D";
    }else if(marks >= 50 and marks <= 59){
        cout<<"C";
    }else if(marks >= 60 and marks <= 79){
        cout<<"B";
    }else if(marks >= 80 and marks <= 100){
        cout<<"A";
    }
    

    int age;
    cin>>age;

    if(age>57){
        cout<<"Retirement soon";
    }
    else if(age>=18){
        cout<<"Eligible for job";
    if(age>=55 and age <= 57){
        cout<<", but retirement soon";
    }
    }

    int day;
    cin>>day;
    switch(day){
        case 1:
        cout<<"Monday";
        break;
        case 2:
        cout<<"Tuesday";
        break;
        case 3:
        cout<<"Wednesday";
        break;
        case 4:
        cout<<"Thursday";
        break;
        case 5:
        cout<<"Friday";
        break;
        case 6:
        cout<<"Saturday";
        break;
        case 7:
        cout<<"Sunday";
        break;
        default:
        cout<<"Ended";
    }
    return 0;
}