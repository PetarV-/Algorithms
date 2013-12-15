/*
 Petar 'PetarV' Velickovic
 Algorithm: Fast Input
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#define LIMIT 1000000
using namespace std;
typedef long long lld;

char buffer[LIMIT], * pos = buffer + LIMIT;

//Algoritam za brzo ucitavanje odredjenih tipova podataka
//date metode za char, long long/int, float/double, char[]
 
inline char getnext(){
  if (pos == buffer + LIMIT){
    pos = buffer;
    fread(buffer, 1, LIMIT, stdin);
  }
  return *pos++;
}
 
inline lld getint()
{
  lld num = 0;
  bool sign = 0;
  char cc;
  while ( !isdigit(cc = getnext()) ) if (cc == '-') sign = 1;
  do { num = num * 10 + cc - '0'; } while ( isdigit(cc = getnext()) );
  if (sign) return -num;
  else return num;
}

inline double getfloat()
{
  double num=0,rest=1;
  int sign=1;
  while ((cc=getnext())<'0' || cc>'9')
    if (cc=='-') sign=-1;
  do {
    num=num*10+cc-'0';
  }
  while ((cc=getnext())>='0' && cc<='9');
  while ((cc=getnext())>='0' && cc<='9'){
    rest/=10;
    num+=rest*(cc-'0');
  }
  return num*sign;
}

inline void getstr(char niz[])
{
  int i=0;
  char cc;
  while (!isalnum(cc=getnext()));
  do {
    niz[i++]=cc;
  }
  while (isalnum((cc=getnext())));
  niz[i]='\0';
}
