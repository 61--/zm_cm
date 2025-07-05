#pragma once

#include "_inner_tr_cm.hpp"
#include <boost/lexical_cast.hpp>
#include "zm_log.hpp"
#include "tr_mat.hpp"


namespace zm
{


	class MultiDenseLayer :public tr::nn::Module
	{
	public:

	public:
		MultiDenseLayer(const std::vector<int>& ns
			, Md_AC mid, Md_AC last);
		MultiDenseLayer(int nStart, int nEnd, Md_AC last);
		MultiDenseLayer();

		void ini(const std::vector<int>& ns
			, Md_AC mid, Md_AC last);
		void ini(const std::vector<int>& ns
			, const std::vector<Md_AC>& md);

		TMat forward(TMat m);
		TMat forward(TMat m, std::vector<TMat>& mid_vs);
		TMat op(TMat m) { return forward(m); }

	private:
		void _ini(const std::vector<int>& ns
			, Md_AC mid, Md_AC last);
		void _ini(const std::vector<int>& ns
			, const std::vector<Md_AC>& md);
		TMat _md(const TMat& m, Md_AC md);

	public:
		std::vector<
			boost::shared_ptr<tr::nn::Linear> > ls_;
		std::vector<Md_AC> mds_;
	};




	class ResMultiDenseLayer :public tr::nn::Module
	{
	public:
		ResMultiDenseLayer(int nStart, int nEnd, Md_AC last);
		ResMultiDenseLayer();

		void ini(const std::vector<int>& ns
			, Md_AC mid, Md_AC last);
		void ini(const std::vector<int>& ns
			, const std::vector<Md_AC>& md);

		TMat forward(TMat m, bool is_train = true);
		//TMat forward(TMat m, std::vector<TMat>& mid_vs);
		TMat op(TMat m) { return forward(m); }


	private:
		void _ini(const std::vector<int>& ns
			, Md_AC mid, Md_AC last);
		void _ini(const std::vector<int>& ns
			, const std::vector<Md_AC>& md);
		TMat _md(const TMat& m, Md_AC md);

	public:
		std::vector<
			boost::shared_ptr<tr::nn::Linear> > ls_;
		std::vector<Md_AC> mds_;
	};


	//-------------------------------------------------


	inline boost::shared_ptr<tr::nn::Linear> _createXavierLinear(
		int n_start, int n_end)
	{
		boost::shared_ptr<tr::nn::Linear> l(
			new tr::nn::Linear(n_start, n_end));

		torch::nn::init::xavier_normal_((*l)->weight);
		torch::nn::init::constant_((*l)->bias, 0.01);

		return l;
	}


	inline MultiDenseLayer::MultiDenseLayer(const std::vector<int>& ns
		, Md_AC mid, Md_AC last)
	{
		_ini(ns, mid, last);
	}

	inline MultiDenseLayer::MultiDenseLayer(int nStart, int nEnd, Md_AC last)
	{
		std::vector<int> ns = { nStart, nEnd };
		_ini(ns, md_none, last);
	}

	inline MultiDenseLayer::MultiDenseLayer()
	{

	}

	inline void MultiDenseLayer::ini(const std::vector<int>& ns
		, Md_AC mid, Md_AC last)
	{
		_ini(ns, mid, last);
	}

	inline void MultiDenseLayer::ini(const std::vector<int>& ns
		, const std::vector<Md_AC>& md)
	{
		_ini(ns, md);
	}

	inline TMat MultiDenseLayer::forward(TMat m)
	{
		FT_IF(ls_.empty());

		if (mds_.size() != ls_.size()) {
			LG_FT << "mds size: " << mds_.size()
				<< " - ls " << ls_.size();
			LG << "";
		}

		for (std::size_t i = 0; i < ls_.size(); i++)
		{
			m = (*ls_[i])->forward(m);
			m = _md(m, mds_[i]);
		}
		return m;
	}

	inline TMat MultiDenseLayer::forward(TMat m, std::vector<TMat>& mid_vs)
	{
		FT_IF(mds_.size() != ls_.size()) << "mds size: " << mds_.size()
			<< " - ls " << ls_.size();

		mid_vs.clear();
		for (std::size_t i = 0; i < ls_.size(); i++)
		{
			m = (*ls_[i])->forward(m);
			mid_vs.push_back(m);
			m = _md(m, mds_[i]);
		}
		return m;
	}

	inline void MultiDenseLayer::_ini(const std::vector<int>& ns
		, Md_AC mid, Md_AC last)
	{
		FT_IF(ns.size() <= 1);

		for (std::size_t i = 0; i < ns.size() - 1; i++)
		{
			int n_start = ns[i];
			int n_end = ns[i + 1];

			std::string name = "l" +
				boost::lexical_cast<std::string>(i);
// 			boost::shared_ptr<tr::nn::Linear> l(
// 				new tr::nn::Linear(n_start, n_end));

			auto l = _createXavierLinear(n_start, n_end);
			register_module(name, *l);

			ls_.push_back(l);
			if (i != ns.size() - 2)
				mds_.push_back(mid);
		}
		mds_.push_back(last);
	}

