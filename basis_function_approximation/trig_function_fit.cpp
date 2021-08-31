#include<bits/stdc++.h>
#include "matrix_functions.h"
#include "basis_functions.h"
#include <random>

#define PI 3.14159265
using namespace std;

double default_trig_fn(double x)
{
/*
	Computes the value of defalut trigonometric function at point d which is 
		y = (1.1 * sin(4*PI*x)) - (2.2 * cos(4*PI*x)) - (3.3 * sin(2*PI*x))+(4.4 * cos(2*PI*x)) - 5.5
	Args:
		x : 1 dimensional point (Scalar)
	Returns:
		y : Value of default trigonometric function at point d (Scalar)
*/	
	return (1.1 * sin(4*PI*x)) - (2.2 * cos(4*PI*x)) - (3.3 * sin(2*PI*x))+(4.4 * cos(2*PI*x)) - 5.5;
}
double user_specified_trig_fn(vector<double>v,double x)
{
/*
	Computes the value of user specified trigonometric function at point x which is 
		y = v[0]*sin(2*PI*x)+v[1]*sin(4*PI*x)+...v[n-1]*sin(2*n*PI*x)+(v[n]*cos(2*PI*x)+v[n+1]*cos(4*PI*x)+...v[2*n-1]*cos(2*n*PI*x))+v[2*x]
	Args:
		v : ( k = 2*n+1) dimensional coefficient vector
		x : 1 dimensional point (Scalar)
	
	Returns:
		y : Value of user specified trigonometric function at point x (Scalar)
*/	
	double y = 0.0;
	int k = v.size();
	for(int i = 0; i < k/2; i++)
	{
	    y += (v[i] * sin(2*(i+1)*PI*x));
	}
	for(int i = k/2; i < k - 1; i++)
	{
	    y += (v[i] * cos(2*(i+1-(k/2))*PI*x));
	}
	y += (v[k-1]);
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
	int l = ans.size();
	for(int i = 1; i < l; i+=2)
	{
	    cout<< "(" <<ans[i][0]<< ")" << "sin("<<(i+1) << "*PI*x) + ";
	}
	for(int i = 2; i < l; i+=2)
	{
	    cout<< "(" << ans[i][0] << ")" << "cos("<<i<<"*PI*x) + " ;
	}
	cout<< "(" << ans[0][0] << ")"<<"\n";
	return ;
}

void analysis()
{
    default_random_engine generator;
  	normal_distribution<double> distribution(1.0,0.0);// Standard normal distribution
	int datapoints = 500; // Number of datapoints being generated
    cout << setprecision(3) << fixed;
	vector<vector<double>> phi(datapoints);
    vector<double> y(datapoints);
    int n = 2;
	cout<<"Would you like to provide the target trignometric function? Press 1 to enter your choice of trignometric function or press 0 to go with the default trignometric function"<<"\n";
	int in;
	cin>>in;
	if(in!=0)
	{
	    cout<<"Please Provide the number n till which you would like to go for sin(2*PI*n*x)/cos(2*PI*n*x)"<<"\n";
	    cin >> n;
		cout<<"First Provide the "<< n <<" number of cofficients starting from sin(2*PI*x) upto sin("<<2*n<<"*PI*x)"<<"\n";
		cout<<"Then Provide another "<< n <<" number of cofficients starting from cos(2*PI*x) upto cos("<<2*n<<"*PI*x)"<<"\n";
		cout<<"And finally the constant term. All in space seaprated manner"<<"\n";
	    vector<double> v(2*n+1);
	    for(int i = 0; i < 2*n+1; i++)
	    {
	        cin >> v[i];
	    }
	    for(int i = 0; i < datapoints; i++)
	    {
		double d = (rand()%1001-500)/10.0;// d is random number(double) between -50 to 50
		vector<double>q = fourier_basis(d,n);
		phi[i] = q;
		y[i] = user_specified_trig_fn(v,d);
		double number = distribution(generator);
		y[i] +=((0.3) * number); // Adding Gausian Noise
	    }
	}
	else
	{
	for(int i = 0; i < datapoints; i++)
	{
		double d = (rand()%1001-500)/(10.0);// d is random number(double) between -50 to 50
		vector<double>v = fourier_basis(d,n);
		phi[i] = v;
		y[i] = default_trig_fn(d);
		double number = distribution(generator);
		y[i]+=(0.3*number);// Adding Gausian Noise
	}
	}
	vector<vector<double>> ans = fit(phi,y);
	cout<<"The best fit for the given data points is : "<<"\n";
	print_approximation(ans);
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