#pragma once
#ifdef __USE_CV__
#include <opencv2/opencv.hpp>
#endif

#include "zm_log.hpp"
//#include "zm_cv.h"
#include "2/json.hpp"

#define __USE_EIGEN__

#ifdef __USE_EIGEN__
#include <Eigen/Eigen>
#endif

namespace zm{
	
	using json = nlohmann::json;
	using Json = nlohmann::json;
	//typedef json Json;

	//class ZmJson:public nlohmann::json{};

//#define Json nlohmann::json
	//class Json:public nlohmann::json{};
}//

#ifdef __USE_EIGEN__
//namespace zm
//{
namespace Eigen
{

	inline void to_json(zm::Json& j
		, const Eigen::MatrixXf& m)
	{
		int col = m.cols();
		int row = m.rows();

		std::vector<float> ays;
		ays.reserve(col * row);

		for (int i0 = 0; i0 < row; i0++)
		{
			for (int i1 = 0; i1 < col; i1++)
			{
				ays.push_back(m(i0, i1));
			}
		}

		j = zm::json{
			{"c", col},
			{"r", row},
			{"t","f"},
			{"dt", ays}
		};
	}
	inline void from_json(const zm::Json& j
		, Eigen::MatrixXf& m)
	{
		std::vector<float> ays = j.at("dt").get<
			std::vector<float> >();

		int col = j.at("c").get<int>();
		int row = j.at("r").get<int>();
		std::string tp = j.at("t").get<std::string>();

		FT_IF(tp != "f");

		m = Eigen::MatrixXf(row, col);

		for (int i0 = 0; i0 < row; i0++)
		{
			for (int i1 = 0; i1 < col; i1++)
			{
				m(i0, i1) = ays[i0 * col + i1];
			}
		}
	}

}

//}
#endif



#ifdef __USE_CV__
namespace cv{
	using namespace zm;
	//using namespace zm::nlohmann;
	
	template<typename _T>
	void to_json(Json& j, const Point_<_T>& pt);

	template<typename _T>
	void from_json(const Json& j, Point_<_T>& pt);

	template<typename _T>
	void to_json(Json& j, const Point3_<_T>& pt);
	template<typename _T>
	void from_json(const Json& j, Point3_<_T>& pt);

	template<typename _T>
	void to_json(Json& j, const Vec<_T,3>& v3);
	template<typename _T, int _N>
	void from_json(const Json& j, Vec<_T,_N>& vs);

	void to_json(Json& j, const cv::Scalar& c);
	void from_json(const Json& j, cv::Scalar& c);

}//


namespace cv{
	using namespace zm;
	//using namespace zm::nlohmann;

	template<typename _T>
	inline void to_json(Json& j, const Rect_<_T>& r)
	{
		j = Json{
			{"x", r.x},
			{"y", r.y},
			{ "w",r.width },
			{ "h",r.height },
		};
	}
	template<typename _T>
	inline void from_json(const Json& j, Rect_<_T>& r)
	{
		r.x = j.at("x").get<_T>();
		r.y = j.at("y").get<_T>();
		r.width = j.at("w").get<_T>();
		r.height = j.at("h").get<_T>();
	}


	template<typename _T>
	inline void to_json(Json& j, const Size_<_T>& sz)
	{
		j = Json{
			{ "w",sz.width },{ "h",sz.height }
		};
	}
	template<typename _T>
	inline void from_json(const Json& j, Size_<_T>& sz)
	{
		sz.width = j.at("w").get<_T>();
		sz.height = j.at("h").get<_T>();
	}
	
	template<typename _T>
	inline void to_json(Json& j, const Point_<_T>& pt)
	{
		j = Json{
			{"x",pt.x},{"y",pt.y}
		};
	}
	template<typename _T>
	inline void from_json(const Json& j, Point_<_T>& pt)
	{
		pt.x = j.at("x").get<_T>();
		pt.y = j.at("y").get<_T>();
	}

