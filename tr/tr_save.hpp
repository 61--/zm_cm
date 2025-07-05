#pragma once


#include <string>
#include <vector>
#include "zm_file.hpp"


namespace zm
{
	namespace __tr_save_inner__ 
	{
		inline std::string genSuccessFlagName(const std::string& name)
		{
			return name + "_success";
		}

		inline void genSuccessFlag(const std::string& name)
		{
			std::string flag_name = genSuccessFlagName(name);
			zm::EnsureFile(flag_name);
		}
	}

	//------------------------------------------------
	
	template<typename _T>
	inline void _saveNN(_T& t, const std::string& dic)
	{
	
		zm::EnsureDic(dic);

		std::string path = zm::makeSubPath(dic, "x.net");

		tr::serialize::OutputArchive output_archive;
		t.save(output_archive);
		output_archive.save_to(path);

		__tr_save_inner__::genSuccessFlag(path);
	}

	template<typename _T>
	inline bool _loadNN(_T& t, const std::string& dic)
	{
		std::string path = zm::makeSubPath(dic, "x.net");

		std::string success_path = __tr_save_inner__::genSuccessFlagName(path);
		if (!bf::exists(bf::path(success_path)))
		{
			ER << "success path not exists";
			return false;
		}

		if (!bf::exists(bf::path(path))) {
			ER << "net not exist: " << path;
			return false;
		}

		tr::serialize::InputArchive archive;
		archive.load_from(path, zm::DevIns::Ins().dev());
		t.load(archive);
		return true;
	}


// 
// 	template<typename _T>
// 	inline void saveNN_byPar(_T& t, const std::string& dic)
// 	{
// 		zm::EnsureDic(dic);
// 		std::string path = zm::makeSubPath(dic, "x.net");
// 		std::vector<TMat> pars = t.parameters();
// 		tr::save(pars, path);
// 
// 		__tr_save_inner__::genSuccessFlag(path);
// 	}
// 
// 
// 	template<typename _T>
// 	inline bool loadNN_byPar(_T& t, const std::string& dic)
// 	{
// 		if (dic.empty())
// 			return false;
// 
// 		std::string path = zm::makeSubPath(dic, "x.net");
// 
// 		std::string success_path = __tr_save_inner__::genSuccessFlagName(path);
// 		if (!bf::exists(bf::path(success_path)))
// 		{
// 			ER << "success path not exists";
// 			return false;
// 		}
// 
// 		if (!bf::exists(bf::path(path))) {
// 			ER << "net not exist: " << path;
// 			return false;
// 		}
// 
// 		std::vector<TMat> pars_load;
// 		tr::load(pars_load, path);
// 
// 		std::vector<TMat> pars = t.parameters();
// 		if (pars.size() != pars_load.size()) {
// 			LG_FT << "par size not match";
// 		}
// 
// 		for (std::size_t i = 0; i < pars.size(); i++)
// 		{
// 			pars[i].set_data(pars_load[i]);
// 		}
// 
// 		return true;
// 	}



}//------