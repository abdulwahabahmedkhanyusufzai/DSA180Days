class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
      int m = mat.size();
      int n = mat[0].size();
      for(int row=0;row<m;row++){
       for(int j=0;j<n;j++){
        if(mat[row][j] != mat[row][(j+k)%n]){
            return false;
        }
       }
      } 
      return true; 
    }
};