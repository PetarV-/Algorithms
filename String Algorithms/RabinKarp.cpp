/*
Author: Shubham Kumar (/shubhamk0027)
Algorithm: Rabin Karp
*/
#include<bits/stdc++.h>
#define ll int64_t
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define vi vector<int>

using namespace std;
const ll M =1e9+7, B =127;
// M and B should be a prime number
 
string text,patt;

void rabinKarp(){
    ll ht=0, tmp=0,s1=patt.size(),b=1;
    for(int i=0;i<s1;i++) {
        ht= ((ht*B)%M +(patt[i]))%M;
        tmp=((tmp*B)%M+(text[i]))%M;
        if(i) b=(b*B)%M;
    }
    for(int i=s1;i<text.size();i++){
        if(tmp==ht) cout<<i-s1<<"\n";
        tmp =  (M+tmp-(b*(text[i-s1]))%M)%M;
        tmp =  (tmp*B + text[i])%M;
    }
    if(tmp==ht) cout<<text.size()-s1<<"\n";
}


int main() {
    int n;
    cin>>n;
    while(n--){
        cin>>patt; // pattern
	cin>>text; // text
	cout<<"The \""<<patt<<"\" occurs in \""<<text<<"\" at-\n";
        rabinKarp();
        cout<<"\n";
    }
    return 0;
}
