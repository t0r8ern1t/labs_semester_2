#include <iostream>
#include <cassert>
#include "inc/matrix.hpp"

using namespace std;
using namespace ssh;

using ssh::math::Mat22d;
using ssh::math::Vec2d;
using ssh::math::Mat23i;


int main()
{
	cout << "=== Test 1 ===" << endl;
	{
		Mat22d A({ {
			 {1,2},
			 {3,4}
		} });

		cout << A.transpose() << endl;
		try
		{
			cout << A.det() << endl;
			cout << A.inv() << endl;
		}
		catch (const std::bad_alloc& e)
		{
			cerr << "BAD ALLOC!!!! " << e.what() << endl;
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
		}

	}

	cout << "=== Test 2 ===" << endl;

		Mat23i A({ {{1, 2, 3}, {3, 4, 7}} });

		cout << A.transpose() << endl;
		try
		{
			cout << A.det() << endl;
			cout << "det done" << endl;
			cout << A.inv() << endl;
			cout << "After inv in main" << endl;
		}
		catch (const std::bad_alloc& e)
		{
			cerr << "BAD ALLOC!!!! " << e.what() << endl;
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
		}

	cout << "Done!" << endl;

	cout << "test 3" << endl;
	ssh::math::Matrix<double, 3, 2> M({ { { 1, 2 }, { 2, 3 }, {0, 1} } });
	auto C = M*A;
	std::cout << C << std::endl;

	return 0;
}