class Solution {
  public:
    void printNumbers(int n) {
        // Your code goes here
        if(n <= 0){
            return;
        }
        cout << n << endl;
        printNumbers(n-1);

    }
};