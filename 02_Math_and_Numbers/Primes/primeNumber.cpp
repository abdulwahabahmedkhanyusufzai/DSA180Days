#include <iostream>
using namespace std;

int main(){
  int n;
  cin >> n;

  if (n <= 1) {
    cout << "N is not Prime Number" << endl;
    return 0;
  }

  bool isPrime = true;
  // Check up to the square root of n for O(sqrt(n)) time complexity
  for(int i=2; i*i<=n; i++){
    if(n % i == 0){
        isPrime = false;
        break;
    }
  }

  if (isPrime){
    cout<<"Prime Number"<<endl;
  }
  else {
    cout<<"N is not Prime Number"<<endl;
  }
  
  
  return 0;
}