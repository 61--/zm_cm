#pragma once
#include "tr_cm.hpp"


namespace zm
{
	class ConstDyAcc
	{
	public:
		ConstDyAcc(){}
		ConstDyAcc(const TMat& m) {
			bf_ = m.data_ptr();
			strides_ = m.strides();

#ifdef _DEBUG
			__ck_tp_ = m.dtype();
#endif
		}


		template<typename _T>
		inline _T _get(int idx0) const
		{
			DFT_IF(strides_.size() != 1);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];

			return *f_bf;
		}

		template<typename _T>
		inline _T _get(int idx0, int idx1) const
		{
			DFT_IF(strides_.size() != 2);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];

			return *f_bf;
		}
		template<typename _T>
		inline _T _get(int idx0, int idx1, int idx2) const
		{
			DFT_IF(strides_.size() != 3);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];
			f_bf += idx2 * strides_[2];

			return *f_bf;
		}

	protected:
		template<typename _T>
		inline void _DBG_CHECK() const {
#ifdef _DEBUG
			if (typeid(_T) == typeid(double))
			{
				FT_IF(__ck_tp_ != tr::kFloat64) << "invalid type";
			}
			else if (typeid(_T) == typeid(float))
			{
				FT_IF(__ck_tp_ != tr::kFloat32) << "invalid type";
			}
			else if (typeid(_T) == typeid(int64_t))
			{
				FT_IF(__ck_tp_ != tr::kInt64) << "invalid type";
			}
			else if (typeid(_T) == typeid(int32_t))
			{
				FT_IF(__ck_tp_ != tr::kInt32) << "invalid type";
			}
			else if (typeid(_T) == typeid(bool))
			{
				FT_IF(__ck_tp_ != tr::kBool) << "invalid type";
			}
			else {
				LG_FT << "unsupport type";
			}
#endif
		}


	protected:
		void* bf_{nullptr};
		c10::IntArrayRef strides_;

#ifdef _DEBUG
		caffe2::TypeMeta __ck_tp_;
