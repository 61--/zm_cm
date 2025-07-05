#ifndef __ZM_LOG__CORE_HPP__
#define __ZM_LOG__CORE_HPP__



#undef LG
#undef ER

#undef LG_FT
#undef LG_IF
#undef FT_IF


#define CPPLOG_FILTER_LEVEL LL_TRACE

#include "algo_log_private.hpp"

#include <map>
#include <set>




#define LG ZM_LOG_INFO(glog)
#define ER ZM_LOG_ERROR(glog)
#define LG_FT ZM_LOG_FATAL(glog)

#define _LG_IF(v) ZM_LOG_IF(ZM_LL_INFO, glog, v)
#define _FT_IF(v) ZM_LOG_IF(ZM_LL_FATAL, glog, v)

//#define _DLG_IF(v) ZM_DLOG_IF(ZM_LL_INFO, glog, v)
//#define _DFT_IF(v) ZM_DLOG_IF(ZM_LL_FATAL, glog, v)


#define LG_IF(v) _LG_IF((v))
#define FT_IF(v) _FT_IF((v))

#ifdef _DEBUG
#define DLG_IF(v) LG_IF((v))
#define DFT_IF(v) FT_IF((v))
#else
#define DLG_IF(v) while(false) LG_IF((v))
#define DFT_IF(v) while(false) FT_IF((v))
#endif


#define _LG_CK(v) FT_IF(!v)
#define LG_CK(v) _LG_CK((v))


#ifdef _DEBUG
#define LG_DBG false ? (void)0 : cpplog::helpers::VoidStreamClass() & ZM_LOG_INFO(glog)
#else
#define LG_DBG true ? (void)0 : cpplog::helpers::VoidStreamClass() & ZM_LOG_INFO(glog)
#endif


//=======================
//===============


#define ZM_CK(condition) ZM_CHECK(glog, condition)
#define ZM_CK_EQUAL(ex1, ex2) ZM_CHECK_EQUAL(glog, ex1, ex2)
#define ZM_CK_LT(ex1, ex2) ZM_CHECK_LT(glog, ex1, ex2)
#define ZM_CK_GT(ex1, ex2) ZM_CHECK_GT(glog, ex1, ex2)
#define ZM_CK_LE(ex1, ex2) ZM_CHECK_LE(glog, ex1, ex2)
#define ZM_CK_GE(ex1, ex2) ZM_CHECK_GE(glog, ex1, ex2)

#define ZM_CK_NE(ex1, ex2) ZM_CHECK_NE(glog, ex1, ex2)
#define ZM_CK_NOT_EQUAL(ex1, ex2) ZM_CHECK_NOT_EQUAL(glog, ex1, ex2)
#define ZM_CK_STREQ(s1, s2) ZM_CHECK_STREQ(glog, s1, s2)
#define ZM_CK_STRNE(s1, s2) ZM_CHECK_STRNE(glog, s1, s2)
#define ZM_CK_NULL(exp) ZM_CHECK_NULL(glog, exp) 
#define ZM_CK_NOT_NULL(exp) ZM_CHECK_NOT_NULL(glog, exp)



#define ZM_DCK(condition) ZM_DCHECK(glog, condition)
#define ZM_DCK_EQUAL(ex1, ex2) ZM_DCHECK_EQUAL(glog, ex1, ex2)
#define ZM_DCK_LT(ex1, ex2) ZM_DCHECK_LT(glog, ex1, ex2)
#define ZM_DCK_GT(ex1, ex2) ZM_DCHECK_GT(glog, ex1, ex2)
#define ZM_DCK_LE(ex1, ex2) ZM_DCHECK_LE(glog, ex1, ex2)
#define ZM_DCK_GE(ex1, ex2) ZM_DCHECK_GE(glog, ex1, ex2)

#define ZM_DCK_NE(ex1, ex2) ZM_DCHECK_NE(glog, ex1, ex2)
#define ZM_DCK_NOT_EQUAL(ex1, ex2) ZM_DCHECK_NOT_EQUAL(glog, ex1, ex2)
#define ZM_DCK_STREQ(s1, s2) ZM_DCHECK_STREQ(glog, s1, s2)
#define ZM_DCK_STRNE(s1, s2) ZM_DCHECK_STRNE(glog, s1, s2)
#define ZM_DCK_NULL(exp) ZM_DCHECK_NULL(glog, exp) 
#define ZM_DCK_NOT_NULL(exp) ZM_DCHECK_NOT_NULL(glog, exp)





//=====================================



template<class _T1, class _T2>
cpplog::My_ostream& operator<<(cpplog::My_ostream& ss
	, const std::pair<_T1, _T2>& pair);

template<typename _T1, typename _T2>
std::ostream& operator<<(std::ostream& ss, const std::pair<_T1,_T2>& p);

template<typename _T>
cpplog::My_ostream& operator<< (cpplog::My_ostream& ss, const std::vector<_T>& ay);

template<typename _T, typename _C, typename _A>
std::ostream& operator<<(std::ostream& ss, const std::set<_T, _C, _A>& s);

template<typename _K, typename _V>
std::ostream& operator<<(std::ostream& ss, const std::map<_K,_V>& mp);

template<typename _K, typename _V>
std::ostream& operator<<(std::ostream& ss, const std::multimap<_K,_V>& mp);


//-----------


template<typename _T1, typename _T2>
inline std::ostream& operator<<(std::ostream& ss
		, const std::pair<_T1,_T2>& p)
{
	ss<<"["<<p.first<<","<<p.second<<"]";
	return ss;
}


template<typename _T>
inline cpplog::My_ostream& operator<< (cpplog::My_ostream& ss, const std::vector<_T>& ay)
{
    ss<<"[";
    for(std::size_t i = 0; i< ay.size(); i++){
        ss<<ay[i];
        if(i!=ay.size()-1)
            ss<<",";
    }
    ss<<"]";
    return ss;
}



template<typename _T, typename _C, typename _A>
std::ostream& operator<<(std::ostream& ss, const std::set<_T, _C, _A>& s)
{
	ss<<"(";
	
	for(auto it = s.begin(); it!=s.end(); it++)
	{
		if(it == s.begin()){
			ss<<*it;
		}
		else{
			ss<<",";
			ss<<*it;
		}
	}
	ss<<")";
	return ss;
}

template<typename _K, typename _V>
inline std::ostream& operator<<(std::ostream& ss, const std::map<_K,_V>& mp)
{
	ss<<"{";
	for(auto it=mp.begin(); it!=mp.end(); it++){
		ss<<"("<<it->first<<":"<<it->second<<")";
	}
	ss<<"}";
	return ss;
}

template<typename _K, typename _V>
inline std::ostream& operator<<(std::ostream& ss, const std::multimap<_K,_V>& mp)
{
	ss<<"{";
	for(auto it=mp.begin(); it!=mp.end(); it++){
		ss<<"("<<it->first<<":"<<it->second<<")";
	}
	ss<<"}";
	return ss;
}




template<class _T1, class _T2>
inline cpplog::My_ostream& operator<<(cpplog::My_ostream& ss
	, const std::pair<_T1, _T2>& pair)
{
	ss << "(";
	ss << pair.first << "," << pair.second;
	ss << ")";
	return ss;
}



#endif