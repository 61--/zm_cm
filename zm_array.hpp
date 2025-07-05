#pragma once

#include <vector>
#include <deque>
#include <numeric>

#include "zm_log.hpp"


namespace zm
{



	template<typename _T0, typename _T1>
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();

	}

	template<typename _T0, typename _T1, typename _T2>
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1
		, const std::vector<_T2>& v2)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();
		FT_IF(v0.size() != v2.size()) << "size not match: pars0: " << v0.size() << " -  pars2: " << v2.size();
	}

	template<typename _T0, typename _T1, typename _T2, typename _T3>
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1
		, const std::vector<_T2>& v2
		, const std::vector<_T3>& v3)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();
		FT_IF(v0.size() != v2.size()) << "size not match: pars0: " << v0.size() << " -  pars2: " << v2.size();
		FT_IF(v0.size() != v3.size()) << "size not match: pars0: " << v0.size() << " -  pars3: " << v3.size();
	}

	template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4>
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1
		, const std::vector<_T2>& v2
		, const std::vector<_T3>& v3
		, const std::vector<_T4>& v4)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();
		FT_IF(v0.size() != v2.size()) << "size not match: pars0: " << v0.size() << " -  pars2: " << v2.size();
		FT_IF(v0.size() != v3.size()) << "size not match: pars0: " << v0.size() << " -  pars3: " << v3.size();
		FT_IF(v0.size() != v4.size()) << "size not match: pars0: " << v0.size() << " -  pars4: " << v4.size();
	}

	template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5>
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1
		, const std::vector<_T2>& v2
		, const std::vector<_T3>& v3
		, const std::vector<_T4>& v4
		, const std::vector<_T5>& v5)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();
		FT_IF(v0.size() != v2.size()) << "size not match: pars0: " << v0.size() << " -  pars2: " << v2.size();
		FT_IF(v0.size() != v3.size()) << "size not match: pars0: " << v0.size() << " -  pars3: " << v3.size();
		FT_IF(v0.size() != v4.size()) << "size not match: pars0: " << v0.size() << " -  pars4: " << v4.size();
		FT_IF(v0.size() != v5.size()) << "size not match: pars0: " << v0.size() << " -  pars5: " << v5.size();
	}

	template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6 >
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1
		, const std::vector<_T2>& v2
		, const std::vector<_T3>& v3
		, const std::vector<_T4>& v4
		, const std::vector<_T5>& v5
		, const std::vector<_T6>& v6)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();
		FT_IF(v0.size() != v2.size()) << "size not match: pars0: " << v0.size() << " -  pars2: " << v2.size();
		FT_IF(v0.size() != v3.size()) << "size not match: pars0: " << v0.size() << " -  pars3: " << v3.size();
		FT_IF(v0.size() != v4.size()) << "size not match: pars0: " << v0.size() << " -  pars4: " << v4.size();
		FT_IF(v0.size() != v5.size()) << "size not match: pars0: " << v0.size() << " -  pars5: " << v5.size();
		FT_IF(v0.size() != v6.size()) << "size not match: pars0: " << v0.size() << " -  pars6: " << v6.size();
	}

	template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7 >
	inline void EnsureSameSize(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1
		, const std::vector<_T2>& v2
		, const std::vector<_T3>& v3
		, const std::vector<_T4>& v4
		, const std::vector<_T5>& v5
		, const std::vector<_T6>& v6
		, const std::vector<_T7>& v7)
	{
		FT_IF(v0.size() != v1.size()) << "size not match: pars0: " << v0.size() << " -  pars1: " << v1.size();
		FT_IF(v0.size() != v2.size()) << "size not match: pars0: " << v0.size() << " -  pars2: " << v2.size();
		FT_IF(v0.size() != v3.size()) << "size not match: pars0: " << v0.size() << " -  pars3: " << v3.size();
		FT_IF(v0.size() != v4.size()) << "size not match: pars0: " << v0.size() << " -  pars4: " << v4.size();
		FT_IF(v0.size() != v5.size()) << "size not match: pars0: " << v0.size() << " -  pars5: " << v5.size();
		FT_IF(v0.size() != v6.size()) << "size not match: pars0: " << v0.size() << " -  pars6: " << v6.size();
		FT_IF(v0.size() != v7.size()) << "size not match: pars0: " << v0.size() << " -  pars7: " << v7.size();
	}


	
	inline bool CheckAllFalse(const std::vector<bool>& masks)
	{
		for (auto mask : masks)
		{
			if (mask)
				return false;
		}
		return true;
	}


	template<typename _T0, typename _T1>
	inline double _l2(const std::vector<_T0>& v0
		, const std::vector<_T1>& v1)
	{
		FT_IF(v0.size() != v1.size());

		double v_all = 0;
		for (int i = 0; i < v0.size(); i++)
		{
			double v = v0[i] - v1[i];
			v_all += v * v;
		}
		return v_all;
	}

	template<typename _T>
	int getMaxIdx(const std::vector<_T>& ay)
	{
		if (ay.size() <= 1)
			return 0;

		int max_i = 0;
		_T max_v = ay[0];

		for (int i = 1; i < ay.size(); i++)
		{
			if (max_v < ay[i]) {
				max_v = ay[i];
				max_i = i;
			}
		}
		return max_i;
	}



	template<typename _T>
	inline void _Insert(
		std::vector<_T>& v1
		, const std::vector<_T>& v2)
	{
		v1.insert(v1.end(), v2.begin(), v2.end());
	}

	template<typename _T1, typename _T2>
	inline void _Insert(
		std::vector<_T1>& v1
		, _T2 v2)
	{
		v1.push_back(v2);
	}

	template<typename _T>
	inline void _FillZero(std::vector<_T>& ay) {
		for (int i = 0; i < ay.size(); i++) {
			ay[i] = 0;
		}
	}


	template<typename _T>
	inline std::vector<_T> _Combine(
		const std::vector<_T>& v1
		, const std::vector<_T>& v2)
	{
		std::vector<_T> ret = v1;
		ret.insert(ret.end(), v2.begin(), v2.end());
		return ret;
	}

	template<typename _T>
	inline std::vector<_T> _Combine(
		const std::vector<_T>& v1
		, const std::vector<_T>& v2
		, const std::vector<_T>& v3)
	{
		std::vector<_T> ret = v1;
		ret.insert(ret.end(), v2.begin(), v2.end());
		ret.insert(ret.end(), v3.begin(), v3.end());
		return ret;
	}


	template<typename _T>
	inline std::vector<_T> _Combine(
		const std::vector<std::vector<_T>>& vs_ay)
	{
		if (vs_ay.empty())
			return std::vector<_T>();

		std::vector<_T> ret = vs_ay[0];
		for (int i = 1; i < vs_ay.size(); i++) {
			ret.insert(ret.end(), vs_ay[i].begin(), vs_ay[i].end());
		}
		return ret;
	}


	template<typename _T>
	inline std::vector<_T> Duplicate(
		const std::vector<_T>& v1
		, int n)
	{
		std::vector<_T> all;
		for (int i = 0; i < n; i++) {
			all = _Combine(all, v1);
		}
		return all;
	}



	template<class _T>
	inline double _mean(const std::vector<_T>& v) {
		if (v.size() == 0)
			return 0;

		_T sum = std::accumulate(v.begin(), v.end(), _T(0.0));
		double mean_v = double(sum) / v.size();
		return mean_v;
	}

	template<class _T>
	inline _T _sum(const std::vector<_T>& v) {
		if (v.size() == 0)
			return 0;

		_T sum = std::accumulate(v.begin(), v.end(), _T(0));
		return sum;
	}
		
	inline float mean(const std::vector<float>& v)
	{
		return (float)_mean(v);
	}

	inline double mean(const std::vector<double>& v) {
		return _mean(v);
	}

	template<typename _T>
	inline int _MinIdx(const std::vector<_T>& vec) {
		auto it = std::min_element(std::begin(vec), std::end(vec));
		return  std::distance(std::begin(vec), it);
	}

	template<typename _T>
	inline int _MaxIdx(const std::vector<_T>& vec) {
		auto it = std::max_element(std::begin(vec), std::end(vec));
		return  std::distance(std::begin(vec), it);
	}


	template<typename _T>
	inline _T _pop_front(std::vector<_T>& vec) {
		_T data = vec.front();
		vec.erase(vec.begin());
		return data;
	}


	template<typename _T>
	inline _T _pop_front(std::deque<_T>& vec) {
		_T data = vec.front();
		vec.pop_front();
		return data;
	}


	template<typename _T>
	inline _T _pop_back(std::vector<_T>& vec) {
		_T data = vec.back();
		vec.pop_back();
		return data;
	}


	template<typename _T>
	inline _T _pop_back(std::deque<_T>& vec) {
		_T data = vec.back();
		vec.pop_back();
		return data;
	}

	template<typename _T>
	inline _T _Pop_At(std::vector<_T>& ay, int idx) {
		_T t = ay[idx];
		ay.erase(ay.begin() + idx);
		return t;
	}


	template<typename _T>
	inline std::vector<double> _to_double(const std::vector<_T>& ns) {
		std::vector<double> ds(ns.size());
		for (int i = 0; i < ns.size(); i++)
			ds[i] = ns[i];
		return ds;
	}
}

