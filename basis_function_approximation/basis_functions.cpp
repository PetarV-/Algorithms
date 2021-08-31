#include<bits/stdc++.h>
#include "basis_functions.h"
using namespace std;
#define PI 3.14159265
vector<double> polynomial_basis(double x,int n) 
{
/*
	Computes the polynomial basis function and returns a vector comprised of monomials upto degree (n-1)
	    Φ(x) = [x^(n-1),x^(n-2),...,x,1]
	
	Args:
		x - 1-dimensional data point(Scalar)
		n - degree of polynomial - (Scalar)
		
	Returns:
		Polynomial Basis function - (n) dimensional vector  
*/
	vector<double> basis(n, 0);
	double q = 1;
	for(int i = 0; i < n; i++)
	{
		basis[n - 1 - i] = q;
		q *= (x);
	}
	return basis;
}
vector<double> rbf_basis(double x,vector<double>&myu, double sigma)
{
/*
	Compute the RBF basis function 
        Φ(x) = [exp(-||x-μ_1||^2/(2*σ^2)),exp(-||x-μ_2||^2/(2*σ^2)),..,exp(-||x-μ_n||^2/(2*σ^2))]
		
	Args:
		x - 1-dimensional data point
		myu - a list of n different myus (n-dimensional vector)
		sigma - the sigma parameter of gaussian function (scalar)
		
	Returns:
		RBF Basis function - (n) dimensional vector  
*/
	if(sigma==0)
		{
			throw runtime_error("sigma can't be zero");
		}
	int n = myu.size();
	double dif,factor=((-2)*sigma*sigma);
	vector<double> basis(n);
	for(int i = 0; i < n; i++)
	{
		dif = (x - myu[i]);
		basis[i] = exp((dif * dif)/factor);
	}
	return basis;
}

double sigmoid(double x)
{
	//Returns the value of the sigmoid function on x.
	return  1/(1+exp(-x));
}
vector<double> sigmoid_basis(double x,vector<double>&myu, double sigma) 
{
/*
	Computes the sigmoid basis function
	    Φ(x) = [sigmoid((x-μ_1)/σ),sigmoid((x-μ_2)/σ),...sigmoid((x-μ_n)/σ)]
	
	Args:
		x - 1-dimensional data point
		myu - a list of n different myus (n-dimensional vector)
		sigma - the sigma parameter of sigmoid function (scalar) 
	Returns:
		Sigmoid Basis function - (n) dimensional vector  
*/
	if(sigma==0)
	{
		throw runtime_error("sigma can't be zero");
	}
	int n = myu.size();
	vector<double> basis(n);
	for(int i = 0; i < n; i++)
	{
		basis[i] = sigmoid((x - myu[i])/ sigma);
	}
	return basis;
}

vector <double> fourier_basis(double x, int n)
{
/*
	Computes the fourier basis function and returns a vector comprised of sins and coses
	    Φ(x) = [1,sin(2*π*x),cos(2*π*x),sin(4*π*x),cos(4*π*x),...,sin(2*π*n*x),cos(2*π*n*x)]
	
	Args:
		x - 1-dimensional data point(Scalar)
		n - degree - (Scalar)
		
	Returns:
		Fourier Basis function - (2n+1) dimensional vector  
*/
	vector <double> basis;
	basis.reserve(2*n+1);
	basis.push_back(1.0);
	for(int i = 1; i <= n; i++)
	{
		basis.push_back(sin(2*PI*i*x));
		basis.push_back(cos(2*PI*i*x));
	}
	return basis;
}