	template<typename _T>
	inline void to_json(Json& j, const Point3_<_T>& pt)
	{
		j = Json{
			{"x",pt.x},{"y",pt.y}, {"z", pt.z}
		};
	}
	template<typename _T>
	inline void from_json(const Json& j, Point3_<_T>& pt)
	{
		pt.x = j.at("x").get<_T>();
		pt.y = j.at("y").get<_T>();
		pt.z = j.at("z").get<_T>();
	}
	

	template<typename _T>
	inline void to_json(Json& j, const Vec<_T,3>& v3)
	{
		_T ay[]={v3[0],v3[1],v3[2]};
		//j = json{
		//	{"v3",ay}
		//};
		j = Json(ay);
	}

	template<typename _T, int _N>
	inline void from_json(const Json& j, Vec<_T,_N>& vs)
	{
		std::vector<_T> ay= j;

		if(_N != (int)ay.size())
		{
			ER<<"invlaid ay size: "<<ay.size();
			throw 0;
		}
		for(int i = 0; i< _N; i++)
		{
			vs[i] = ay[i];
		}
	}

	inline void to_json(Json& j, const cv::Scalar& c)
	{
		j = Json(c.val);
	}
	inline void from_json(const zm::json& j, cv::Scalar& c)
	{
		std::vector<double> ay = j;
		if(ay.size() != 4){
			ER<<"invalid ay sz: "<<ay.size();
			throw 0;
		}

		for(int i = 0; i< 4; i++)
			c.val[i] = ay[i];
	}

	template<typename _T>
	inline void _to_json_data(Json& j
		, const cv::Mat& m)
	{
		std::vector<_T> ays;
		ays.reserve(m.rows * m.cols);
		for(int j=0; j<m.rows; j++)
		{
			for(int i=0; i<m.cols; i++)
			{
				ays.push_back(m.at<_T>(j,i));	
			}	
		}
		int type = m.type();
		cv::Size sz = m.size();

		j = zm::json{
			{"sz", sz},
			{"tp", type},
			{"dt", ays}
		};
	}

	template<typename _T>
	inline void _from_json(const Json& j
			, cv::Mat& m, int type)
	{
		std::vector<_T> ays = j.at("dt").get<
			std::vector<_T> >();
		cv::Size sz = j.at("sz").get<cv::Size>();
		m = cv::Mat(sz, type);
		
		int idx = 0;
		for(int j=0; j<m.rows; j++)
		{
			for(int i=0; i<m.cols; i++)
			{
				m.at<_T>(j,i) = ays[idx++];
			}	
		}
	}

#ifdef __USE_ZM_CV__

	inline void to_json(Json& j
		, const cv::Mat& m)
	{
		int type = m.type();
		if(type == CV_8U)
			_to_json_data<uchar>(j,m);
		else if(type ==CV_8UC3)
			_to_json_data<cv::Vec3b>(j,m);
		else if(type == CV_64F)
			_to_json_data<double>(j,m);
		else{
			LG_FT<<"unsupport m type:"<<_str_Mat_type(type);
		}
	}
	inline void from_json(const Json& j
			, cv::Mat& m)
	{
		int type = j.at("tp").get<int>();
		
		if(type == CV_8U)
			_from_json<uchar>(j, m, type);
		else if(type == CV_8UC3)
			_from_json<cv::Vec3b>(j, m, type);
		else if(type == CV_64F)
			_from_json<double>(j, m, type);
		else
			LG_FT<<"unsupport m type"<<_str_Mat_type(type);
	}

#endif
	
}

#endif

namespace zm
{
	Json loadJsonOrThrow(const std::string& name);
	bool loadJson(const std::string& name, Json& j);
	
	bool saveJson(const std::string& name, const Json& s, int align=4);
	void saveJsonOrThrow(const std::string& name, const Json& j, int align=4);

	bool load(const std::string& name, Json& j);
	bool save(const std::string& name, const Json& j);

	template<typename _T>
	inline _T loadJsonDataOrThrow(const std::string& name){
		Json js = loadJsonOrThrow(name);
		_T t = js;
		return t;
	}

