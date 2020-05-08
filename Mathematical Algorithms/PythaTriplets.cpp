#include <iostream>
using namespace std;

int main() {
	int num;
	cin>>num;
	
	if(num == 1 || num == 2){
	    cout<<"-1";
	}
	
	/*
        for pythagorean triplets, 
        
        if n is even, 
            the triplets could be given by, 
             n^2/4-1, n and n^2/4+1
             so if a variable say, var = n^2/4-1, then
             
             a = var
             b = n
             c = var + 2
            
        if n is odd, 
            the triplets could be given by, 
             (n^2-1)/2, n and (n^2+1)/2
             so if a variable say, var = (n^2-1)/2, then
             
             a = var
             b = n
             c = var + 1
	*/
	
	else if(num%2==0){
            long m=num/2;
            long n=1;
            cout<<(m*m-n*n)<<" "<<(m*m+n*n);
        }else{
            long m=(num + 1)/2;
            long n=(num - 1)/2;
            cout<<(2*m*n)<<" "<<(m*m+n*n);
        }
	return 0;
}