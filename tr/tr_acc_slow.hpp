#pragma once
#include <ATen/ATen.h>
//#include <torch/torch.h>
#include <boost/shared_ptr.hpp>
#include "zm_intArray.hpp"



namespace zm
{
	inline IntArray makeGIndx(c10::IntArrayRef sz_ay)
	{
		IntArray idx(sz_ay);
		return idx;
	}


	class KernelAcc
	{
	public:
		virtual double& get_double_ref(int i1) { LG_FT << "empty func: "<< dbg_class_name_;  static double v = 0; return v; }
		virtual double& get_double_ref(int i1, int i2) { LG_FT << "empty func";  static double v = 0; return v; }
		virtual double& get_double_ref(int i1, int i2, int i3) { LG_FT << "empty func";  static double v = 0; return v; }
		virtual double& get_double_ref(int i1, int i2, int i3, int i4) { LG_FT << "empty func";  static double v = 0; return v; }

		virtual double get_double(int i1) const{ LG_FT << "empty func"; static double v = 0; return v; }
		virtual double get_double(int i1, int i2) const{ LG_FT << "empty func"; static  double v = 0; return v; }
		virtual double get_double(int i1, int i2, int i3) const{ LG_FT << "empty func"; static double v = 0; return v; }
		virtual double get_double(int i1, int i2, int i3, int i4) const { LG_FT << "empty func"; static double v = 0; return v; }

		virtual float& get_float_ref(int i1) { LG_FT << "empty func"; static  float v = 0; return v; }
		virtual float& get_float_ref(int i1, int i2) { LG_FT << "empty func"; static  float v = 0; return v; }
		virtual float& get_float_ref(int i1, int i2, int i3) { LG_FT << "empty func"; static  float v = 0; return v; }
		virtual float& get_float_ref(int i1, int i2, int i3, int i4) { LG_FT << "empty func"; static  float v = 0; return v; }

		virtual float get_float(int i1) const { LG_FT << "empty func"; static  double v = 0; return v; }
		virtual float get_float(int i1, int i2) const { LG_FT << "empty func"; static double v = 0; return v; }
		virtual float get_float(int i1, int i2, int i3) const { LG_FT << "empty func"; static  double v = 0; return v; }
		virtual float get_float(int i1, int i2, int i3, int i4) const { LG_FT << "empty func"; static  double v = 0; return v; }

		virtual int64_t get_int64(int i1) const { LG_FT << "empty func"; return 0; }
		virtual int64_t get_int64(int i1, int i2) const { LG_FT << "empty func"; return 0; }
		virtual int64_t get_int64(int i1, int i2, int i3) const { LG_FT << "empty func"; return 0; }
		virtual int64_t get_int64(int i1, int i2, int i3, int i4) const { LG_FT << "empty func"; return 0; }

		virtual void set1(int i1, double){ LG_FT << "empty func";}
		virtual void set2(int i1, int i2, double){ LG_FT << "empty func";}
		virtual void set3(int i1, int i2, int i3, double){ LG_FT << "empty func";}
		virtual void set4(int i1, int i2, int i3, int i4, double) { LG_FT << "empty func"; }

		virtual int dim() const = 0;
		virtual int size(int n) const= 0;
		virtual IntArray gIdx() const= 0;
	protected:
		std::string dbg_class_name_;
	};
	typedef boost::shared_ptr<KernelAcc> KernelAccPtr;
	
	class KernelAcc_double_1:public KernelAcc
	{
	public:
		KernelAcc_double_1(at::Tensor tr):acc_(tr.accessor<double,1>()){
			dbg_class_name_ = "KernelAcc_double_1";
		}

		virtual double& get_double_ref(int i1) { return acc_[i1]; }
		virtual double get_double(int i1) const{ return acc_[i1]; }
		virtual float get_float(int i1) const { return acc_[i1]; }
		virtual int64_t get_int64(int i1) const { return (int64_t)std::round(acc_[i1]); }

		virtual void set1(int i1, double v) { get_double_ref(i1) = v; }

		virtual int dim() const{ return 1; }
		virtual int size(int n) const{ return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<double,1> acc_;
	};

	class KernelAcc_double_2 :public KernelAcc
	{
	public:
		KernelAcc_double_2(at::Tensor tr) :acc_(tr.accessor<double, 2>()) {
			dbg_class_name_ = "KernelAcc_double_2";
		}

		virtual double& get_double_ref(int i0, int i1) { return acc_[i0][i1]; }
		virtual double get_double(int i0, int i1) const { return acc_[i0][i1]; }
		virtual float get_float(int i0, int i1) const { return acc_[i0][i1]; }
		virtual int64_t get_int64(int i0, int i1) const { return (int64_t)std::round(acc_[i0][i1]); }

