#include<iostream>
#include<math.h>
using namespace std;

//checks if it is perfect square or not
bool isSqrt(int num){
    int s = sqrt(num);
    return(s*s == num);
}

//checks if it the two terms 5n^2 + 4 are perfect squares or not
bool isFibonacci(int n){
    return isSqrt(5*n*n + 4) || isSqrt(5*n*n - 4);
}

int main(){
    //the main principle behind whether a number is a fibonacci series element or not is,
    // say the number is n, it is in fibonacci, if and only if, one or both, (5n^2 + 4) and (5n^2 - 4) are perfect squares.

     int number;

     cout<<"Enter the number which you want to search inside the series: ";
     cin>>number;

     isFibonacci(number)? cout<<"Yes the number is present in series." :
                          cout<<"No, it is not present in the list.";
}
