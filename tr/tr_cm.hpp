#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <torch/torch.h>
#undef UNICODE
#include <torch/script.h>
#include "zm_log.hpp"


#pragma comment(lib, "torch.lib")
#pragma comment(lib, "torch_cpu.lib")
#pragma comment(lib, "torch_cuda.lib")
#pragma comment(lib, "c10.lib")

namespace tr = torch;
typedef  at::Tensor TMat;

#ifdef _WIN32
#include <windows.h>
#endif



namespace zm
{
#ifdef _WIN32

	inline void ini_torch_cuda()
	{

		LoadLibraryA("ATen_cuda.dll");
		LoadLibraryA("c10_cuda.dll");
		LoadLibraryA("torch_cuda.dll");
		LoadLibraryA("torchvision.dll");

		if (!torch::cuda::is_available()) {
			LG_FT << "cuda is_available is no avb";
		}
		if (!torch::cuda::cudnn_is_available()) {
			LG_FT << "cudnn is_available is no avb";
		}

		if (torch::cuda::device_count() == 0) {
			LG_FT << "device_count is zero";
		}
	}
#else
	inline void ini_torch_cuda()
	{
	}

#endif



	inline void EnsureSameDim0(const TMat& m0, const TMat& m1) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);
	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);
	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);

		FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars3: " << m3.size(0);
	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);

		FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars3: " << m3.size(0);

		FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars4: " << m4.size(0);

	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);

		FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars3: " << m3.size(0);

		FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars4: " << m4.size(0);

		FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars5: " << m5.size(0);
	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);

		FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars3: " << m3.size(0);

		FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars4: " << m4.size(0);

		FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars5: " << m5.size(0);

		FT_IF(m0.size(0) != m6.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars6: " << m6.size(0);
	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6, const TMat& m7) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);

		FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars3: " << m3.size(0);

		FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars4: " << m4.size(0);

		FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars5: " << m5.size(0);

		FT_IF(m0.size(0) != m6.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars6: " << m6.size(0);

		FT_IF(m0.size(0) != m7.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars7: " << m7.size(0);
	}

	inline void EnsureSameDim0(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6
		, const TMat& m7 , const TMat& m8) {
		FT_IF(m0.size(0) != m1.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars1: " << m1.size(0);

		FT_IF(m0.size(0) != m2.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars2: " << m2.size(0);

		FT_IF(m0.size(0) != m3.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars3: " << m3.size(0);

		FT_IF(m0.size(0) != m4.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars4: " << m4.size(0);

		FT_IF(m0.size(0) != m5.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars5: " << m5.size(0);

		FT_IF(m0.size(0) != m6.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars6: " << m6.size(0);

		FT_IF(m0.size(0) != m7.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars7: " << m7.size(0);

		FT_IF(m0.size(0) != m8.size(0)) << "invalid dim0: "
			<< " pars0: " << m0.size(0)
			<< " pars8: " << m8.size(0);
	}


	inline void EnsureSameDev(const TMat& m0, const TMat& m1) {
		FT_IF(m0.device() != m1.device()) << "invalid dim0: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
		FT_IF(m0.device() != m3.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars3: " << m3.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
		FT_IF(m0.device() != m3.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars3: " << m3.device();
		FT_IF(m0.device() != m4.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars4: " << m4.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
		FT_IF(m0.device() != m3.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars3: " << m3.device();
		FT_IF(m0.device() != m4.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars4: " << m4.device();
		FT_IF(m0.device() != m5.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars5: " << m5.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
		FT_IF(m0.device() != m3.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars3: " << m3.device();
		FT_IF(m0.device() != m4.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars4: " << m4.device();
		FT_IF(m0.device() != m5.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars5: " << m5.device();

		FT_IF(m0.device() != m6.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars6: " << m6.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6, const TMat& m7) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
		FT_IF(m0.device() != m3.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars3: " << m3.device();
		FT_IF(m0.device() != m4.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars4: " << m4.device();
		FT_IF(m0.device() != m5.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars5: " << m5.device();

		FT_IF(m0.device() != m6.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars6: " << m6.device();
		FT_IF(m0.device() != m7.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars7: " << m7.device();
	}

	inline void EnsureSameDev(const TMat& m0, const TMat& m1, const TMat& m2
		, const TMat& m3, const TMat& m4, const TMat& m5, const TMat& m6
		, const TMat& m7, const TMat& m8) {
		FT_IF(m0.device() != m1.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars1: " << m1.device();
		FT_IF(m0.device() != m2.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars2: " << m2.device();
		FT_IF(m0.device() != m3.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars3: " << m3.device();
		FT_IF(m0.device() != m4.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars4: " << m4.device();
		FT_IF(m0.device() != m5.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars5: " << m5.device();

		FT_IF(m0.device() != m6.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars6: " << m6.device();
		FT_IF(m0.device() != m7.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars7: " << m7.device();

		FT_IF(m0.device() != m8.device()) << "invalid dev: "
			<< " pars0: " << m0.device()
			<< " pars8: " << m8.device();
	}

	//------------

	inline void EnsureSameSizes(const TMat& m0, const TMat& m1) {
		FT_IF(m0.sizes() != m1.sizes()) << "invalid sizes: "
			<< " pars0: " << m0.sizes()
			<< " pars1: " << m1.sizes();
	}


	class TMatCK
	{
	public:
		TMatCK(TMat& m):m_(m) {}

		TMatCK& DimEq(int n) {
			FT_IF(m_.dim() != n) << "invalid dim: "
				<< m_.dim() << " - should: " << n
				<< " data: " << m_;
			return *this;
		}
		TMatCK& SXEq(int dim, int n) {
			FT_IF(m_.size(dim) != n) << "invalid size: " << m_.sizes()
				<< " - should: "
				<< " dim:" << dim << " v:" << n
				<< " data: " << m_;
			return *this;
		}
		TMatCK& S0Eq(int n) {
			return SXEq(0, n);
		}
		TMatCK& S1Eq(int n) {
			return SXEq(1, n);
		}
		TMatCK& S2Eq(int n) {
			return SXEq(2, n);
		}
		TMatCK& TypeEq(c10::ScalarType ty) {
			FT_IF(m_.dtype() != ty) << "invalid type: " << m_.dtype()
				<<"  should: "<<ty;
			return *this;
		}


	private:
		TMat& m_;
	};

	inline TMat maxOneHot(TMat m)
	{
		TMatCK(m).DimEq(2);
		auto idx = tr::argmax(m, -1, true);
		TMat m2 = tr::zeros_like(m).scatter(-1, idx, 1);
		return m2;
	}

	inline tr::optim::Adam genOpt_m(const std::vector<TMat>& pars, double lrate)
	{
		tr::optim::Adam opt(pars, tr::optim::AdamOptions(lrate));
		return opt;
	}

	inline tr::optim::Adam genOpt_m(const std::vector<std::vector<TMat> >& pars_ay, double lrate)
	{
		std::vector<TMat> pars;
		for (auto& tmp_par : pars_ay)
		{
			pars.insert(pars.end(), tmp_par.begin(), tmp_par.end());
		}

		tr::optim::Adam opt(pars, tr::optim::AdamOptions(lrate));
		return opt;
	}

	inline boost::shared_ptr<tr::optim::Adam > genOpt_m_ptr(
		const std::vector<TMat>& pars, double lrate)
	{
		boost::shared_ptr<tr::optim::Adam >  opt;
		opt.reset(new tr::optim::Adam(pars, tr::optim::AdamOptions(lrate)));

		return opt;
	}

	inline boost::shared_ptr<tr::optim::Adam > genOpt_m_ptr(
		const std::vector<std::vector<TMat> >& pars_ay
		, double lrate)
	{
		std::vector<TMat> pars;
		for (auto& tmp_par : pars_ay)
		{
			pars.insert(pars.end(), tmp_par.begin(), tmp_par.end());
		}

		return genOpt_m_ptr(pars, lrate);
	}


	inline void ini_opt(tr::optim::Adam& opt)
	{
		opt.zero_grad();
	}

	inline void ini_opt(boost::shared_ptr<tr::optim::Adam > opt)
	{
		ini_opt(*opt);
	}

	inline void ini_opt(tr::optim::SGD& opt)
	{
		opt.zero_grad();
	}


	struct DevIns
	{
		static DevIns& Ins() {
			static DevIns ins;
			return ins;
		}

		torch::Device device;
		torch::Device device_gpu;
		torch::Device device_cpu;

		torch::Device Dev() {
			if (use_gpu_)
				return device_gpu;
			return device_cpu;
		}

		torch::Device dev() {
			return Dev();
		}

		void use_cpu() {
			use_gpu_ = false;
		}
		void use_gpu() {
			use_gpu_ = true;
		}

		bool checkIsCpu() const{
			return !use_gpu_;
		}
		bool checkIsGpu() const{
			return use_gpu_;
		}

	private:
		DevIns() :device_gpu(torch::kCUDA), device_cpu(torch::kCPU), device(torch::kCUDA) {
		}

	private:
		bool use_gpu_{false};
	};

	inline bool checkIsCPU(const TMat& m) {
		if (m.device().is_cpu())
			return true;
		return false;
	}
	inline bool checkIsGPU(const TMat& m) {
		if (m.device().is_cuda())
			return true;
		return false;
	}

	inline TMat to_dev(TMat tm) {
		return tm.to(DevIns::Ins().dev());
	}

	inline std::vector<TMat> to_dev(const std::vector<TMat>& tms)
	{
		std::vector<TMat> dev_tms(tms.size());
		for (int i = 0; i < tms.size(); i++) {
			dev_tms[i] = to_dev(tms[i]);
		}
		return dev_tms;
	}

	inline TMat to_cpu(TMat tm) {
		return tm.to(DevIns::Ins().device_cpu);
	}
	inline TMat to_gpu(TMat tm) {
		return tm.to(DevIns::Ins().device_gpu);
	}

	inline void to_dev_(TMat& tm) {
		tm = tm.to(DevIns::Ins().dev());
	}
	inline void to_cpu_(TMat& tm) {
		tm = tm.to(DevIns::Ins().device_cpu);
	}
	inline void to_gpu_(TMat& tm) {
		tm = tm.to(DevIns::Ins().device_gpu);
	}

	inline void to_dev_(std::vector<TMat>& tms) {
		for (auto& tm : tms) {
			to_dev_(tm);
		}
	}

	inline void to_dev_(std::vector<std::vector<TMat>>& tms_ay) {
		for (auto& tms : tms_ay) {
			to_dev_(tms);
		}
	}

	inline void to_cpu_(std::vector<TMat>& tms) {
		for (auto& tm : tms) {
			to_cpu_(tm);
		}
	}
	inline void to_gpu_(std::vector<TMat>& tms) {
		for (auto& tm : tms) {
			to_gpu_(tm);
		}
	}


	//---------------------
	template<typename _T>
	inline std::vector<TMat> combine_pars(const std::vector<TMat>& tms, const _T& t2)
	{
		std::vector<TMat> pars = tms;
		std::vector<TMat> pars_2 = t2.parameters();

		pars.insert(pars.end(), pars_2.begin(), pars_2.end());

		return pars;
	}



	inline std::vector<TMat> combine_pars(const std::vector<TMat>& tms
		, const std::vector<TMat>& tms2)
	{
		std::vector<TMat> pars = tms;
		std::vector<TMat> pars_2 = tms2;

		pars.insert(pars.end(), pars_2.begin(), pars_2.end());

		return pars;
	}

	inline std::vector<TMat> combine_pars(
		const std::vector<TMat>& tms1
		, const std::vector<TMat>& tms2
		, const std::vector<TMat>& tms3)
	{
		return combine_pars(combine_pars(tms1, tms2), tms3);
	}
	inline std::vector<TMat> combine_pars(
		const std::vector<TMat>& tms1
		, const std::vector<TMat>& tms2
		, const std::vector<TMat>& tms3
		, const std::vector<TMat>& tms4)
	{
		return combine_pars(combine_pars(tms1, tms2), combine_pars(tms3, tms4));
	}

	template<typename _T1, typename _T2>
	inline std::vector<TMat> combine_pars(const _T1& t1, const _T2& t2)
	{
		std::vector<TMat> pars = t1.parameters();
		std::vector<TMat> pars_2 = t2.parameters();

		pars.insert(pars.end(), pars_2.begin(), pars_2.end());

		return pars;
	}

	template<typename _T>
	inline std::vector<TMat> combine_pars(const _T& t1, const _T& t2, const _T& t3)
	{
		std::vector<TMat> pars = combine_pars(t1, t2);
		return combine_pars(pars, t3);
	}

	template<typename _T>
	inline std::vector<TMat> combine_pars(const _T& t1, const _T& t2, const _T& t3, const _T& t4)
	{
		return combine_pars(combine_pars(t1, t2), combine_pars(t3, t4));
	}

	inline std::vector<TMat> combine_pars(const std::vector<std::vector<TMat>>& tms_ay)
	{
		FT_IF(tms_ay.empty());
		std::vector<TMat> pars = tms_ay[0];

		for (int i = 1; i < tms_ay.size(); i++)
		{
			pars.insert(pars.end(), tms_ay[i].begin(), tms_ay[i].end());
		}

		return pars;
	}

	inline TMat pars_mean_sum(const std::vector<TMat>& pars)
	{
		if (pars.empty()) {
			LG_FT << "pars empty";
		}

		TMat v1 = pars[0].abs().mean();
		for (std::size_t i = 1; i < pars.size(); i++)
		{
			TMat v_tmp = pars[i].abs().mean();
			v1 = v1 + v_tmp.clone();
		}
		return v1;
	}

	inline TMat pars_norm_sum(const std::vector<TMat>& pars)
	{
		if (pars.empty()) {
			LG_FT << "pars empty";
		}

		TMat v1 = pars[0].norm();
		for (std::size_t i = 1; i < pars.size(); i++)
		{
			TMat v_tmp = pars[i].norm();
			v1 = v1 + v_tmp.clone();
		}
		return v1;
	}


	//---------------------------------
	inline double to_double(TMat _v)
	{
		TMat v = _v.reshape({ 1 });
		v = v.to(tr::kF64);
		v = to_cpu(v);
		return *v.data_ptr<double>();
	}

	inline float to_float(TMat _v)
	{
		TMat v = _v.reshape({ 1 });
		v = v.to(tr::kF32);
		v = to_cpu(v);
		return *v.data_ptr<float>();
	}

	inline int64_t to_int64_t(TMat _v)
	{
		TMat v = _v.reshape({ 1 });
		v = v.to(tr::kInt64);
		v = to_cpu(v);

		return *v.data_ptr<int64_t>();
	}


	inline TMat _clone(TMat in) {
		return in.clone();
	}

	inline std::vector<TMat> _clone(const std::vector<TMat>& ins)
	{
		std::vector<TMat> outs(ins.size());

		for (int i = 0; i < ins.size(); i++)
		{
			outs[i] = _clone(ins[i]);
		}

		return outs;
	}


	inline void to_64_(TMat& tm)
	{
		tm = tm.to(tr::kF64);
	}

	inline void to_64_(std::vector<TMat>& tms)
	{
		for (int i = 0; i < tms.size(); i++) {
			to_64_(tms[i]);
		}
	}


	inline void to_64_(std::vector<std::vector<TMat>>& tms_ay)
	{
		for (int i = 0; i < tms_ay.size(); i++) {
			to_64_(tms_ay[i]);
		}
	}





}//