		virtual void set2(int i0, int i1, double v) { get_double_ref(i0,i1) = v; }

		virtual int dim() const{ return 2; }
		virtual int size(int n) const{ return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<double, 2> acc_;
	};

	class KernelAcc_double_3 :public KernelAcc
	{
	public:
		KernelAcc_double_3(at::Tensor tr) :acc_(tr.accessor<double, 3>()) {}
		virtual double& get_double_ref(int i0, int i1, int i2) { return acc_[i0][i1][i2]; }
		virtual double get_double(int i0, int i1, int i2) const { return acc_[i0][i1][i2]; }
		virtual float get_float(int i0, int i1, int i2) const { return acc_[i0][i1][i2]; }
		virtual int64_t get_int64(int i0, int i1, int i2) const { return (int64_t)std::round(acc_[i0][i1][i2]); }

		virtual void set3(int i0, int i1, int i2, double v){ get_double_ref(i0, i1, i2) = v; }

		virtual int dim() const{ return 3; }
		virtual int size(int n) const{ return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<double, 3> acc_;
	};

	class KernelAcc_double_4 :public KernelAcc
	{
	public:
		KernelAcc_double_4(at::Tensor tr) :acc_(tr.accessor<double, 4>()) {}
		virtual double& get_double_ref(int i0, int i1, int i2, int i3) { return acc_[i0][i1][i2][i3]; }
		virtual double get_double(int i0, int i1, int i2, int i3) const { return acc_[i0][i1][i2][i3]; }
		virtual float get_float(int i0, int i1, int i2, int i3) const { return acc_[i0][i1][i2][i3]; }
		virtual int64_t get_int64(int i0, int i1, int i2, int i3) const { return (int64_t)std::round(acc_[i0][i1][i2][i3]); }

		virtual void set4(int i0, int i1, int i2, int i3, double v) { get_double_ref(i0, i1, i2, i3) = v; }

		virtual int dim() const { return 4; }
		virtual int size(int n) const { return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<double, 4> acc_;
	};
	

	class KernelAcc_float_1 :public KernelAcc
	{
	public:
		KernelAcc_float_1(at::Tensor tr) :acc_(tr.accessor<float, 1>()) {
			dbg_class_name_ = "KernelAcc_float_1";
		}

		
		virtual double get_double(int i1) const { return acc_[i1]; }
		virtual float& get_float_ref(int i1) { return acc_[i1]; }
		virtual float get_float(int i1) const { return acc_[i1]; }
		virtual int64_t get_int64(int i1) const { return (int64_t)std::round(acc_[i1]); }

		virtual void set1(int i1, double v) { get_float_ref(i1) = v; }


		virtual int dim() const { return 1; }
		virtual int size(int n) const { return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<float, 1> acc_;
	};

	class KernelAcc_float_2 :public KernelAcc
	{
	public:
		KernelAcc_float_2(at::Tensor tr) :acc_(tr.accessor<float, 2>()) {}

		virtual float& get_float_ref(int i0, int i1) { return acc_[i0][i1]; }
		virtual double get_double(int i0, int i1) const { return acc_[i0][i1]; }
		virtual float get_float(int i0, int i1) const { return acc_[i0][i1]; }
		virtual int64_t get_int64(int i0, int i1) const { return (int64_t)std::round(acc_[i0][i1]); }

		virtual void set2(int i0, int i1, double v) { get_float_ref(i0, i1) = v; }

		virtual int dim() const { return 2; }
		virtual int size(int n) const { return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<float, 2> acc_;
	};

	class KernelAcc_float_3 :public KernelAcc
	{
	public:
		KernelAcc_float_3(at::Tensor tr) :acc_(tr.accessor<float, 3>()) {}
		virtual float& get_float_ref(int i0, int i1, int i2) { return acc_[i0][i1][i2]; }
		virtual double get_double(int i0, int i1, int i2) const { return acc_[i0][i1][i2]; }
		virtual float get_float(int i0, int i1, int i2) const { return acc_[i0][i1][i2]; }
		virtual int64_t get_int64(int i0, int i1, int i2) const { return (int64_t)std::round(acc_[i0][i1][i2]); }

		virtual void set3(int i0, int i1, int i2, double v) { get_float_ref(i0, i1, i2) = v; }

		virtual int dim() const { return 3; }
		virtual int size(int n) const { return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<float, 3> acc_;
	};

	class KernelAcc_float_4 :public KernelAcc
	{
	public:
		KernelAcc_float_4(at::Tensor tr) :acc_(tr.accessor<float, 4>()) {}
		virtual float& get_float_ref(int i0, int i1, int i2, int i3) { return acc_[i0][i1][i2][i3]; }
		virtual double get_double(int i0, int i1, int i2, int i3) const { return acc_[i0][i1][i2][i3]; }
		virtual float get_float(int i0, int i1, int i2, int i3) const { return acc_[i0][i1][i2][i3]; }
		virtual int64_t get_int64(int i0, int i1, int i2, int i3) const { return (int64_t)std::round(acc_[i0][i1][i2][i3]); }

