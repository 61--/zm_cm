#pragma once
#include <vector>
#include <initializer_list>
#include <torch/torch.h>
#include "zm_log.hpp"


namespace zm
{
	struct IntArray
	{
		IntArray() {}

		template<typename _T>
		IntArray(std::initializer_list<_T> vs) {
			std::vector<_T> v_vs(vs.begin(), vs.end());
			datas.resize(v_vs.size());
			for (int i = 0; i < v_vs.size(); i++) {
				datas[i] = (int)v_vs[i];
			}
		}

		IntArray(std::initializer_list<int64_t> vs) {
			std::vector<int64_t> v_vs(vs.begin(), vs.end());
			datas.resize(v_vs.size());
			for (int i = 0; i < v_vs.size(); i++) {
				datas[i] = (int)v_vs[i];
			}
		}

		template<typename _T>
		IntArray(const std::vector<_T>& vs) {
			datas.resize(vs.size());
			for (int i = 0; i < vs.size(); i++) {
				datas[i] = vs[i];
			}
		}

		IntArray(c10::IntArrayRef sz_ay)
		{
			datas.resize(sz_ay.size());
			for (int i = 0; i < sz_ay.size(); i++)
			{
				datas[i] = sz_ay[i];
			}
		}

		IntArray(int v0) {
			datas = { v0 };
		}
		IntArray(int v0, int v1) {
			datas = { v0, v1 };
		}
		IntArray(int v0, int v1, int v2) {
			datas = { v0, v1 , v2};
		}
		IntArray(int v0, int v1, int v2, int v3) {
			datas = { v0, v1 , v2, v3 };
		}

		int len() {
			return datas.size();
		}
		int len() const {
			return datas.size();
		}

		int getVal(int idx) {
			return datas[idx];
		}
		int getVal(int idx) const {
			if (idx <0 || idx> datas.size()) {
				LG_FT << "invalid idx: " << idx;
				return 0;
			}
			return datas[idx];
		}

		void setVal(int idx, int v) {
			datas.at(idx) = v;
		}

		std::vector<int64_t> to_vector_int64_t() const {
			std::vector<int64_t> ret(datas.size());
			for (int i = 0; i < datas.size(); i++)
			{
				ret[i] = datas[i];
			}
			return ret;
		}

		int volume() const {
			if (len() == 0)
				return 0;

			int n = 1;
			for (int i = 0; i < len(); i++)
			{
				n *= getVal(i);
			}
			return n;
		}

	private:
		std::vector<int> datas;
	};


	inline bool operator==(const IntArray& i1, const IntArray& i2)
	{
		if (i1.len() != i2.len())
			return false;

		int n1 = i1.len();
		for (int i = 0; i < n1; i++)
		{
			if (i1.getVal(i) != i2.getVal(i))
				return false;
		}
		return true;
	}

	inline bool operator!=(const IntArray& i1, const IntArray& i2)
	{
		if (i1 == i2)
			return false;
		return true;
	}

}//


inline cpplog::My_ostream& operator<<(cpplog::My_ostream& ss
	, const zm::IntArray& idx)
{
	ss << "[";
	for (int i = 0; i < idx.len(); i++)
	{
		if (i != 0)
			ss << ", ";
		ss << idx.getVal(i);
	}
	ss << "]";
	return ss;
}