#pragma once
#include <string>
#include <boost/lexical_cast.hpp>
#include "zm_log.hpp"


namespace zm
{
	template<typename _T>
	inline std::string _str(_T v)
	{
		return boost::lexical_cast<std::string>(v);
	}


	template<typename _T>
	void clamp(_T& v, _T min_v, _T max_v)
	{
		FT_IF(max_v < min_v);
		if (v < min_v)
			v = min_v;
		if (v > max_v)
			v = max_v;
	}

	template<typename _T>
	void clamp_min(_T& v, _T min_v)
	{
		if (v < min_v)
			v = min_v;
	}

	template<typename _T>
	void clamp_max(_T& v, _T max_v)
	{
		if (v > max_v)
			v = max_v;
	}
}