		virtual void set3(int i0, int i1, int i2, int i3, double v) { get_float_ref(i0, i1, i2, i3) = v; }

		virtual int dim() const { return 4; }
		virtual int size(int n) const { return acc_.size(n); }
		virtual IntArray gIdx() const { return makeGIndx(acc_.sizes()); }

	private:
		at::TensorAccessor<float, 4> acc_;
	};



	class TrAcc
	{
	public:
		enum FLAG {
			raw,
			copy,
			deep_copy
		};

	public:
		TrAcc();
		TrAcc(at::Tensor tr, FLAG flag = copy);
		void ini(at::Tensor tr, FLAG flag = copy);

		template<typename _T>
		_T& at(int i0);
		template<typename _T>
		_T& at(int i0, int i1);	
		template<typename _T>
		_T& at(int i0, int i1, int i2);
		template<typename _T>
		_T& at(int i0, int i1, int i2, int i3);
		template<typename _T>
		_T& at(const IntArray& idx);

		template<typename _T>
		_T get(int i0) const;
		template<typename _T>
		_T get(int i0, int i1) const;
		template<typename _T>
		_T get(int i0, int i1, int i2) const;
		template<typename _T>
		_T get(int i0, int i1, int i2, int i3) const;
		template<typename _T>
		_T get(const IntArray& idx) const;

		void set1(int i1, double);
		void set2(int i1, int i2, double);
		void set3(int i1, int i2, int i3, double);
		void set4(int i1, int i2, int i3, int i4, double);

		int dim() const{ return acc_->dim(); }
		int size(int n) const{ return acc_->size(n); }
		IntArray gIdx() const { return acc_->gIdx(); }

	private:
		KernelAccPtr acc_;
		at::Tensor cp_data_;
	};


	inline TrAcc::TrAcc()
	{

	}

	inline TrAcc::TrAcc(at::Tensor tr, FLAG flag)
	{
		ini(tr, flag);
	}

	inline void TrAcc::ini(at::Tensor _tr, FLAG flag)
	{
		at::Tensor* p_tr = &_tr;
		if (flag == copy) {
			cp_data_ = _tr;
			p_tr = &cp_data_;
		}
		else if (flag == deep_copy) {
			cp_data_ = _tr.clone();
			p_tr = &cp_data_;
		}

		if (p_tr->scalar_type() == at::kDouble)
		{
			switch (p_tr->dim()) {
			case 1: acc_.reset(new KernelAcc_double_1(*p_tr)); break;
			case 2: acc_.reset(new KernelAcc_double_2(*p_tr)); break;
			case 3: acc_.reset(new KernelAcc_double_3(*p_tr)); break;
			case 4: acc_.reset(new KernelAcc_double_4(*p_tr)); break;
			default:
				LG_FT << "invalid dim: " << p_tr->dim();
			}
		}
		else if (p_tr->scalar_type() == at::kFloat) {
			switch (p_tr->dim()) {
			case 1: acc_.reset(new KernelAcc_float_1(*p_tr)); break;
			case 2: acc_.reset(new KernelAcc_float_2(*p_tr)); break;
			case 3: acc_.reset(new KernelAcc_float_3(*p_tr)); break;
			case 4: acc_.reset(new KernelAcc_float_4(*p_tr)); break;
			default:
				LG_FT << "invalid dim: " << p_tr->dim();
			}
		}
		else {
			LG_FT << "invalid tr type";
		}
	}

	template<typename _T>
	inline _T& TrAcc::at(int)
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}

	template<typename _T>
	inline _T& TrAcc::at(int, int)
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}

	template<typename _T>
	inline _T& TrAcc::at(int, int, int)
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}
	template<typename _T>
	inline _T& TrAcc::at(int, int, int, int)
	{
		LG_FT << "empty func";
		static _T v;
		return v;
	}

	template<typename _T>
	inline _T& TrAcc::at(const zm::IntArray& idx)
	{
		if (idx.len() == 1)
		{
			return at<_T>(idx.getVal(0));
		}
		else if (idx.len() == 2)
		{
			return at<_T>(idx.getVal(0), idx.getVal(1));
		}
		else if (idx.len() == 3)
		{
			return at<_T>(idx.getVal(0), idx.getVal(1), idx.getVal(2));
		}
		else if (idx.len() == 4)
		{
			return at<_T>(idx.getVal(0), idx.getVal(1), idx.getVal(2), idx.getVal(3));
		}
		else {
			LG_FT << "invalid dim";
		}

		static _T v;
		return v;
	}

