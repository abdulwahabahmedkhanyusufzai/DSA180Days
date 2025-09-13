#include <iostream>
using namespace std;

void printPattern1(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j < n;j++){
        cout<<"*";
    }
    cout<<endl;
    }
}

void printPattern2(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        cout<<"*";
    }
    cout<<endl;
    }
}
void printPattern3(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        cout<<j+1;
    }
    cout<<endl;
    }
}
void printPattern4(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        cout<<i+1;
    }
    cout<<endl;
    }
}
void printPattern5(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=n-i-1;j++){
        cout<<"*";
    }
    cout<<endl;
    }
}
void printPattern6(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=n-i-1;j++){
        cout<<j+1;
    }
    cout<<endl;
    }
}
void printPattern7(int n){
    for(int i = 0; i < n;i++){
     for(int j = 0; j <n-i-1;j++){
        cout<<" ";
    }
    for(int j = 0; j <=i;j++){
        cout<<"*";
    }
     for(int j = 0; j <=i-1;j++){
        cout<<"*";
    }
    cout<<endl;
    }
}
void printPattern8(int n){
    for(int i = 0; i < n;i++){
     for(int j = 0; j <=i;j++){
        cout<<" ";
    }
    for(int j = 0; j <=n-i-1;j++){
        cout<<"*";
    } 
    for(int j = 0; j <=n-i-2;j++){
        cout<<"*";
    } 
    cout<<endl;
    }
}

void printPattern9(int n){
    for(int i = 0; i < n;i++){
     for(int j = 0; j <n-i-1;j++){
        cout<<" ";
    }
    for(int j = 0; j <=i;j++){
        cout<<"*";
    }
     for(int j = 0; j <=i-1;j++){
        cout<<"*";
    }
    cout<<endl;
    }
     for(int i = 0; i < n;i++){
     for(int j = 0; j <i;j++){
        cout<<" ";
    }
    for(int j = 0; j <=n-i-1;j++){
        cout<<"*";
    } 
    for(int j = 0; j <=n-i-2;j++){
        cout<<"*";
    } 
    cout<<endl;
    }
}
void printPattern10(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        cout<<"*";
    } 
    cout<<endl;
    }
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=n-i-1;j++){
        cout<<"*";
    } 
    cout<<endl;
    }
}

void printPattern11(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        if(i % 2 == 0 && j % 2 == 0){
           cout<<1;
        }else if(i%2 == 0 && j%2 !=0){
            cout<<0;
        }else if(i%2 != 0 && j % 2 == 0){
            cout<<0;
        }else if(i%2 != 0 && j %2 != 0){
            cout<<1;
        }
    } 
    cout<<endl;
    }
}
void printPattern12(int n){
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        cout<<j+1;
    } 
     for(int j = 0; j <2*(n-i-1);j++){
        cout<<" ";
    }
    for(int j = i; j >=0;j--){
        cout<<j+1;
    }  
    cout<<endl;
    }
}
void printPattern13(int n){
    int num = 1;
    for(int i = 0; i < n;i++){
    for(int j = 0; j <=i;j++){
        cout<<num<<" ";
        num++;
    }   
    cout<<endl;
    }
}
void printPattern14(int n){
    for(int i = 0; i < n;i++){
        char ch = 'A';
        for(int j = 0; j <=i;j++){
        cout<<ch<<" ";
        ch++;
    }   
    cout<<endl;
    }
}
void printPattern15(int n){
    for(int i = 0; i < n;i++){
        char ch = 'A';
        for(int j = 0; j <=n-i;j++){
        cout<<ch<<" ";
        ch++;
    }   
    cout<<endl;
    }
}
void printPattern16(int n){
    for(int i = 0; i < n;i++){
        char ch = 'A'+i;
        for(int j = 0; j <=i;j++){
        cout<<ch<<" ";
    }   
    cout<<endl;
    }
}
void printPattern17(int n){
    for(int i = 0; i < n;i++){
        for(int j = 0; j <n-i-1;j++){
        cout<<" ";
    }
    for(char ch = 'A'; ch <='A'+i;ch++){
        cout<<ch;
    }
   for (char dh = 'A' + i - 1; dh >= 'A'; dh--) {
            cout << dh;
        }
    cout<<endl;
    }
}
void printPattern18(int n){
    for(int i = 0; i < n;i++){
        char start = 'A' + (n-1-i);
    for(char ch = start; ch <='A'+(n-1);ch++){
        cout<<ch;
    };
    cout<<endl;
    }
}
void printPattern19(int n){
    for(int i = 0; i < n;i++){
        char start = 'A' + (n-1-i);
    for(char ch = start; ch <='A'+(n-1);ch++){
        cout<<ch;
    };
    cout<<endl;
    }
}
void printPattern20(int n){
    for(int i =0;i<n;i++){
    for(int j=0;j<=n-i-1;j++){
        cout<<"*";
    }
    for(int j=0;j<2*i;j++){
        cout<<" ";
    }
    for(int j=0;j<=n-i-1;j++){
        cout<<"*";
    }    
    cout<<endl;
    }
        for(int i =0;i<n;i++){
    for(int j=0;j<=i;j++){
        cout<<"*";
    }
    for(int j=2*(n-i-1);j>0;j--){
        cout<<" ";
    }
    for(int j=0;j<=i;j++){
        cout<<"*";
    }    
    cout<<endl;
    }
}
void printPattern21(int n){
        for(int i =0;i<n;i++){
    for(int j=0;j<=i;j++){
        cout<<"*";
    }
    for(int j=2*(n-i-1);j>0;j--){
        cout<<" ";
    }
    for(int j=0;j<=i;j++){
        cout<<"*";
    }    
    cout<<endl;
    }
      for(int i =0;i<n;i++){
    for(int j=0;j<=n-i-1;j++){
        cout<<"*";
    }
    for(int j=0;j<2*i;j++){
        cout<<" ";
    }
    for(int j=0;j<=n-i-1;j++){
        cout<<"*";
    }    
    cout<<endl;
    }
}
void printPattern22(int n){
    for(int i =0;i<n;i++){
    for(int j=0;j<n;j++){
        if(i==0 or j==0 or  i==n-1 or j==n-1){
        cout<<"*";
        }
        else cout<<" ";
    }    
    cout<<endl;
    }
}
void printPattern23(int n){
    int end = (2*n)-1;
    for(int i =0;i<end;i++){
    for(int j=0;j<end;j++){
        int top = i;
        int left = j;
        int right =(end-1)-j;
        int bottom=(end-1)-i;
        
        int layer = min(min(top,bottom),min(left,right));
        cout<<n-layer;
    }    
    cout<<endl;
    }
}
int main(){
   int n;
   cin>>n;
   printPattern23(n);
}

