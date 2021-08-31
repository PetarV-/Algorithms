std::vector<double> polynomial_basis(double x,int n);
std::vector<double> rbf_basis(double x,std::vector<double>&myu, double sigma);
double sigmoid(double x);
std::vector<double> sigmoid_basis(double x,std::vector<double>&myu, double sigma);
std::vector <double> fourier_basis(double x, int n);
double mother_wavelet(double x);
std::vector <double> wavelet_basis(double x, int m_low, int m_high, int j_low, int j_high);
double spline_aux(double x, double k);
std::vector <double> spline_basis(double x, int n);

