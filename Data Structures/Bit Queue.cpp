/*
 Petar 'PetarV' Velickovic
 Data Structure: Bit Queue
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
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
using namespace std;
typedef long long lld;

class BitQueue
{
    int valid_bits; //the number of valid bits held in queue
    int queue;      //least significant bit is most recent bit added
public:
    BitQueue(): valid_bits(0),queue(0) {}
    void push(int val, int bsize);
    int pop(int bsize);
    int size();
};

class QueueOverflowException: public exception
{
    virtual const char* what() const throw()
    {
        return "Error: Queue Overflow";
    }
} qoverex;

class QueueUnderflowException: public exception
{
    virtual const char* what() const throw()
    {
        return "Error: Queue Underflow";
    }
} qunderex;

int BitQueue::size()
{
    return this -> valid_bits;
}

void BitQueue::push(int val, int bsize)
{
    if (this -> size() + bsize > 32) throw qoverex;
    this -> queue <<= bsize;
    if (bsize != 32) val &= (1 << bsize) - 1;
    this -> queue |= val;
    this -> valid_bits += bsize;
}

int BitQueue::pop(int bsize)
{
    if (this -> size() < bsize) throw qunderex;
    int shift_amount = this -> size() - bsize;
    int ret;
    if (bsize != 32) ret = ((this -> queue) >> shift_amount) & ((1 << bsize) - 1);
    else ret = this -> queue;
    this -> valid_bits -= bsize;
    return ret;
}

void send(char x)
{
    printf("sent 0x%x\n", (unsigned char)x); //stub method for testing
}

void sendmsg(const char* msg)
{
    BitQueue *aux = new BitQueue();
    int len = strlen(msg);
    for (int i=0;i<len;i++)
    {
        if (msg[i] == 'a') aux -> push(0, 1);
        else if (msg[i] == 'b') aux -> push(2, 2);
        else if (msg[i] == 'c') aux -> push(12, 4);
        else if (msg[i] == 'd') aux -> push(13, 4);
        
        if (aux -> size() >= 8)
        {
            char curr = (char)(aux -> pop(8));
            send(curr);
        }
    }
    aux -> push(7, 3);
    while (aux -> size() >= 8)
    {
        char curr = (char)(aux -> pop(8));
        send(curr);
    }
    if (aux -> size() > 0)
    {
        int to_shift = 8 - aux -> size();
        char curr = (char)(aux -> pop(aux -> size())) << to_shift;
        send(curr);
    }
    delete aux;
}

int main()
{
    BitQueue *test = new BitQueue();
    test -> push(55, 5);
    test -> push(127, 5);
    printf("%d\n", test -> size());
    printf("%d\n", test -> pop(5));
    printf("%d\n", test -> pop(5));
    printf("%d\n", test -> size());
    
    sendmsg("abcd");
    
    return 0;
}