	template<typename _T>
	bool loadJsonData(const std::string& name, _T& t){
		Json j;
		if(!load(name, j))
			return false;

		t = j;
		return true;
	}
	template<typename _T>
	bool saveJsonData(const std::string& name, const _T& t) {
		Json j = t;
		if (!save(name, j))
			return false;
		return true;
	}

	template<typename _T>
	inline std::string _to_JsonStr(const _T& t)
	{
		Json j = t;
		return j.dump();
	}


	template<typename _T>
	inline _T _from_JsonStr(const std::string& str)
	{
		Json j =  Json::parse(str);
		_T t = j;
		return t;
	}

//--------------

#if 0
	inline void dbg_makeJsonSupportTxtCode(
		const std::string& name
		, int max)
	{	
		std::ofstream f(name);
		auto ni = [](int i)->std::string{
			return "n" + boost::lexical_cast<std::string>(i);
		};

		for(int i=0; i< max; i++)
		{
			std::string line;
			line += "#define ZM_JSON_SPT_" 
				+ boost::lexical_cast<std::string>(i+1) + "(st";
			for(int j = 0; j<=i; j++){
				line +=" ," + ni(j);	
			}
			line += ")  inline void to_json(json& j, const st& data) { j = json{";
			for(int j = 0; j<=i; j++){
				line += "{__ZM_JS_STR(" + ni(j) + "), data."+ ni(j) + "},";
			}
			line += "}; } ";

			line += "inline void from_json(const json& j, st& data) {";
			for(int j=0; j<=i; j++){
				line += "data." + ni(j) + "=j.at(__ZM_JS_STR("+ni(j)+ ") ).get<decltype(data." + ni(j) + ")>();";
			}
			line+= "}";

			line +="\r\n";	


			LG<<"line: "<<line;
			f<<line;
		}
	}
#endif


