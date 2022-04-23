#pragma once
#include <iostream>

namespace ssh::math
{
		// MY_DEBUG определена
		//#define MY_DEBUG 

		template<typename T, int N, int M>
		struct MasWrapper
		{
			T mas[N][M];
		};

		template<typename T, int N, int M>
		class Matrix
		{
		public:
			// Конструктор
			Matrix()
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = 0;
			}

			// Конструктор
			Matrix(const T mas[N][M])
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mas[i][j];
			}

			// Конструктор
			Matrix(const MasWrapper<T, N, M>& mas)
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mas.mas[i][j];
			}

			// Конструктор копирования
			Matrix(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "Copy constructor" << std::endl;
	#endif

				m_n = mat.m_n;
				m_m = mat.m_m;

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.m_mat[i][j];
			}

			int getN() const { return m_n; }
			int getM() const { return m_m; }
			T get(int i, int j) const { return m_mat[i][j]; }
			void set(int i, int j, T data) { m_mat[i][j] = data; }

			// Присваивание
			template<typename T, int N, int M>
			Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "Operator =" << std::endl;
	#endif

				m_n = mat.getN();
				m_m = mat.getM();

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.get(i, j);

				return *this;
			}

			// Оператор сложения
			template<typename T, int N, int M>
			Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "operator+" << std::endl;
	#endif
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
				return tmp;
			}

			// Оператор умножения
			template<typename T, int K>
			Matrix<T, N, K> operator*(const Matrix<T, M, K>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "operator*" << std::endl;
	#endif
				Matrix<T, N, K> tmp;

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < mat.getM(); j++)
					{
						T sum = 0;
						for (int k = 0; k < m_m; k++)
							sum += m_mat[i][k] * mat.get(k, j);
						tmp.set(i, j, sum);
					}
				return tmp;
			}

			// Расчет определителя
			T det()
			{
				T det = 0;
				std::cout << "det counting" << std::endl;
				if (m_m != m_n) throw std::exception("determinant doesn't exist");
				if (m_m == 1)
					det = m_mat[0][0];
				else if (m_m == 2)
					det = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
				else if (m_m == 3)
					det = m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1]) - m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0]) + m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0]);
				else if (m_m > 3)
					throw std::exception("too many digits:(");
				return det;
			}

			// Обратная матрица
			Matrix<T, N, M> inv()
			{
				Matrix<T, N, M> tmp;

				T d = det();

				if (det() == 0)
					throw std::exception("zero determinant");

				for (int i = 0; i < m_n; ++i)
					for (int j = 0; j < m_m; ++j)
						tmp.m_mat[i][j] = m_mat[i][j] / d;
				return tmp;
			}

			//Транспонирование
			Matrix<T, M, N> transpose() {
				Matrix<T, M, N> tmp;
				for (int i = 0; i < m_n; ++i)
					for (int j = 0; j < m_m; ++j)
						tmp.set(j, i, m_mat[i][j]);
				cout << "transposing done" << endl;
				return tmp;
			}

			// Деструктор
			~Matrix()
			{
	#ifdef MY_DEBUG
				std::cout << "Destructor" << std::endl;
	#endif
			}

			template<typename T, int N, int M>
			friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);

			template<typename T, int N, int M>
			friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

		private:
			int m_n, m_m;
			T m_mat[N][M];
		};

		// Перегрузка оператора ввода
		template<typename T, int N, int M>
		std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
		{
			for (int i = 0; i < mat.m_n; i++)
				for (int j = 0; j < mat.m_m; j++)
					in >> mat.m_mat[i][j];
			return in;
		}

		// Перегрузка оператора вывода
		template<typename T, int N, int M>
		std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
		{
			out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
			for (int i = 0; i < mat.m_n; i++) {
				for (int j = 0; j < mat.m_m; j++)
					out << mat.m_mat[i][j] << " ";
				out << std::endl;
			}
			return out;
		}

		using Vec2i = Matrix<int, 2, 1>;	// Сокращенное удобное название
		using Vec2d = Matrix<double, 2, 1>;
		using Mat23i = Matrix<int, 2, 3>;
		using Mat22d = Matrix<double, 2, 2>;
}