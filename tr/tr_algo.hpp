#pragma once

#include "tr_mat.hpp"


namespace zm
{


	inline TMat maxVal(const std::vector<TMat>& vals)
	{
		FT_IF(vals.empty());

		if (vals.size() == 1)
			return vals[0];

		TMat ret = vals[0];
		for (int i = 1; i < vals.size(); i++) {
			ret = tr::maximum(ret, vals[i]);
		}
		return ret;
	}

	inline TMat meanVal(const std::vector<TMat>& vals)
	{
		FT_IF(vals.empty());

		if (vals.size() == 1)
			return vals[0];

		TMat ret = vals[0];
		for (int i = 1; i < vals.size(); i++) {
			ret += vals[i];
		}
		ret /= vals.size();
		return ret;
	}


	inline void minValIdx(const std::vector<TMat>& vals
		, const std::vector<TMat>& valids
		, TMat& out_val
		, TMat& out_idx)
	{
		FT_IF(vals.empty());
		FT_IF(vals.size() != valids.size());

		TMat min_val = 1.0 / (tr::zeros_like(vals[0]) + 1e-12);
		TMat idx = -1 * zm::to_dev(zm::createOneTMat({ vals[0].size(0),1 }, tr::kInt32));

		for (int i = 0; i < vals.size(); i++)
		{
			TMat cond = (min_val <= vals[i]);

			TMat idx_i = i * zm::to_dev(zm::createOneTMat({ vals[0].size(0),1 }, tr::kInt32));

			idx_i = tr::where(cond, idx, idx_i);
			TMat tmp_min_val = tr::where(cond, min_val, vals[i]);

			idx = tr::where(valids[i] > 0.5, idx_i, idx);
			min_val = tr::where(valids[i] > 0.5, tmp_min_val, min_val);
		}


		out_val = min_val;
		out_idx = idx;
	}



	inline void maxValIdx(const std::vector<TMat>& vals
		, const std::vector<TMat>& valids
		, TMat& out_val
		, TMat& out_idx)
	{
		FT_IF(vals.empty());
		FT_IF(vals.size() != valids.size());

		TMat max_val = -1.0 / (tr::zeros_like(vals[0]) + 1e-12);
		TMat idx = -1 * zm::to_dev(zm::createOneTMat({ vals[0].size(0),1 }, tr::kInt32));

		for (int i = 0; i < vals.size(); i++)
		{
			TMat cond = (max_val >= vals[i]);

			TMat idx_i = i * zm::to_dev(zm::createOneTMat({ vals[0].size(0),1 }, tr::kInt32));

			idx_i = tr::where(cond, idx, idx_i);
			TMat tmp_max_val = tr::where(cond, max_val, vals[i]);

			idx = tr::where(valids[i] > 0.5, idx_i, idx);
			max_val = tr::where(valids[i] > 0.5, tmp_max_val, max_val);
		}


		out_val = max_val;
		out_idx = idx;
	}





}