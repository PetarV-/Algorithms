## This includes implementation of approximation of polynomial and trigonometric functions using basis functions in C++.

Both are interactive programs where user can specify the corresponding functions or use default polynomial/trigonometric functions for the analysis.


[poly_function_fit](https://github.com/Poojan-ml/Algorithms/blob/Poojan-ml-patch-1/basis_function_approximation/poly_function_fit.cpp) approximates a user given polynomial by using polynomial basis function.

**How do this work?**

In the implementation , a choice is being given to user to give any polynomial as input and we generate **200** random data points(**_x_**) and evaluate the
value of user specified polynomial on those points(**_y_**). And using the polynomial basis function, coefficients of the polynomial are computed using the least square regression on polynomial basis function φ. 


**How to compile this?** 

`g++ poly_function_fit.cpp  basis_functions.cpp matrix_functions.cpp`


[trig_function_fit](https://github.com/Poojan-ml/Algorithms/blob/Poojan-ml-patch-1/basis_function_approximation/trig_function_fit.cpp) approximates a user given trigonometric using fourier basis function.

**How do this work?**

In the implementation , a choice is being given to user to give Trigonometric function as input and we generate **500** random data points(**_x_**) and evaluate the
value of user specified Trigonometric function on those points(**_y_**). And using the fourier basis function, coefficients of the trigonometric terms are computed using the least square regression on Fourier basis function φ. 

**How to compile this?** 

`g++ trig_function_fit.cpp  basis_functions.cpp matrix_functions.cpp`

Both of these work very well and almost(slight difference due to the noise) approximates the real target function with **_least_** mean square error. 

Here are the snaps of sample examples for both.

![](https://github.com/Poojan-ml/Algorithms/blob/Poojan-ml-patch-1/basis_function_approximation/poly_snap.PNG?raw=true)

![](https://github.com/Poojan-ml/Algorithms/blob/Poojan-ml-patch-1/basis_function_approximation/trigo_snap.PNG?raw=true)



