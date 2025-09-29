#include <iostream>
using namespace std;

int main() {
    int age;
    string name;
    char grade;
    cout << "Enter your age: ";
    cin >> age;
    cin.ignore();   // clears leftover newline

    cout << "Enter your full name: ";
    getline(cin, name);

    cout << "Enter your grade";
    cin>>grade;

    cout << "My name is: " << name 
         << ",and I am " << age << "years old," << "and my grade is" << grade << endl;

    return 0;
}
