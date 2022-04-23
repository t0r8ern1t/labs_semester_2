#include <iostream>

class Matrix
{
	
public:
	Matrix(int n, int m)
	{
		m_n = n;
		m_m = m;
		m_mat = new double* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new double[m_m];
	}

	Matrix(const Matrix& mat)
	{
		m_n = mat.m_n;
		m_m = mat.m_m;

		m_mat = new double* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new double[m_m];

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];
	}

	Matrix& operator=(const Matrix& mat)
	{

		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];

		return *this;
	}

	Matrix operator+(const Matrix& mat) {
		std::cout << "operator+" << std::endl;
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	Matrix operator-(const Matrix& mat) {
		std::cout << "operator-" << std::endl;
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}

	Matrix operator+=(const Matrix& mat) {
		std::cout << "operator+=" << std::endl;
		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	Matrix operator*(const Matrix& mat) {
		std::cout << "operator*" << std::endl;
		Matrix tmp(m_n, mat.m_m);
		for (int i = 0; i < mat.m_m; i++)
			for (int j = 0; j < m_n; j++){
				tmp.m_mat[i][j] = 0;
				for (int k = 0; k < m_m; k++)
					tmp.m_mat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
			}
		return tmp;
	}

	double Deter() {
		int det = 0;
		std::cout << "det counting" << std::endl;
		if (m_m != m_n) return 0.5;
		if (m_m == 1)
			det = m_mat[0][0];
		else if (m_m == 2)
			det = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
		else if (m_m == 3)
			det = m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1]) - m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0]) + m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0]);
		else if (m_m > 3)
			return 0.5;
		return det;
	}

	Matrix Reverse() {
		std::cout << "reverse matrix counting" << std::endl;
		Matrix tmp(m_n, m_m);
		double det = Deter();
		for (int i = 0; i < m_n; ++i)
			for (int j = 0; j < m_m; ++j)
				tmp.m_mat[i][j] = m_mat[i][j] / det;
		return tmp;
	}

	Matrix Transpose() {
		Matrix tmp(m_m, m_n);
		for (int i = 0; i < m_n; ++i)
			for (int j = 0; j < m_m; ++j)
				tmp.m_mat[j][i] = m_mat[i][j];
		return tmp;
	}

	~Matrix()
	{
		for (int i = 0; i < m_n; i++)
			delete[] m_mat[i];
		delete m_mat;
	}

	friend std::istream& operator>>(std::istream& os, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

private:
	int m_n, m_m;
	int n;
	double** m_mat;
};

std::istream& operator>>(std::istream& in, Matrix& mat)
{
	for (int i = 0; i < mat.m_n; i++)
		for (int j = 0; j < mat.m_m; j++)
			in >> mat.m_mat[i][j];
	return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
	for (int i = 0; i < mat.m_n; i++) {
		for (int j = 0; j < mat.m_m; j++)
			out << mat.m_mat[i][j] << " ";
		out << std::endl;
	}
	return out;
}

int main()
{
	double eps = 0.01;
	int m = 2, n = 2;
	Matrix A(n, m);

	std::cin >> A;
	std::cout << A << std::endl;

	Matrix B(n, m);
	std::cin >> B;
	std::cout << B << std::endl;

	Matrix C(n, m);
	C = A - B;

	std::cout << C << std::endl;

	C = A * B;
	std::cout << C << std::endl;
	double det = C.Deter();
	if (abs(det - 0.5) > eps)
		std::cout << C.Deter() << std::endl;
	else std::cout << "deter() unavaliable" << std::endl;

	Matrix x(3, 3);
	std::cin >> x;
	std::cout << x << std::endl;
	det = x.Deter();
	if (abs(det - 0.5) < eps) std::cout << "deter() unavaliable" << std::endl;
	else
		std::cout << det << std::endl;

	if ((abs(det - 0) > eps) && (abs(det - 0.5) > eps))
		std::cout << x.Reverse() << std::endl;
	else std::cout << "imposiible to find reverse matrix" << std::endl;

	Matrix y(2, 5);
	std::cin >> y;
	std::cout << y.Transpose() << std::endl;

	return 0;
}
