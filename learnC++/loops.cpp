#include <iostream>
using namespace std;

int main(){
    string name="wahab";

    for(auto i=0;i<10;i++){
        cout<<name<<endl;
    }
    cout<<"end"<<endl;
    auto i = 0;
    while(i<10){
         cout<<name<<endl;
         i++;
    }

    auto j=8;
    do{
        cout<<name<<endl;
    }while(j<1);

    return 0;
}