	#define __ZM_JS_STR(v) (#v)




#define ZM_JSON_SPT_1(st ,n0)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();}
#define ZM_JSON_SPT_2(st ,n0 ,n1)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();}
#define ZM_JSON_SPT_3(st ,n0 ,n1 ,n2)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();}
#define ZM_JSON_SPT_4(st ,n0 ,n1 ,n2 ,n3)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();}
#define ZM_JSON_SPT_5(st ,n0 ,n1 ,n2 ,n3 ,n4)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();}
#define ZM_JSON_SPT_6(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();}
#define ZM_JSON_SPT_7(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();}
#define ZM_JSON_SPT_8(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();}
#define ZM_JSON_SPT_9(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();}
#define ZM_JSON_SPT_10(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();}
#define ZM_JSON_SPT_11(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();}
#define ZM_JSON_SPT_12(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();}
#define ZM_JSON_SPT_13(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();}
#define ZM_JSON_SPT_14(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();}
#define ZM_JSON_SPT_15(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();}
#define ZM_JSON_SPT_16(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();}
#define ZM_JSON_SPT_17(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();}
#define ZM_JSON_SPT_18(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();}
#define ZM_JSON_SPT_19(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();}
#define ZM_JSON_SPT_20(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();}
#define ZM_JSON_SPT_21(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();}
#define ZM_JSON_SPT_22(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();}
#define ZM_JSON_SPT_23(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();}
#define ZM_JSON_SPT_24(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();}
#define ZM_JSON_SPT_25(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23 ,n24)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},{__ZM_JS_STR(n24), data.n24},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();data.n24=j.at(__ZM_JS_STR(n24) ).get<decltype(data.n24)>();}
#define ZM_JSON_SPT_26(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23 ,n24 ,n25)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},{__ZM_JS_STR(n24), data.n24},{__ZM_JS_STR(n25), data.n25},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();data.n24=j.at(__ZM_JS_STR(n24) ).get<decltype(data.n24)>();data.n25=j.at(__ZM_JS_STR(n25) ).get<decltype(data.n25)>();}
#define ZM_JSON_SPT_27(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23 ,n24 ,n25 ,n26)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},{__ZM_JS_STR(n24), data.n24},{__ZM_JS_STR(n25), data.n25},{__ZM_JS_STR(n26), data.n26},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();data.n24=j.at(__ZM_JS_STR(n24) ).get<decltype(data.n24)>();data.n25=j.at(__ZM_JS_STR(n25) ).get<decltype(data.n25)>();data.n26=j.at(__ZM_JS_STR(n26) ).get<decltype(data.n26)>();}
#define ZM_JSON_SPT_28(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23 ,n24 ,n25 ,n26 ,n27)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},{__ZM_JS_STR(n24), data.n24},{__ZM_JS_STR(n25), data.n25},{__ZM_JS_STR(n26), data.n26},{__ZM_JS_STR(n27), data.n27},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();data.n24=j.at(__ZM_JS_STR(n24) ).get<decltype(data.n24)>();data.n25=j.at(__ZM_JS_STR(n25) ).get<decltype(data.n25)>();data.n26=j.at(__ZM_JS_STR(n26) ).get<decltype(data.n26)>();data.n27=j.at(__ZM_JS_STR(n27) ).get<decltype(data.n27)>();}
#define ZM_JSON_SPT_29(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23 ,n24 ,n25 ,n26 ,n27 ,n28)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},{__ZM_JS_STR(n24), data.n24},{__ZM_JS_STR(n25), data.n25},{__ZM_JS_STR(n26), data.n26},{__ZM_JS_STR(n27), data.n27},{__ZM_JS_STR(n28), data.n28},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();data.n24=j.at(__ZM_JS_STR(n24) ).get<decltype(data.n24)>();data.n25=j.at(__ZM_JS_STR(n25) ).get<decltype(data.n25)>();data.n26=j.at(__ZM_JS_STR(n26) ).get<decltype(data.n26)>();data.n27=j.at(__ZM_JS_STR(n27) ).get<decltype(data.n27)>();data.n28=j.at(__ZM_JS_STR(n28) ).get<decltype(data.n28)>();}
#define ZM_JSON_SPT_30(st ,n0 ,n1 ,n2 ,n3 ,n4 ,n5 ,n6 ,n7 ,n8 ,n9 ,n10 ,n11 ,n12 ,n13 ,n14 ,n15 ,n16 ,n17 ,n18 ,n19 ,n20 ,n21 ,n22 ,n23 ,n24 ,n25 ,n26 ,n27 ,n28 ,n29)  inline void to_json(json& j, const st& data) { j = json{{__ZM_JS_STR(n0), data.n0},{__ZM_JS_STR(n1), data.n1},{__ZM_JS_STR(n2), data.n2},{__ZM_JS_STR(n3), data.n3},{__ZM_JS_STR(n4), data.n4},{__ZM_JS_STR(n5), data.n5},{__ZM_JS_STR(n6), data.n6},{__ZM_JS_STR(n7), data.n7},{__ZM_JS_STR(n8), data.n8},{__ZM_JS_STR(n9), data.n9},{__ZM_JS_STR(n10), data.n10},{__ZM_JS_STR(n11), data.n11},{__ZM_JS_STR(n12), data.n12},{__ZM_JS_STR(n13), data.n13},{__ZM_JS_STR(n14), data.n14},{__ZM_JS_STR(n15), data.n15},{__ZM_JS_STR(n16), data.n16},{__ZM_JS_STR(n17), data.n17},{__ZM_JS_STR(n18), data.n18},{__ZM_JS_STR(n19), data.n19},{__ZM_JS_STR(n20), data.n20},{__ZM_JS_STR(n21), data.n21},{__ZM_JS_STR(n22), data.n22},{__ZM_JS_STR(n23), data.n23},{__ZM_JS_STR(n24), data.n24},{__ZM_JS_STR(n25), data.n25},{__ZM_JS_STR(n26), data.n26},{__ZM_JS_STR(n27), data.n27},{__ZM_JS_STR(n28), data.n28},{__ZM_JS_STR(n29), data.n29},}; } inline void from_json(const json& j, st& data) {data.n0=j.at(__ZM_JS_STR(n0) ).get<decltype(data.n0)>();data.n1=j.at(__ZM_JS_STR(n1) ).get<decltype(data.n1)>();data.n2=j.at(__ZM_JS_STR(n2) ).get<decltype(data.n2)>();data.n3=j.at(__ZM_JS_STR(n3) ).get<decltype(data.n3)>();data.n4=j.at(__ZM_JS_STR(n4) ).get<decltype(data.n4)>();data.n5=j.at(__ZM_JS_STR(n5) ).get<decltype(data.n5)>();data.n6=j.at(__ZM_JS_STR(n6) ).get<decltype(data.n6)>();data.n7=j.at(__ZM_JS_STR(n7) ).get<decltype(data.n7)>();data.n8=j.at(__ZM_JS_STR(n8) ).get<decltype(data.n8)>();data.n9=j.at(__ZM_JS_STR(n9) ).get<decltype(data.n9)>();data.n10=j.at(__ZM_JS_STR(n10) ).get<decltype(data.n10)>();data.n11=j.at(__ZM_JS_STR(n11) ).get<decltype(data.n11)>();data.n12=j.at(__ZM_JS_STR(n12) ).get<decltype(data.n12)>();data.n13=j.at(__ZM_JS_STR(n13) ).get<decltype(data.n13)>();data.n14=j.at(__ZM_JS_STR(n14) ).get<decltype(data.n14)>();data.n15=j.at(__ZM_JS_STR(n15) ).get<decltype(data.n15)>();data.n16=j.at(__ZM_JS_STR(n16) ).get<decltype(data.n16)>();data.n17=j.at(__ZM_JS_STR(n17) ).get<decltype(data.n17)>();data.n18=j.at(__ZM_JS_STR(n18) ).get<decltype(data.n18)>();data.n19=j.at(__ZM_JS_STR(n19) ).get<decltype(data.n19)>();data.n20=j.at(__ZM_JS_STR(n20) ).get<decltype(data.n20)>();data.n21=j.at(__ZM_JS_STR(n21) ).get<decltype(data.n21)>();data.n22=j.at(__ZM_JS_STR(n22) ).get<decltype(data.n22)>();data.n23=j.at(__ZM_JS_STR(n23) ).get<decltype(data.n23)>();data.n24=j.at(__ZM_JS_STR(n24) ).get<decltype(data.n24)>();data.n25=j.at(__ZM_JS_STR(n25) ).get<decltype(data.n25)>();data.n26=j.at(__ZM_JS_STR(n26) ).get<decltype(data.n26)>();data.n27=j.at(__ZM_JS_STR(n27) ).get<decltype(data.n27)>();data.n28=j.at(__ZM_JS_STR(n28) ).get<decltype(data.n28)>();data.n29=j.at(__ZM_JS_STR(n29) ).get<decltype(data.n29)>();}



}//




