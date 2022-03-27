#include "timer.hpp"
#include <chrono>

namespace ssh
{

	void Timer::reset()
	{
		m_beg = clock_t::now();
	}
}