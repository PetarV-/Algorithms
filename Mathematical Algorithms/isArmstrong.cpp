#include<iostream>
#include<math.h>
using namespace std;

bool isArmstrong(int num){
    int temp = num,
        sum = 0,
        power;

    power = std::to_string(temp).length();
    /*
        std::to_string(integer) coverts our number into a string so as to operate upon it various string
        functionalities
    */
    // cout<<power;

    while(num>=1){
        sum = sum + pow((num%10), power);
        num = num/10;
    }
    return(sum == temp);
}

int main(){
    int n;
    cin>>n;

    isArmstrong(n)?cout<<"true":cout<<"false";
    return 0;
}
