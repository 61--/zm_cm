#pragma once

#include <deque>

#include "tr_cm.hpp"
#include "zm_log.hpp"
#include "zm_intArray.hpp"
#include "zm_log.hpp"


namespace zm
{

	template<typename _T>
	at::Tensor createTMat(const IntArray& sz
		, const std::vector<_T>& data
		, c10::ScalarType ty)
	{
		FT_IF(sz.volume() > data.size()) 
			<< "crateTMat invalid:  sz:"<<sz
			<<" - dataLen:"<<data.size();
		FT_IF(sz.getVal(0) <= 0);

		std::vector<int64_t> ay = sz.to_vector_int64_t();
		c10::IntArrayRef c10_sz(ay);

		at::Tensor ret;
		if (typeid(_T) == typeid(double))
		{
			at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kDouble);
			ret = t.clone().to(ty);
		}
		else if (typeid(_T) == typeid(float))
		{
			at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kFloat);
			ret = t.clone().to(ty);
		}
		else if (typeid(_T) == typeid(int64_t))
		{
			at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kLong);
			ret = t.clone().to(ty);
		}
		else if (typeid(_T) == typeid(int32_t))
		{
			at::Tensor t = torch::from_blob((void*)data.data(), c10_sz, at::kInt);
			ret = t.clone().to(ty);
		}else{
			LG_FT << "invalid type";
		}
		return ret;
	}

	template<typename _T>
	at::Tensor createTMat_dq(const IntArray& sz
		, const std::deque<_T>& data
		, c10::ScalarType ty)
	{
		std::vector<_T> data_ay(data.begin(), data.end());
		return createTMat(sz, data_ay, ty);
	}

	inline at::Tensor createZeroTMat(const IntArray& idx
		, c10::ScalarType ty
		, bool use_gpu = false)
	{
		std::vector<int64_t> ay = idx.to_vector_int64_t();
		c10::IntArrayRef ret(ay);

		at::Tensor t = at::zeros(ret, tr::dtype(ty));
		if (use_gpu) {
			t = t.to(DevIns::Ins().device_gpu);
		}
		return t;
	}



	inline at::Tensor createEyeTMat(int n
		, c10::ScalarType ty)
	{
		at::Tensor t = at::eye(n, tr::dtype(ty));
		return t;
	}

	inline at::Tensor createOneTMat(const IntArray& idx
		, c10::ScalarType ty)
	{
		std::vector<int64_t> ay = idx.to_vector_int64_t();
		c10::IntArrayRef ret(ay);

		at::Tensor t = at::ones(ret, tr::dtype(ty));
		return t;
	}

	inline at::Tensor createRandTMat(const IntArray& idx
		, c10::ScalarType ty)
	{
		std::vector<int64_t> ay = idx.to_vector_int64_t();
		c10::IntArrayRef ret(ay);

		at::Tensor t = at::rand(ret, tr::dtype(ty));
		return t;
	}

	inline at::Tensor createUniformTMat(const IntArray& idx
		, float min_v, float max_v
		, c10::ScalarType ty)
	{
		at::Tensor t = createZeroTMat(idx, ty);
		t.uniform_(min_v, max_v);
		return t;
	}

	inline TMat createRandBoolTMat(const IntArray& idx)
	{
		std::vector<int64_t> ay = idx.to_vector_int64_t();
		c10::IntArrayRef ret(ay);

		TMat m = tr::rand(ret, tr::dtype(tr::kFloat16));
		TMat bm = tr::le(m, 0.5);
		return bm;
	}

	inline TMat rowLike(TMat tm, int n, c10::ScalarType tp)
	{
		TMat m = createZeroTMat({ tm.size(0),n }, tp);

		if (checkIsGPU(tm)) {
			//LG << "m: " << m;
			m = to_gpu(m);
		}
		return m;
	}

	inline TMat rowLike(TMat tm, int n, double v, c10::ScalarType tp)
	{
		TMat m = createOneTMat({ tm.size(0),n }, tp) * v;

		if (checkIsGPU(tm)) {
			//LG << "m: " << m;
			m = to_gpu(m);
		}
		return m;
	}


	//------------------------------------


	inline TMat interp_1D(TMat in, int n_out)
	{
		FT_IF(in.ndimension() != 2);

		std::vector<int64_t> sz{n_out};
		tr::nn::functional::InterpolateFuncOptions options;
		options.mode(tr::kLinear).align_corners(false)
			.size(sz);;

		TMat m = in.unsqueeze(1);

		LG << "m: " << m;

		TMat m1 = tr::nn::functional::interpolate(m, options);

		return m1.squeeze(1);
		//LG<<"m1: "<<m1;

		//TMat r;
		//return r;
	}

	inline TMat to_max_one_hot(TMat val)
	{
		TMat max_idx = torch::argmax(val, 1);
		max_idx = torch::unsqueeze(max_idx, 1);

		
		TMat v_ret = torch::zeros_like(val);
		v_ret.scatter_(1, max_idx, 1);

		return v_ret;
	}

	inline TMat to_max_two_hot(TMat _val)
	{
		TMat val = _val.clone();
		TMat max_idx = torch::argmax(val, 1);
		max_idx = torch::unsqueeze(max_idx, 1);

		val.scatter_(1, max_idx, -1e8);

		TMat v_ret = torch::zeros_like(val);
		v_ret.scatter_(1, max_idx, 1);


		max_idx = torch::argmax(val, 1);
		max_idx = torch::unsqueeze(max_idx, 1);
		v_ret.scatter_(1, max_idx, 1);

		return v_ret;
	}


	inline TMat to_max_x_hot(TMat _val, int n)
	{
		TMat val = _val.clone();
		TMat max_idx = torch::argmax(val, 1);
		max_idx = torch::unsqueeze(max_idx, 1);

		

		TMat v_ret = torch::zeros_like(val);
		v_ret.scatter_(1, max_idx, 1);

		for (int i = 0; i < n-1; i++) {
			
			val.scatter_(1, max_idx, -1e8);

			max_idx = torch::argmax(val, 1);
			max_idx = torch::unsqueeze(max_idx, 1);
			v_ret.scatter_(1, max_idx, 1);
		}

		return v_ret;
	}

	inline TMat getRow(TMat data, int row)
	{
		return data.index({ row });
	}



	template<typename _T>
	inline TMat createTMat_1xn(const std::vector<_T>& vs, c10::ScalarType tp) {
		return createTMat({ 1, (int)vs.size() }, vs, tp);
	}
	template<typename _T>
	inline TMat createTMat_1xn_dq(const std::deque<_T>& vs, c10::ScalarType tp) {
		return createTMat_dq({ 1, (int)vs.size() }, vs, tp);
	}


	template<typename _T>
	inline TMat createTMat_nx1(const std::vector<_T>& vs, c10::ScalarType tp) {
		return createTMat({ (int)vs.size(),1 }, vs, tp);
	}
	template<typename _T>
	inline TMat createTMat_nx1_dq(const std::deque<_T>& vs, c10::ScalarType tp) {
		return createTMat_dq({ (int)vs.size(),1 }, vs, tp);
	}


	template<typename _T>
	inline TMat createTMat_n(const std::vector<_T>& vs, c10::ScalarType tp) {
		return createTMat<double>({ (int)vs.size() }, vs, tp);
	}
	template<typename _T>
	inline TMat createTMat_n_dq(const std::deque<_T>& vs, c10::ScalarType tp) {
		return createTMat_dq<double>({ (int)vs.size() }, vs, tp);
	}

	inline std::tuple<TMat, TMat> split_two(TMat s, int dim, int size_dim)
	{
		int n = s.size(dim);
		FT_IF(size_dim >= n) << "invalid s: " << size_dim;
		FT_IF(size_dim <= 0) << "invalid s: " << size_dim;

		std::vector<int64_t> s_d0, s_d1;
		for (int i = 0; i < size_dim; i++)
		{
			s_d0.push_back(i);
		}
		for (int i = size_dim; i < n; i++)
		{
			s_d1.push_back(i);
		}

		auto idx0 = createTMat<int64_t>({ s_d0.size() }, s_d0, tr::kI64);
		auto idx1 = createTMat<int64_t>({ s_d1.size() }, s_d1, tr::kI64);

// 		LG << "s: " << s.sizes();
// 		LG << "dim: " << dim;
// 		LG << "s: " << s;

		if (s.is_cpu()) {
			auto m1 = s.index_select(dim, (idx0));
			auto m2 = s.index_select(dim, (idx1));
			return std::tie(m1, m2);
		}
	
		auto m1 = s.index_select(dim, to_gpu(idx0));
		auto m2 = s.index_select(dim, to_gpu(idx1));
		return std::tie(m1, m2);

		
	}
}//