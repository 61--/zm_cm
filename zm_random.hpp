/*	
 * File: Random.h
 * Project: DUtils library
 * Author: Dorian Galvez-Lopez
 * Date: April 2010, November 2011
 * Description: manages pseudo-random numbers
 * License: see the LICENSE.txt file
 *
 */

#pragma once


#include <cstdlib>
#include <vector>
#include <math.h>
#include <set>
//#include <boost/random.hpp>
#include <ctime>
#include <random>
#include <boost/unordered_set.hpp>
#include <numeric>

#include "zm_log.hpp"
#include "zm_array.hpp"








namespace zm {

	class RdCore_C
	{
	public:
		template<typename _T>
		static inline _T uniform_real(_T lowerBndr, _T upperBndr) {
			return lowerBndr + ((_T)std::rand() / (RAND_MAX + _T(1))) * (upperBndr - lowerBndr);
		}

		static inline int uniform_int(int lowerBndr, int upperBndr)
		{
			return c_uniform_int_ee(lowerBndr, upperBndr - 1);
		}

	private:
		static inline int c_uniform_int_ee(int lowerBndr, int upperBndr)
		{
			return lowerBndr + std::rand() % (upperBndr - lowerBndr + 1);
		}
	};



	inline int uniform_int(int lowerBndr, int upperBndr) {
		return RdCore_C::uniform_int(lowerBndr, upperBndr);
	}


	template<typename _T>
	inline _T uniform_real(_T lowerBndr, _T upperBndr) {
		return RdCore_C::uniform_real<_T>(lowerBndr, upperBndr);
	}



	//======================================================================


	//===============================================================================
	//===============================================================================
	//¸ÅÂÊ²ÉÑù
	inline int randomByPb(const std::vector<double>& pbs)
	{
		FT_IF(pbs.empty());

		double sum = zm::_sum(pbs);
		FT_IF(sum <= 0);

		double rd_v = zm::uniform_real<double>(0, 1);


		double v = 0;
		for (int i = 0; i < pbs.size(); i++)
		{
			v += pbs[i] / sum;
			if (rd_v <= v)
				return i;

		}
		return pbs.size() - 1;
	}

	inline int randomByPb(const std::vector<int>& pbs) {
		return randomByPb(_to_double(pbs));
	}


	inline int uniform_int_ee(int lowerBndr, int upperBndr) {
		return uniform_int(lowerBndr, upperBndr + 1);
	}


	template<typename _It>
	inline void random_shuffle(_It begin, _It end)
	{
		static std::default_random_engine eng(
			(unsigned)std::rand());
		std::shuffle(begin, end, eng);
	}

	template<class _T>
	inline void uniform_idx_set_val(std::vector<_T>& ay, _T v)
	{
		FT_IF(ay.empty());
		int idx = uniform_int(0, ay.size());
		ay[idx] = v;
	}
	template<class _T>
	inline _T uniform_idx_get_val(std::vector<_T>& ay)
	{
		FT_IF(ay.empty());
		int idx = uniform_int(0, ay.size());
		return ay[idx];
	}

	inline bool rate_random(double rate)
	{
		if (rate >= 1)
			return true;
		if (rate <= 0)
			return false;

		double v = uniform_real<double>(0, 1);
		if (v <= rate)
			return true;
		return false;
	}

	inline char random_char() {
		return (char)(uniform_int(0, 256));
	}

	inline bool random_bool()
	{
		return uniform_int(0, 1000000) % 2 == 0;
	}

	template<typename _T>
	inline void randomSwapVector(std::vector<_T>& ay){
		if(ay.size() <=1)
			return;
		int i = zm::uniform_int(0, ay.size());
		int j = zm::uniform_int(0, ay.size());
		if(i ==j )
			return;
		std::swap(ay[i], ay[j]);
	}
	
	template<typename _T>
	inline void randomRemoveOne(std::vector<_T>& ay)
	{
		if(ay.empty())
			return;
		int n = zm::uniform_int(0, ay.size());
		ay.erase(ay.begin() + n);
	}

	template<typename _T>
	inline _T randomPopVector(std::vector<_T>& ay)
	{
		if(ay.empty()){
			ER<<"vector is empty";
			throw 0;
		}
		
		int n = zm::uniform_int(0, ay.size());
		_T t = ay[n];
		ay.erase(ay.begin() + n);
		return t;
	}

