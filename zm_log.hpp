#ifndef __ZM_LOG_HPP__
#define __ZM_LOG_HPP__

//#define LOG_USE_BOOST
//#define LOG_USE_OPENCV
//#define LOG_USE_EIGEN

#include "lg/zm_log_core.h"


#include "lg/system_adpter.hpp" 

#ifdef LOG_USE_OPENCV
#include <opencv2/opencv.hpp>
#endif


#ifdef LOG_USE_BOOST
#include <boost/unordered_set.hpp>
#endif


namespace __zm_log_ext_private{
}


inline std::ostream& operator<<(std::ostream& ss, const std::vector<unsigned char>& ay)
{
    ss<<"[";
    for(std::size_t i = 0; i< ay.size(); i++){
        ss<<(int)(ay[i]);
        if(i!=ay.size()-1)
            ss<<",";
    }
    ss<<"]";
    return ss;
}




#ifdef LOG_USE_BOOST


template<typename _VType, typename _HashType, typename _PType, typename _Alloc>
std::ostream& operator<<(std::ostream& ss
	, const boost::unordered_set<_VType, _HashType, _PType, _Alloc>& s);


template<typename _VType, typename _HashType, typename _PType, typename _Alloc>
std::ostream& operator<<(std::ostream& ss
	, const boost::unordered_set<_VType, _HashType, _PType, _Alloc>& s)
{
	ss<<"(";
	for(auto it=s.begin(); it!=s.end(); it++)
	{
		ss<<*it<<", ";
	}
	ss<<")";
	return ss;
}

#endif


#ifdef LOG_USE_OPENCV

std::ostream& operator<<(std::ostream& ss, const cv::KeyPoint& kpt);


inline std::ostream& operator<<(std::ostream& ss, const cv::KeyPoint& kpt)
{
	ss<<"{pt:("<<kpt.pt.x<<", "<<kpt.pt.y<<"),oct:"<<kpt.octave<<"}";
	return ss;
}


#endif



#ifdef LOG_USE_EIGEN



template<typename _T, int _N1, int _N2>
inline std::ostream& operator<<(std::ostream& ss, Eigen::Matrix<_T, _N1, _N2> m);
//template<class _T>
//inline std::ostream& operator<<(std::ostream& ss, const Eigen::Quaternion<_T>& q);




template<typename _T, int _N1, int _N2>
inline std::ostream& operator<<(std::ostream& ss, Eigen::Matrix<_T,_N1,_N2> m)
{
	int rows = m.rows();
	int cols = m.cols();
	if(_N2 == 1){
		ss<<"(";
		for(int i = 0; i< rows; i++){
			if(i == rows - 1)
				ss<<m(i);
			else
				ss<<m(i)<<",";
		}
		ss<<")";
	}
	else if(_N1 == 1){
		ss<<"(";
		for(int i = 0; i< cols; i++){
			if(i == cols - 1)
				ss<<m(i);
			else
				ss<<m(i)<<",";
		}
		ss<<")";
	}
	else{
		for(int i = 0; i< rows; i++){
			for(int j = 0; j< cols; j++){
				if(j == cols -1)
					ss<<m(i,j)<<";";
				else
					ss<<m(i,j)<<", ";
			}
			ss<<std::endl;
		}
	}
	return ss;
}

inline std::ostream& operator<<(std::ostream& ss
		, const Eigen::Vector2d& v2)
{
	ss<<"("<<v2(0)<<", "<< v2(1)<<")";
	return ss;
}

template<typename _T>
inline std::ostream& operator<<(std::ostream& ss
		,const Eigen::Quaternion<_T>& q)
{
	ss<<"["<<q.w()<<";"<<q.x()<<","<<q.y()<<","<<q.z()<<"]";
	return ss;
}


namespace cpplog
{

	template<typename _T>
	inline cpplog::My_ostream& operator<<(cpplog::My_ostream& ss
		, const Eigen::Quaternion<_T>& q)
	{
		ss << "[" << q.w() << ";" << q.x() << "," << q.y() << "," << q.z() << "]";
		return ss;
	}
}



#endif












#endif
