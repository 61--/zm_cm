#pragma once

#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include "zm_log.hpp"

namespace bf = boost::filesystem;


namespace zm
{

	inline std::string makeSubPath(const std::string& dic
		, const std::string& name)
	{
		bf::path p(dic);
		p /= name;

		return p.string();
	}

	inline std::string makeSubPath(const std::string& dic
		, int sub_idx)
	{
		std::string str_sub_idx = boost::lexical_cast<std::string>(sub_idx);
		return makeSubPath(dic, str_sub_idx);
	}

	inline std::string makeSubPath(const std::string& dic
		, const std::string& subDic
		, const std::string& name)
	{
		bf::path p(dic);
		p /= subDic;
		p /= name;

		return p.string();
	}

	inline std::string makeSubPath(const std::string& dic
		, const std::string& sub1
		, const std::string& sub2
		, const std::string& sub3)
	{
		return makeSubPath(makeSubPath(dic, sub1, sub2), sub3);
	}

	inline std::string makeSubPath(const std::string& dic
		, const std::string& sub1
		, const std::string& sub2
		, const std::string& sub3
		, const std::string& sub4)
	{
		return makeSubPath(makeSubPath(dic, sub1, sub2), sub3, sub4);
	}

	inline std::wstring makeSubPath(const std::wstring& dic
		, const std::wstring& name)
	{
		bf::path p(dic);
		p /= name;

		return p.wstring();
	}

	inline std::wstring makeSubPath(
		const std::wstring& dic
		, const std::wstring& subDic
		, const std::wstring& name)
	{
		bf::path p(dic);
		p /= subDic;
		p /= name;

		return p.wstring();
	}

	inline bool EnsureDic_bf(const bf::path& dic)
	{
		if (dic.empty())
			return true;

		bf::path p(dic);

		if (bf::is_directory(p) && bf::exists(p)) {
			return true;
		}
		try {
			bf::create_directories(p);
			return true;
		}
		catch (...) {

		}
		return false;
	}
	inline	bool EnsureDic(const std::string& dic)
	{
		return EnsureDic_bf(bf::path(dic));
	}


	inline bool EnsureFile(const std::string& name)
	{
		std::ofstream outfile(name);
		if (!outfile.is_open())
			return false;
		return true;
	}

	inline bool checkFileExist(const std::string& path)
	{
		return bf::exists(bf::path(path));
	}

	inline bool checkDicExist(const std::string& path)
	{
		return bf::exists(bf::path(path));
	}



	inline std::vector<std::string> getSubFiles(const std::string& dic)
	{
		if (!bf::exists(dic)) {
			return std::vector<std::string>();
		}
		std::vector<std::string> paths;
		bf::path p(dic);
		bf::directory_iterator end_it;
		for (bf::directory_iterator it(p); it != end_it; it++)
		{
			if (bf::is_directory(*it))
				continue;

			paths.push_back(it->path().string());
		}
		return paths;
	}

	inline std::vector<std::string> getSubDics(const std::string& dic)
	{
		std::vector<std::string> paths;
		bf::path p(dic);
		if (!bf::exists(p))
			return std::vector<std::string>();

		bf::directory_iterator end_it;
		for (bf::directory_iterator it(p); it != end_it; it++)
		{
			if (bf::is_directory(*it)) {
				paths.push_back(it->path().string());
			}
		}
		return paths;
	}

	inline std::vector<std::string> getSubDics_SortByNumbers(const std::string& dic)
	{
		
		bf::path p(dic);
		if (!bf::exists(p))
			return std::vector<std::string>();

		bf::directory_iterator end_it;
		
		std::vector<std::string> dic_names;
		for (bf::directory_iterator it(p); it != end_it; it++)
		{
			if (bf::is_directory(*it)) 
			{
				dic_names.push_back(it->path().filename().string());
			}
		}

		std::sort(dic_names.begin(), dic_names.end(), 
			[](const std::string& str0, const std::string& str1)->bool {
				double d0 = boost::lexical_cast<double>(str0);
				double d1 = boost::lexical_cast<double>(str1);
				return d0 < d1;
			});

		std::vector<std::string> paths;
		for (auto dic_name : dic_names) {
			paths.push_back(makeSubPath(dic, dic_name));
		}

		return paths;
	}

	inline bool CheckIsImgType(const std::string& path)
	{
		if (path.size() <= 4)
			return false;
		int pos = (int)path.find_last_of(".");
		if (pos == -1)
			return false;
		std::string ext = path.substr(pos, path.size());
		if (boost::iequals(ext, ".jpg")
			|| boost::iequals(ext, ".bmp")
			|| boost::iequals(ext, ".png")
			|| boost::iequals(ext, ".jpeg")
			)
		{
			return true;
		}
		return false;
	}

	inline	std::vector<std::string> getSubImgFiles(const std::string& dic)
	{
		bf::directory_iterator end_it;

		bf::path p(dic);

		if (!bf::exists(p)) {
			ER << "dic not exist: " << dic;
			return std::vector<std::string>();
		}

		std::vector<std::string> paths;
		bf::directory_iterator it;
		if (p.empty())
			it = bf::directory_iterator(bf::current_path());
		else
			it = bf::directory_iterator(p);

		for (; it != end_it; it++)
		{
			if (!bf::is_directory(*it) && CheckIsImgType(it->path().string()))
			{
				bool valid = true;
				std::string name = it->path().filename().string();
				//std::cout << "name = " << name << std::endl;
				if (name.size() > 2)
				{
					if (name[0] == '.' && name[1] == '_')
					{
						valid = false;
						//std::cout << "name = " << name <<std::endl;
					}
				}
				if (valid)
					paths.push_back(it->path().string());
			}
		}
		return paths;
	}


	inline std::vector<std::string> IdxSortFileNames(const std::vector<std::string>& sub_files)
	{
		struct Item {
			int idx;
			std::string path;
		};

		std::vector<Item> items;
		for (auto file : sub_files)
		{
			std::string name = bf::path(file).stem().string();
			try {
				int idx = boost::lexical_cast<int>(name);
				Item item;
				item.idx = idx;
				item.path = file;
				items.push_back(item);
			}
			catch (...) {

			}
		}

		std::sort(items.begin(), items.end(),
			[](Item i1, Item i2) ->bool {

				return i1.idx < i2.idx;
			});

		std::vector<std::string> files;
		for (auto item : items) {
			files.push_back(item.path);
		}
		return files;
	}


	inline std::string readFile(const std::string& path)
	{
		std::ifstream inFile;
		inFile.open(path);

		std::stringstream strStream;
		strStream << inFile.rdbuf();
		std::string str = strStream.str();
		return str;
	}


}//