	inline void MultiDenseLayer::_ini(const std::vector<int>& ns
		, const std::vector<Md_AC>& md)
	{
		FT_IF(ns.size() <= 1);
		FT_IF(ns.size() - 1 != md.size());

		for (std::size_t i = 0; i < ns.size() - 1; i++)
		{
			int n_start = ns[i];
			int n_end = ns[i + 1];

			std::string name = "l" +
				boost::lexical_cast<std::string>(i);
// 			boost::shared_ptr<tr::nn::Linear> l(
// 				new tr::nn::Linear(n_start, n_end));

			auto l = _createXavierLinear(n_start, n_end);
			register_module(name, *l);

			ls_.push_back(l);
			//if (i != ns.size() - 2)
			//	mds_.push_back(mid);
		}
		mds_ = md;
		//mds_.push_back(last);
	}

	inline TMat MultiDenseLayer::_md(const TMat& m, Md_AC md)
	{
		switch (md)
		{
		case md_elu:
			return tr::elu(m);

		case md_tanh:
		case md_th:
			return tr::tanh(m);

		case md_sigmoid:
		case md_sg:
			return tr::sigmoid(m);

		case md_leaky_relu:
		case md_lk:
			return tr::leaky_relu(m);

		case md_relu:
			return tr::relu(m);

		case md_so_mx:
			return tr::softmax(m, 1);


		case md_none:
			return m;
		default:
			break;

		}
		LG_FT << "invalid md";
		return TMat();
	}





	inline ResMultiDenseLayer::ResMultiDenseLayer(int nStart, int nEnd, Md_AC last)
	{
		std::vector<int> ns = { nStart, nEnd };
		_ini(ns, md_none, last);
	}

	inline ResMultiDenseLayer::ResMultiDenseLayer()
	{

	}

	inline void ResMultiDenseLayer::ini(const std::vector<int>& ns
		, Md_AC mid, Md_AC last)
	{
		_ini(ns, mid, last);
	}

	inline void ResMultiDenseLayer::ini(const std::vector<int>& ns
		, const std::vector<Md_AC>& md)
	{
		_ini(ns, md);
	}

	inline TMat ResMultiDenseLayer::forward(TMat m, bool is_train)
	{
		FT_IF(mds_.size() != ls_.size()) << "mids size: " << mds_.size()
			<< " - ls " << ls_.size();
		FT_IF(ls_.empty());

		for (std::size_t i = 0; i < ls_.size(); i++)
		{
			m = (*ls_[i])->forward(m);

// 			if (i != ls_.size() - 1) {
// 				m = tr::dropout(m, 0.01, is_train);
// 			}

			m = _md(m, mds_[i]);
		}
		return m;
	}

// 	inline TMat ResMultiDenseLayer::forward(TMat m, std::vector<TMat>& mid_vs)
// 	{
// 		FT_IF(mds_.size() != ls_.size()) << "mds size: " << mds_.size()
// 			<< " - ls " << ls_.size();
// 		FT_IF(ls_.empty());
// 
// 		mid_vs.clear();
// 		for (std::size_t i = 0; i < ls_.size(); i++)
// 		{
// 			m = (*ls_[i])->forward(m);
// 			mid_vs.push_back(m);
// 			m = _md(m, mds_[i]);
// 		}
// 		return m;
// 	}



	inline void ResMultiDenseLayer::_ini(const std::vector<int>& ns
		, Md_AC mid, Md_AC last)
	{
		FT_IF(ns.size() <= 1);

		for (std::size_t i = 0; i < ns.size() - 1; i++)
		{
			int n_start = ns[i];
			int n_end = ns[i + 1];

			std::string name = "l" +
				boost::lexical_cast<std::string>(i);
// 			boost::shared_ptr<tr::nn::Linear> l(
// 				new tr::nn::Linear(n_start, n_end));
			
			auto l = _createXavierLinear(n_start, n_end);
			//torch::nn::init::xavier_normal_(l->weight);

			register_module(name, *l);

			ls_.push_back(l);
			if (i != ns.size() - 2)
				mds_.push_back(mid);
		}
		mds_.push_back(last);
	}

	inline void ResMultiDenseLayer::_ini(const std::vector<int>& ns
		, const std::vector<Md_AC>& md)
	{
		FT_IF(ns.size() <= 1);
		FT_IF(ns.size() - 1 != md.size());

		for (std::size_t i = 0; i < ns.size() - 1; i++)
		{
			int n_start = ns[i];
			int n_end = ns[i + 1];

			std::string name = "l" +
				boost::lexical_cast<std::string>(i);
// 			boost::shared_ptr<tr::nn::Linear> l(
// 				new tr::nn::Linear(n_start, n_end));

			auto l = _createXavierLinear(n_start, n_end);
			register_module(name, *l);

			ls_.push_back(l);
			//if (i != ns.size() - 2)
			//	mds_.push_back(mid);
		}
		mds_ = md;
		//mds_.push_back(last);
	}

	inline TMat ResMultiDenseLayer::_md(const TMat& m, Md_AC md)
	{
		switch (md)
		{
		case md_elu:
			return tr::elu(m);

		case md_tanh:
		case md_th:
			return tr::tanh(m);

		case md_sigmoid:
		case md_sg:
			return tr::sigmoid(m);

		case md_leaky_relu:
		case md_lk:
			return tr::leaky_relu(m);

		case md_relu:
			return tr::relu(m);

		case md_so_mx:
			return tr::softmax(m, 1);


		case md_none:
			return m;
		default:
			break;

		}
		LG_FT << "invalid md";
		return TMat();
	}


}