//====================================




namespace zm
{
	inline bool loadJson(const std::string& name, json& j)
	{
		std::ifstream f(name);
		if(!f.is_open())
		{
			ER<<"load json failed: open file : "<<name;
			return false;
		}

		f>>j;
		return true;
	}

	inline json loadJsonOrThrow(const std::string& name)
	{
		json j;
		if(!loadJson(name, j))
		{
			ER<<"load json failed throw : "<<name;
			throw 0;
		}
		return j;
		/*
		std::ifstream f(name);
		if(!f.is_open())
		{
			ER<<"load json failed: open file : "<<name;
			throw 0;
		}

		json j;
		f>>j;
		return j;
		*/
	}

	inline bool saveJson(const std::string& name, const json& s, int align)
	{
		std::ofstream f(name);
		if(!f.is_open())
		{
			return false;
		}
		//f<<s.dump(4);
		f<<s.dump(align);
		return true;
	}

	inline void saveJsonOrThrow(const std::string& name
		, const json& j, int align)
	{
		if(!saveJson(name, j, align)){
			ER<<"save json failed: "<<name;
			throw 0;
		}
	}

	inline bool load(const std::string& name, json& j)
	{
		return loadJson(name, j);
	}
	
	inline bool save(const std::string& name, const json& j)
	{
		return saveJson(name, j);
	}

}//