#endif

	};

	class DyAcc :public ConstDyAcc
	{
	public:
		DyAcc(){}
		DyAcc(const TMat& m) :ConstDyAcc(m) {}

		template<typename _T>
		inline void _set(int idx0, _T v)
		{
			DFT_IF(strides_.size() != 1);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];

			*f_bf = v;
		}

		template<typename _T>
		inline void _set(int idx0, int idx1, _T v)
		{
			DFT_IF(strides_.size() != 2);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];

			*f_bf = v;
		}
		template<typename _T>
		inline void _set(int idx0, int idx1, int idx2, _T v)
		{
			DFT_IF(strides_.size() != 3);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];
			f_bf += idx2 * strides_[2];

			*f_bf = v;
		}

	};
	/*
	class DyAcc
	{
	public:
		DyAcc(TMat& m) {
			bf_ = m.data_ptr();
			strides_ = m.strides();

#ifdef _DEBUG
			__ck_tp_ = m.dtype();
#endif
		}

		template<typename _T>
		inline void _set(int idx0, _T v)
		{
			DFT_IF(strides_.size() != 1);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];

			*f_bf = v;
		}

		template<typename _T>
		inline void _set(int idx0, int idx1, _T v) 
		{
			DFT_IF(strides_.size() != 2);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];

			*f_bf = v;
		}
		template<typename _T>
		inline void _set(int idx0, int idx1, int idx2, _T v)
		{
			DFT_IF(strides_.size() != 3);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];
			f_bf += idx2 * strides_[2];

			*f_bf = v;
		}

		template<typename _T>
		inline _T _get(int idx0) const
		{
			DFT_IF(strides_.size() != 1);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];

			return *f_bf;
		}

		template<typename _T>
		inline _T _get(int idx0, int idx1) const
		{
			DFT_IF(strides_.size() != 2);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];

			return *f_bf;
		}
		template<typename _T>
		inline _T _get(int idx0, int idx1, int idx2) const
		{
			DFT_IF(strides_.size() != 3);
			_DBG_CHECK<_T>();

			_T* f_bf = (_T*)bf_;

			f_bf += idx0 * strides_[0];
			f_bf += idx1 * strides_[1];
			f_bf += idx2 * strides_[2];

			return *f_bf;
		}

	private:
		template<typename _T>
		inline void _DBG_CHECK() const{
#ifdef _DEBUG
			if (typeid(_T) == typeid(double)) 
			{
				FT_IF(__ck_tp_ != tr::kFloat64) << "invalid type";
			}
			else if (typeid(_T) == typeid(float))
			{
				FT_IF(__ck_tp_ != tr::kFloat32) << "invalid type";
			}
			else if (typeid(_T) == typeid(int64_t))
			{
				FT_IF(__ck_tp_ != tr::kInt64) << "invalid type";
			}
			else if (typeid(_T) == typeid(int32_t))
			{
				FT_IF(__ck_tp_ != tr::kInt32) << "invalid type";
			}
			else {
				LG_FT << "unsupport type";
			}
#endif
		}



	protected:
		void* bf_{nullptr};
		c10::IntArrayRef strides_;

#ifdef _DEBUG
		caffe2::TypeMeta __ck_tp_;
#endif
		
	};
	*/


	//-----------------------------------------------------------------
	//-----------------------------------------------------------------

	class DyAccEx :public DyAcc
	{
	public:
		DyAccEx(TMat& m):DyAcc(m) {
			tp_ = m.dtype();
		}

		template<typename _T>
		_T get(const std::vector<int>& idxs) {
			FT_IF(idxs.size() != strides_.size())<<"invalid size";

			_T* f_bf = (_T*)bf_;

			for (int i = 0; i < idxs.size(); i++) {
				f_bf += idxs[i] * strides_[i];
			}
			return *f_bf;
		}

		template<typename _T>
		void set(const std::vector<int>& idxs, _T v) {
			FT_IF(idxs.size() != strides_.size())<< "invalid size";

			_T* f_bf = (_T*)bf_;

			for (int i = 0; i < idxs.size(); i++) {
				f_bf += idxs[i] * strides_[i];
			}
			*f_bf = v;
		}


		double get_double(int i0) const{
			if (tp_ == tr::kDouble)
				return _get<double>(i0);

			LG_FT << "empty type";
			return 0;
		}


	protected:
		caffe2::TypeMeta tp_;
	};



	
	template<typename _T, typename _TOut>
	inline std::vector<_TOut> __to_vector__(const TMat& mat)
	{
		DyAcc acc(mat);
		if (mat.dim() == 1) 
		{
			std::vector<_TOut> ay(mat.size(0));
			for (int i = 0; i < mat.size(0); i++) {
				ay[i] =  acc._get<_T>(i);
			}
			return ay;
		}
		else if (mat.dim() == 2) 
		{
			if (mat.size(0) == 1)
			{
				std::vector<_TOut> ay(mat.size(1));
				for (int i = 0; i < mat.size(1); i++) {
					ay[i] = acc._get<_T>(0,i);
				}
				return ay;
			}
			else {
				std::vector<_TOut> ay(mat.size(0));
				for (int i = 0; i < mat.size(0); i++) {
					ay[i] = acc._get<_T>(i,0);
				}
				return ay;
			}
		}

		LG_FT << "imsupport";
		return std::vector<_TOut>();
	}

	template<typename _T>
	inline std::vector<_T> to_vector(const TMat& mat)
	{
		if (mat.scalar_type() == tr::kF32) {
			return __to_vector__<float, _T>(mat);
		}
		else if (mat.scalar_type() == tr::kF64) {
			return __to_vector__<double, _T>(mat);
		}
		LG_FT << "invlaid mat type";
		return std::vector<_T>();
	}

}//