	template<typename _T>
	inline _T randomTrivialOne(std::vector<_T>& ay)
	{
		if(ay.empty()){
			ER<<"vector is empty";
			throw 0;
		}
		
		int n = (int)zm::uniform_int(0, (int)(ay.size() ));
		_T t = ay[n];
		return t;
	}

	template<typename _T>
	inline _T randomTrivialOne(const std::vector<_T>& ay)
	{
		if (ay.empty()) {
			ER << "vector is empty";
			throw 0;
		}

		int n = (int)zm::uniform_int(0, (int)(ay.size()) );
		_T t = ay[n];
		return t;
	}
	



	inline std::vector<int> randomTrivialN_Idx(int sz, int n)
	{
		if (n <= 0)
			return std::vector<int>();

		if (sz < n) {
			LG_FT << "vector is empty";
		}
		if (sz < n * 5) {
			std::vector<int> idxs(sz);
			for (int i = 0; i < sz; i++) {
				idxs[i] = i;
			}
			zm::random_shuffle(idxs.begin(), idxs.end());

			idxs.resize(n);
			return idxs;
		}

		std::set<int> idxs;
		while (true) {
			int idx = zm::uniform_int(0, sz);
			idxs.insert(idx);
			if (idxs.size() >= n)
				break;
		}
		std::vector<int> v_idxs(idxs.begin(), idxs.end());
		v_idxs.resize(n);
		return v_idxs;
	}


	template<typename _T>
	inline std::vector<_T> randomTrivialN(const std::vector<_T>& ay, int n)
	{
		if (n <= 0)
			return std::vector<_T>();

		if (ay.size()<n) {
			LG_FT << "vector is empty";
		}
		if (ay.size() < n * 5) {
			std::vector<int> idxs(ay.size());
			for (int i = 0; i < ay.size(); i++) {
				idxs[i] = i;
			}
			zm::random_shuffle(idxs.begin(), idxs.end());

			std::vector<_T> subs(n);
			for (int i = 0; i < n; i++) {
				subs[i] = ay[idxs[i]];
			}
			return subs;
		}

		std::set<int> idxs;
		while (true) {
			int idx = zm::uniform_int(0, ay.size());
			idxs.insert(idx);
			if (idxs.size() >= n)
				break;
		}
		std::vector<int> v_idxs(idxs.begin(), idxs.end());
		std::vector<_T> subs(n);
		for (int i = 0; i < n; i++) {
			subs[i] = ay[v_idxs[i]];
		}
		return subs;
	}

	template<typename _T>
	inline std::vector<_T> randomTrivialN(const std::deque<_T>& ay, int n)
	{
		if (n <= 0)
			return std::vector<_T>();

		if (ay.size() < n) {
			LG_FT << "vector is empty";
		}
		if (ay.size() < n * 5) {
			std::vector<int> idxs(ay.size());
			for (int i = 0; i < ay.size(); i++) {
				idxs[i] = i;
			}
			zm::random_shuffle(idxs.begin(), idxs.end());

			std::vector<_T> subs(n);
			for (int i = 0; i < n; i++) {
				subs[i] = ay[idxs[i]];
			}
			return subs;
		}

		std::set<int> idxs;
		while (true) {
			int idx = zm::uniform_int(0, ay.size());
			idxs.insert(idx);
			if (idxs.size() >= n)
				break;
		}
		std::vector<int> v_idxs(idxs.begin(), idxs.end());
		std::vector<_T> subs(n);
		for (int i = 0; i < n; i++) {
			subs[i] = ay[v_idxs[i]];
		}
		return subs;
	}

	class SUIDIns
	{
	public:
		static SUIDIns& Ins() {
			static SUIDIns ins;
			return ins;
		}


		std::string gen(int n) {
			while (true) {
				std::string str = _gen(n);
				if(str_sets_.find(str) != str_sets_.end())
					continue;
				str_sets_.insert(str);
				return str;
			}

			return "";
		}

	private:
		SUIDIns() {
			for (int i = 0; i < 10; i++) {
				cs_.push_back('0' + i);
			}
			for (char i = 'A'; i <= 'Z'; i++) {
				cs_.push_back(i);
			}
		}

		std::string _gen(int n) {
			std::string str;
			for (int i = 0; i < n; i++) {
				char c = randomTrivialOne(cs_);
				str.push_back(c);
			}
			return str;
		}

