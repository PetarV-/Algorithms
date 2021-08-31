#include<bits/stdc++.h>
#include "matrix_functions.h"
using namespace std;

double getDeterminant(vector<vector<double>> a)
{
    if(a.size() != a[0].size()) 
	{
        throw runtime_error("Matrix must be square");
    } 
    int d = a.size();
    if(d == 0) 
    {
        return 1;
    }
    if(d == 1) 
    {
        return a[0][0];
    }
    if(d == 2) 
    {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    double ans = 0;
    int sign = 1;
    for(int i = 0; i < d; i++) 
    {
        vector<vector<double>> subVect(d - 1, vector<double> (d - 1));
        for(int m = 1; m < d; m++)
        {
            int z = 0;
            for(int n = 0; n < d; n++) 
            {
                if(n != i) 
                {
                    subVect[m-1][z] = a[m][n];
                    z++;
                }
            }
        }
        ans = ans + sign * a[0][i] * getDeterminant(subVect);
        sign = -sign;//As sign changes with consecutive cofactors
    }

    return ans;
}

vector<vector<double>> getTranspose(vector<vector<double>> a)
 {
    vector<vector<double>> ans(a[0].size(), vector<double> (a.size()));
    for(int i = 0; i < a.size(); i++) 
	{
        for(int j = 0; j < a[0].size(); j++) 
		{
            ans[j][i] = a[i][j];
        }
    }
    return ans;
}

vector<vector<double>> getCofactor(const vector<vector<double>> a) 
{
    if(a.size() != a[0].size()) 
	{
        throw runtime_error("Matrix must be square");
    } 
    vector<vector<double>> solution(a.size(), vector<double> (a.size()));
    vector<vector<double>> subVect(a.size() - 1, vector<double> (a.size() - 1));

    for(int i = 0; i < a.size(); i++) 
    {
        for(int j = 0; j < a[0].size(); j++) 
        {
            int p = 0;
            for(int x = 0; x < a.size(); x++)
			 {
                if(x == i) {
                    continue;
                }
                int q = 0;

                for(int y = 0; y < a.size(); y++)
				 {
                    if(y == j) {
                        continue;
                    }

                    subVect[p][q] = a[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j) * getDeterminant(subVect);
        }
    }
    return solution;
}

vector<vector<double>> getInverse(vector<vector<double>> a) 
{
    if(getDeterminant(a) == 0)
    {
        throw runtime_error("Determinant is 0");
    } 
    double d = getDeterminant(a);
    vector<vector<double>> ans(a.size(), vector<double> (a.size()));
    for(int i = 0; i < a.size(); i++) 
	{
        for(int j = 0; j < a.size(); j++) 
		{
            ans[i][j] = a[i][j]; 
        }
    }

    ans = getTranspose(getCofactor(ans));

    for(int i = 0; i < a.size(); i++) 
    {
        for(int j = 0; j < a.size(); j++) 
        {
            ans[i][j] /= d;
        }
    }
    return ans;
}



void printMatrix(vector<vector<double>> a)
{
    for(int i = 0; i < a.size(); i++) 
    {
        for(int j = 0; j < a[0].size(); j++) 
        {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}



vector<vector<double>> matrix_mult(vector<vector<double>>a,vector<vector<double>>b)
{
	int r1 = a.size(),c1 = a[0].size();
	int r2 = b.size(),c2 = b[0].size();
	vector<vector<double>>ans(r1,vector<double>(c2,0.0));
	for(int i = 0; i < r1; i++)
	{
		for(int j = 0; j < c2; j++)
		{
			for(int k = 0; k < c1; k++)
			{
				ans[i][j] +=  (a[i][k] * b[k][j]) ;
			}
		}
	}
	return ans;
}

vector<vector<double>> fit(vector<vector<double>>phi,vector<double>y)
{
	int m = phi.size(),n = phi[0].size();
	vector<vector<double>> phi_T = getTranspose(phi);
	vector<vector<double>> q = matrix_mult(phi_T,phi);
	vector<vector<double>> q_inv = getInverse(q);
	vector<vector<double>> s = matrix_mult(q_inv,phi_T);
	vector<vector<double>> y_T(y.size());
// Constructing y_T as vector<vector<double>> in order to use in matrix_mult(matrix multiplication)
	for(int i=0;i<y.size();i++)
	{
		vector<double> v(1, y[i]);
		y_T[i] = (v);
	}
	return matrix_mult(s, y_T);
}



