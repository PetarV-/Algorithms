#include<bits/stdc++.h>
using namespace std;

void lin_insert(int a[], int m, int k, int* u)
{
	int i = k%m;
		
	while(1)
	{
		if(a[i]==-1 || a[i]==-777)
		{
			a[i] = k;
			cout << k << " INSERTED AT INDEX " << i << " IN LINEAR PROBING" << endl;
			break;
		}	
		else
		{
			i = (i+1)%m;
			(*u)++;
		}
		
		if(i==k%m)
		{
			cout << k << " CANNOT BE INSERTED IN LINEAR PROBING" << endl;
			break;
		}
	}
}

void lin_search(int a[], int m, int k)
{
	int i = k%m;
	while(1)
	{
		if(a[i]==k)
		{
			cout << k << " FOUND AT INDEX " << i << " IN LINEAR PROBING" << endl;
			break;
		}
		else
		{
			i = (i+1)%m;
		}
		
		if(a[i]==-1 || i==k%m)
		{
			cout << k << " IS NOT PRESENT IN LINEAR PROBING" << endl;
			break;
		}
	}
}

void lin_delete(int a[], int m, int k)
{
	int i = k%m;
	while(1)
	{
		if(a[i]==k)
		{
			cout << k << " DELETED FROM INDEX " << i << " IN LINEAR PROBING" << endl;
			a[i] = -777;
			break;
		}
		else
		{
			i = (i+1)%m;
		}
		
		if(a[i]==-1 || i==k%m)
		{
			cout << k << " CANNOT BE DELETED IN LINEAR PROBING" << endl;
			break;
		}
	}
}


void qua_insert(int a[], int m, int k, int* u)
{
	int t = 0;
	
	while(1)
	{
		int idx = ((k%m) + t + 3*t*t)%m;
		if(a[idx]==-1 || a[idx]==-777)
		{
			a[idx] = k;
			cout << k << " INSERTED AT INDEX " << idx << " IN QUADRATIC PROBING" << endl;
			break;
		}	
		else
		{
			t++;
			(*u)++;
		}
		
		if(t==m)
		{
			cout << k << " CANNOT BE INSERTED IN QUADRATIC PROBING" << endl;
			break;
		}
	}
}

void qua_search(int a[], int m, int k)
{
	int t = 0;
	int idx = ((k%m) + t + 3*t*t)%m;
	
	while(1)
	{
		
		if(a[idx]==k)
		{
			cout << k << " FOUND AT INDEX " << idx << " IN QUADRATIC PROBING" << endl;
			break;
		}	
		else
		{
			t++;
		}
		
		idx = ((k%m) + t + 3*t*t)%m;
		if(a[idx]==-1 || t==m)
		{
			cout << k << " NOT PRESENT IN QUADRATIC PROBING" << endl;
			break;
		}
	}
}

void qua_delete(int a[], int m, int k)
{
	int t = 0;
	int idx = ((k%m) + t + 3*t*t)%m;
	
	while(1)
	{
		
		if(a[idx]==k)
		{
			cout << k << " DELETED FROM INDEX " << idx << " IN QUADRATIC PROBING" << endl;
			a[idx] = -777;
			break;
		}	
		else
		{
			t++;
		}
		
		idx = ((k%m) + t + 3*t*t)%m;
		if(a[idx]==-1 || t==m)
		{
			cout << k << " CANNOT BE DELETED IN QUADRATIC PROBING" << endl;
			break;
		}
	}
}

void dou_insert(int a[], int m, int k, int* u)
{
	int t = 0;
	
	while(1)
	{
		int idx = ((k%m) + t*(1+k%(m-1)))%m;
		if(a[idx]==-1 || a[idx]==-777)
		{
			a[idx] = k;
			cout << k << " INSERTED AT INDEX " << idx << " IN DOUBLE HASHING" << endl;
			break;
		}	
		else
		{
			t++;
			(*u)++;
		}
		
		if(t==m)
		{
			cout << k << " CANNOT BE INSERTED IN DOUBLE HASHING" << endl;
			break;
		}
	}
}

void dou_search(int a[], int m, int k)
{
	int t = 0;
	int idx = (k%m) + t*(1+k%(m-1));
	while(1)
	{
		
		if(a[idx]==k)
		{
			cout << k << " FOUND AT INDEX " << idx << " IN DOUBLE HASHING" << endl;
			break;
		}	
		else
		{
			t++;
		}
		
		idx = (k%m) + t*(1+k%(m-1));
		if(a[idx]==-1 || t==m)
		{
			cout << k << " NOT PRESENT IN DOUBLE HASHING" << endl;
			break;
		}
	}
}

void dou_delete(int a[], int m, int k)
{
	int t = 0;
	int idx = (k%m) + t*(1+k%(m-1));
	while(1)
	{
		
		if(a[idx]==k)
		{
			cout << k << " DELETED FROM INDEX " << idx << " IN DOUBLE HASHING" << endl;
			a[idx] = -777;
			break;
		}	
		else
		{
			t++;
		}
		
		idx = (k%m) + t*(1+k%(m-1));
		if(a[idx]==-1 || t==m)
		{
			cout << k << " CANNOT BE DELETED IN DOUBLE HASHING" << endl;
			break;
		}
	}
}

void endinfo(int a,int b,int c, int n)
{
	cout << "TOTAL NUMBER OF COLLISIONS IN LINEAR PROBING "    << a << endl;
	cout << "TOTAL NUMBER OF COLLISIONS IN QUADRATIC PROBING " << b << endl;
	cout << "TOTAL NUMBER OF COLLISIONS IN DOUBLE HASING "     << c << endl;
	
	float x = a;
	float y = b;
	float z = c;
	cout << setprecision(2) << fixed;
	cout << "AVERAGE NUMBER OF REHASING REQUIRED IS " << x/n << " IN LINEAR PROBING"    << endl;
	cout << "AVERAGE NUMBER OF REHASING REQUIRED IS " << y/n << " IN QUADRATIC PROBING" << endl;
	cout << "AVERAGE NUMBER OF REHASING REQUIRED IS " << z/n << " IN DOUBLE HASHING"	<< endl;
}

int main()
{
	//Enter number of commands and has table size
	int n,m;
	cin >> n >> m;
	
	int arr1[m];
	int arr2[m];
	int arr3[m];
	
	for(int i=0;i<m;i++)
		arr1[i] = arr2[i] = arr3[i] = -1;
	
	int col1 = 0;
	int col2 = 0;
	int col3 = 0;
	int inserts = 0;
	
	for(int t=0;t<n;t++)
	{
		string s;
		int x;

		//"INSERT" , "SEARCH" or "DELETE" followed by a number
		cin >> s >> x;
		
		if(s=="INSERT")
		{
			inserts++;
			lin_insert(arr1,m,x,&col1);
			qua_insert(arr3,m,x,&col2);
			dou_insert(arr2,m,x,&col3);
		}
		
		else if(s=="SEARCH")
		{
			lin_search(arr1,m,x);
			qua_search(arr3,m,x);
			dou_search(arr2,m,x);
		}
		
		else if(s=="DELETE")
		{
			lin_delete(arr1,m,x);
			qua_delete(arr3,m,x);
			dou_delete(arr2,m,x);
		}
		
		else
		{
			cout << "Command not recognised. Use INSERT, SEARCH or DELETE" << endl;
		}
	}
	
	//Prints extra info at end (collisions in each hashing)
	endinfo(col1,col2,col3,inserts);
	
	
}
