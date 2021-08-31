#include<bits/stdc++.h>
#include "matrix_functions.h"
#include "basis_functions.h"

using namespace std;

double default_poly_fn(double x)
{
/*
	Computes the value of defalut polynomial at point x which is 
		y = 1 + (2)*(x) - (3)*(x*x) + (4)*(x*x*x)
	Args:
		v : The n dimensional coefficient vector
		d : 1 dimensional point (Scalar)
	
	Returns:
		y : Value of polynomial at point x (Scalar)
*/	
	return 1 + (2)*(x) - (3)*(x*x) + (4)*(x*x*x);
}
double user_specified_poly_fn(vector<double>v,double x)
{

/*
	Computes the value of user specified polynomial at point x
		y = v[0]+v[1]*x+v[2]*(x^2)+...+v[n-1]*(x^(n-1))
	Args:
		v : The n dimensional coefficient vector
		x : 1 dimensional point (Scalar)
	
	Returns:
		y : Value of polynomial at point x (Scalar)

*/	
	double q = 1.0, y = 0.0;
	int n = v.size();
	for(int i = 0; i < n; i++)
	{
		y += (v[i]*q);
		q *= x;
	}
	return y;
}

double mean_square_error(vector<double> y , vector<vector<double>> y_pred)
{
/*
	Computes the mean square error between the estimated values and the actual values
	Args:
		y : Actual values n(number of points) dimensional vector 
		y_pred : Estimated values (n(number of points),1) dimensional vector
	Returns:
		y : Value of mean square error between the y and y_pred (Scalar)
*/
	double mse = 0.0;
	int n = y.size();
	for(int i = 0;i < n; i++)
	{
		double dif = y[i] - y_pred[i][0];
		mse += (dif*dif);
	}
	return mse/n;
}

void print_approximation (vector<vector<double>>ans)
{
	int power = ans.size() - 1;
	cout<<ans[power][0]<<" + ";
	for(int i=power-1;i>0;i--)
	{
	    cout<<"("<<ans[i][0]<<")"<<"x^"<<power-i<<" + ";  
	}
	cout<<"("<<ans[0][0]<<")"<<"x^"<<power;
	return ;
}


void analysis()
{
    default_random_engine generator;
  	normal_distribution<double> distribution(2,1.5);// Normal Distribution
	cout << setprecision(3) << fixed;
	int datapoints = 200; // Number of datapoints being generated
    int power = 3;
	vector<vector<double>>phi(datapoints);
    vector<double>y(datapoints);
	vector<double>x(datapoints);
	cout<<"Would you like provide the target polynomial? Press 1 to enter your choice of polynomial or press 0 to go with the default polynomial"<<"\n";
	int in;
	cin>>in;
	if(in != 0)
	{
	cout<<"Enter the degree of polynomial(Upto 10 in order to avoid the numerical overflow/underflow)"<<"\n";
	cin >> power;
	cout<<"Please enter "<< power+1 <<" coefficients starting from the constant term upto the cofficiant of x^"<< power <<" in space seaprated manner"<<"\n";
	vector<double> v(power+1);
	for(int i = 0 ; i < power+1 ; i++)
	{
		cin >> v[i];
	}
	for(int i = 0; i < datapoints; i++)
	{
		double d = (rand()%1001-500)/(50.0);// d is random number(double) between -10 to 10
		vector<double> q = polynomial_basis(d,power+1);
		phi[i] = q;
		y[i] = user_specified_poly_fn(v,d);
		double number = distribution(generator);
		y[i]+=(2*number); // Adding Gausian Noise
	}	
	}
	else
	{
	for(int i = 0; i < datapoints; i++)
	{
		double d = (rand()%1001-500)/(50.0);// d is random number(double) between -10 to 10
		vector<double> v = polynomial_basis(d,4);
		phi[i] = v;
		y[i] = default_poly_fn(d);
		double number = distribution(generator);
		y[i]+=(2*number);// Adding Gausian Noise
	}
	}
	vector<vector<double>> ans = fit(phi,y);
	cout<<"The best fit for the given data points is "<<"\n";
	print_approximation(ans);
	cout<<"\n";
	vector<vector<double>> predicted_y = matrix_mult(phi,ans);
	double mse = mean_square_error(y,predicted_y);
	cout<<"The mean square error with the best fit is equal to : "<<mse<<"\n";	
    return ;
}
int main()
{
	analysis();
	return 0;
}