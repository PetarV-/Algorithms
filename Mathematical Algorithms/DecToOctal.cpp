#include<iostream>
using namespace std;

void decToOct(int num) 
{	int arr[50], i = 0; 
    
	while (num != 0) { 
        arr[i] = num % 8; 
        num /= 8; 
        i++; 
    } 
	
    for (int j = i - 1; j >= 0; j--) 
        cout << arr[j]; 
} 

int main() 
{ 
    int n;
	cin >>n; 

    decToOct(n);
  
    return 0; 
} 