	template<typename _T>
	inline _T TrAcc::get(int) const
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}

	template<typename _T>
	inline _T TrAcc::get(int, int) const
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}

	template<typename _T>
	inline _T TrAcc::get(int, int, int) const
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}
	template<typename _T>
	inline _T TrAcc::get(int, int, int,int) const
	{
		LG_FT << "empty func";
		_T v;
		return v;
	}

	template<typename _T>
	inline _T TrAcc::get(const IntArray& idx) const
	{
		if (idx.len() == 1)
		{
			return get<_T>(idx.getVal(0));
		}
		else if (idx.len() == 2)
		{
			return get<_T>(idx.getVal(0), idx.getVal(1));
		}
		else if (idx.len() == 3)
		{
			return get<_T>(idx.getVal(0), idx.getVal(1), idx.getVal(2));
		}
		else if (idx.len() == 4)
		{
			return get<_T>(idx.getVal(0), idx.getVal(1), idx.getVal(2), idx.getVal(3));
		}
		else {
			LG_FT << "invalid dim";
		}

		_T v(0);
		return v;
	}

	template<>
	inline double& TrAcc::at<double>(int i0)
	{
		return acc_->get_double_ref(i0);
	}

	template<>
	inline double& TrAcc::at<double>(int i0, int i1)
	{
		return acc_->get_double_ref(i0, i1);
	}

	template<>
	inline double& TrAcc::at<double>(int i0, int i1, int i2)
	{
		return acc_->get_double_ref(i0, i1, i2);
	}

	template<>
	inline double& TrAcc::at<double>(int i0, int i1, int i2, int i3)
	{
		return acc_->get_double_ref(i0, i1, i2, i3);
	}

	template<>
	inline double TrAcc::get<double>(int i0) const
	{
		return acc_->get_double(i0);
	}

	template<>
	inline double TrAcc::get<double>(int i0, int i1) const
	{
		return acc_->get_double(i0, i1);
	}

	template<>
	inline double TrAcc::get<double>(int i0, int i1, int i2) const
	{
		return acc_->get_double(i0, i1, i2);
	}

	template<>
	inline double TrAcc::get<double>(int i0, int i1, int i2, int i3) const
	{
		return acc_->get_double(i0, i1, i2, i3);
	}

	template<>
	inline float& TrAcc::at<float>(int i0)
	{
		return acc_->get_float_ref(i0);
	}

	template<>
	inline float& TrAcc::at<float>(int i0, int i1)
	{
		return acc_->get_float_ref(i0, i1);
	}

	template<>
	inline float& TrAcc::at<float>(int i0, int i1, int i2)
	{
		return acc_->get_float_ref(i0, i1, i2);
	}

	template<>
	inline float& TrAcc::at<float>(int i0, int i1, int i2, int i3)
	{
		return acc_->get_float_ref(i0, i1, i2, i3);
	}


	template<>
	inline float TrAcc::get<float>(int i0) const
	{
		return acc_->get_float(i0);
	}

	template<>
	inline float TrAcc::get<float>(int i0, int i1) const
	{
		return acc_->get_float(i0, i1);
	}

	template<>
	inline float TrAcc::get<float>(int i0, int i1, int i2) const
	{
		return acc_->get_float(i0, i1, i2);
	}

	template<>
	inline float TrAcc::get<float>(int i0, int i1, int i2, int i3) const
	{
		return acc_->get_float(i0, i1, i2, i3);
	}

	inline void TrAcc::set1(int i1, double v)
	{
		return acc_->set1(i1, v);
	}

	inline void TrAcc::set2(int i1, int i2, double v)
	{
		return acc_->set2(i1, i2, v);
	}

	inline void TrAcc::set3(int i1, int i2, int i3, double v)
	{
		return acc_->set3(i1, i2, i3, v);
	}

	inline void TrAcc::set4(int i1, int i2, int i3, int i4, double v)
	{
		return acc_->set4(i1, i2, i3, i4, v);
	}


	template<>
	inline int64_t TrAcc::get<int64_t>(int i0) const
	{
		return acc_->get_int64(i0);
	}

	template<>
	inline int64_t TrAcc::get<int64_t>(int i0, int i1) const
	{
		return acc_->get_int64(i0, i1);
	}

	template<>
	inline int64_t TrAcc::get<int64_t>(int i0, int i1, int i2) const
	{
		return acc_->get_int64(i0, i1, i2);
	}

	template<>
	inline int64_t TrAcc::get<int64_t>(int i0, int i1, int i2, int i3) const
	{
		return acc_->get_int64(i0, i1, i2, i3);
	}
}//