	private:
		std::vector<char> cs_;
		boost::unordered_set<std::string> str_sets_;
	};


}//


//======================================================================
//==========================================================================


	/*
	template<typename _T>
	inline _T uniform_rand(_T lowerBndr, _T upperBndr){
		return lowerBndr + ((_T) std::rand() / (RAND_MAX + _T(1))) * (upperBndr - lowerBndr);
	}

	inline int uniform_rand_int(int lowerBndr, int upperBndr)
	{
		return lowerBndr + std::rand() %(upperBndr - lowerBndr +1);
	}

	template<>
	inline int uniform_rand<int>(int lowerBndr, int upperBndr){
		return uniform_rand_int(lowerBndr, upperBndr);
	}


	inline char random_char(){
		return (char)(uniform_rand_int(0,255));
	}
	*/

	/*
	inline double gauss_rand(double mean, double sigma){
	  double x, y, r2;
	  do {
		x = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
		y = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
		r2 = x * x + y * y;
	  } while (r2 > 1.0 || r2 == 0.0);
	  return mean + sigma * y * std::sqrt(-2.0 * log(r2) / r2);
	}

	inline bool random_bool()
	{
		return uniform_rand_int(0,1)!= 0;
	}
	*/


	/*
	class Uniform_int{
	public:
		Uniform_int(int min, int max){
			reset(min, max);
		}
		Uniform_int(){
		}
		void reset(int min, int max){
			min_ = min;
			max_ = max;
		}
		int gen()
		{
			return uniform_rand<int>(min_, max_);
		}
		std::vector<int> gen_N(std::size_t n){
			std::vector<int> vs;
			std::set<int> s;
			while(vs.size() < n){
				int v = gen();
				if(s.find(v) != s.end() )
					continue;

				vs.push_back(v);
				s.insert(v);
			}
			return vs;
		}
	private:
		int min_;
		int max_;
	};


	inline bool RateRandom(double rate)
	{
		if(rate< 0 || rate>1)
		{
			ER<<"invalid rate: "<<rate;
			throw 0;
		}
		if(rate>=1)
			return true;
		if(rate <=0)
			return false;

		double v = zm::uniform_rand<double>(0,1);
		if(v <= rate)
			return true;
		return false;
	}


	inline void random_sleep(int64_t lower, int64_t upper)
	{
		int64_t tk = (int64_t)zm::uniform_rand_int((int)lower, (int)upper);
		zm::sleep(tk);
	}
	*/




	// 
	// 	class __inner_Uniform_real
	// 	{
	// 	public:
	// 		static __inner_Uniform_real& Ins() {
	// 			static __inner_Uniform_real ins;
	// 			return ins;
	// 		}
	// 		std::random_device rd;
	// 		std::mt19937 gen;
	// 
	// 	private:
	// 		__inner_Uniform_real() : gen(rd()) {}
	// 	};
	// 
	// 
	// 
	// 
	// 	template<typename _T>
	// 	inline _T dy_uniform_real(_T min, _T max) {
	// 		std::uniform_real_distribution<_T> dis(min, max);
	// 		return dis(__inner_Uniform_real::Ins().gen);
	// 	}
	// 
	// 	//[min, max)
	// 	inline int dy_uniform_int(int min, int max) {
	// 		std::uniform_int_distribution<int> dis(min, max - 1);
	// 		return dis(__inner_Uniform_real::Ins().gen);
	// 	}
	// 
	// 	//[min, max]
	// 	inline int dy_uniform_int_ee(int min, int max) {
	// 		return dy_uniform_int(min, max + 1);
	// 	}
	// 
	// 
	// 	template<typename _T>
	// 	inline _T dy_gaussan_real(_T mean, _T cov) {
	// 		std::normal_distribution<_T> dis(mean, cov);
	// 		return dis(__inner_Uniform_real::Ins().gen);
	// 	}


	// 	#define uniform_int c_uniform_int
	// 	#define uniform_real c_uniform_real
	// 	#define dy_uniform_int_ee uniform_int_ee


	// 	template<typename _T>
	// 	inline _T dy_randomTrivialOne(const std::vector<_T>& ay)
	// 	{
	// 		if (ay.empty()) {
	// 			ER << "vector is empty";
	// 			throw 0;
	// 		}
	// 
	// 		int n = (int)zm::dy_uniform_int(0, (int)(ay.size()));
	// 		_T t = ay[n];
	// 		return t;
	// 	}
