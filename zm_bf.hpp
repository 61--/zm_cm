#pragma once


#include <string>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/core/noncopyable.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/unordered_map.hpp>



#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>



#include <boost/noncopyable.hpp>
#include <boost/format.hpp>

#include <boost/static_assert.hpp>

#ifdef __ZM_USE_OPENCV
#include <opencv2/opencv.hpp>

#endif


#ifdef __ZM_USE_EIGEN

#define EIGEN_DENSEBASE_PLUGIN "EigenDenseBaseAddns.h"
#include <Eigen/Core>
#include <Eigen/Eigen>

#endif


//#define USE_SOPHUS
#ifdef USE_SOPHUS
	#include <sophus/se3.hpp>
#endif




namespace zm
{

    class Buffer:public boost::noncopyable{
    public:
        Buffer(){
            pss_ = new std::stringstream;
            poa_ = nullptr;
            pia_ = nullptr;
        }
        ~Buffer(){
            if(poa_) delete poa_;
            if(pia_) delete pia_;
            if(pss_) delete pss_;
        }

        Buffer(const Buffer& other){
            pss_ = new std::stringstream;
            poa_ = nullptr;
            pia_ = nullptr;

            (*pss_) << other.pss_->rdbuf();

        }

        Buffer& operator=(const Buffer& other){
            (*pss_) << other.pss_->rdbuf();
            return *this;
        }

        boost::archive::text_oarchive& w(){
            //assert(poa_ && pia_);
            if(!poa_)
                poa_ = new boost::archive::text_oarchive(*pss_);
            return *poa_;
        }
        boost::archive::text_iarchive& r(){
            if(poa_){
                delete poa_;
                poa_ = nullptr;
            }
            if(!pia_){
                pia_ = new boost::archive::text_iarchive(*pss_);
            }
            return *pia_;
        }
        template<typename _T>
        Buffer& operator<<(const _T& t){
            w()<<t;
            return *this;
        }
        template<typename _T>
        Buffer& operator>>(_T& t){
            r()>>t;
            return *this;
        }

    protected:
        std::stringstream* pss_;
        boost::archive::text_oarchive *poa_;
        boost::archive::text_iarchive *pia_;
    };

	class StrBuffer:public Buffer
	{
	public:
		StrBuffer(){}
		StrBuffer(const std::string& str){
			(*pss_)<<str;
		}
		std::string getStr(){
			std::string str = pss_->rdbuf()->str();
			return str;
		}
	};


    class FBuffer: public boost::noncopyable{
    public:
        enum _WRITE {write};
        enum _READ {read};

    public:
        FBuffer(const std::string& name, _WRITE){
            fs_ = new std::fstream(name, std::ios::out);
            poa_ = new boost::archive::text_oarchive(*fs_);
            pia_ = nullptr;
        }
        FBuffer(const std::string& name, _READ){
            fs_ = new std::fstream(name, std::ios::in);
            poa_ = nullptr;
            pia_ = nullptr;
            if(fs_->good()){
                pia_ = new boost::archive::text_iarchive(*fs_);
            }
        }

        ~FBuffer(){
            if(poa_) delete poa_;
            if(pia_) delete pia_;
            if(fs_) delete fs_;
        }

        bool good(){
            if(fs_!=nullptr){
                return fs_->good();
            }
            return false;
        }

        boost::archive::text_oarchive& w(){ return *poa_;}
        boost::archive::text_iarchive& r(){ return *pia_;}

        template<typename _T>
        FBuffer& operator<<(const _T& t){
            w()<<t;
            return *this;
        }
        template<typename _T>
        FBuffer& operator>>(_T& t){
            r()>>t;
            return *this;
        }


    private:
        std::fstream* fs_;
        boost::archive::text_oarchive *poa_;
        boost::archive::text_iarchive *pia_;
    };


    template<typename _T>
    bool FBuffer_write(const std::string& name, const _T& t)
    {
        FBuffer bf(name, FBuffer::write);
        bf << t;

        return bf.good();
    }

    template<typename _T>
    bool FBUffer_read(const std::string& name, _T& t)
    {
        FBuffer bf(name, FBuffer::read);
        bf >> t;
        return bf.good();
    }
}//

    //------------------------
    //-----------------------------------------------






#define ZM_BF_SUPPORT_1(Data,p0) template<typename Archive> inline void serialize(Archive &ar, Data& data, const unsigned int){ ar&data.p0;}
#define ZM_BF_SUPPORT_2(Data,p0,p1) template<typename Archive> inline void serialize(Archive &ar, Data& data, const unsigned int){ ar&data.p0&data.p1;}
#define ZM_BF_SUPPORT_3(Data,p0,p1,p2) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int){ ar&data.p0&data.p1&data.p2;}
#define ZM_BF_SUPPORT_4(Data,p0,p1,p2,p3) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int){ ar&data.p0&data.p1&data.p2&data.p3;}
#define ZM_BF_SUPPORT_5(Data,p0,p1,p2,p3,p4) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4;if(version);}
#define ZM_BF_SUPPORT_6(Data,p0,p1,p2,p3,p4,p5) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5;if(version);}
#define ZM_BF_SUPPORT_7(Data,p0,p1,p2,p3,p4,p5,p6) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6;if(version);}
#define ZM_BF_SUPPORT_8(Data,p0,p1,p2,p3,p4,p5,p6,p7) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7;if(version);}
#define ZM_BF_SUPPORT_9(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8;if(version);}
#define ZM_BF_SUPPORT_10(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9;if(version);}
#define ZM_BF_SUPPORT_11(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10;if(version);}
#define ZM_BF_SUPPORT_12(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11;if(version);}
#define ZM_BF_SUPPORT_13(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12;if(version);}
#define ZM_BF_SUPPORT_14(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13;if(version);}
#define ZM_BF_SUPPORT_15(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14;if(version);}
#define ZM_BF_SUPPORT_16(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15;if(version);}
#define ZM_BF_SUPPORT_17(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16;if(version);}
#define ZM_BF_SUPPORT_18(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17;if(version);}
#define ZM_BF_SUPPORT_19(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18;if(version);}
#define ZM_BF_SUPPORT_20(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19;if(version);}
#define ZM_BF_SUPPORT_21(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20;if(version);}
#define ZM_BF_SUPPORT_22(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21;if(version);}
#define ZM_BF_SUPPORT_23(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22;if(version);}
#define ZM_BF_SUPPORT_24(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23;if(version);}
#define ZM_BF_SUPPORT_25(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24;if(version);}
#define ZM_BF_SUPPORT_26(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25;if(version);}
#define ZM_BF_SUPPORT_27(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26;if(version);}
#define ZM_BF_SUPPORT_28(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27;if(version);}
#define ZM_BF_SUPPORT_29(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28;if(version);}
#define ZM_BF_SUPPORT_30(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29;if(version);}
#define ZM_BF_SUPPORT_31(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30;if(version);}
#define ZM_BF_SUPPORT_32(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31;if(version);}
#define ZM_BF_SUPPORT_33(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32;if(version);}
#define ZM_BF_SUPPORT_34(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33;if(version);}
#define ZM_BF_SUPPORT_35(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33&data.p34;if(version);}
#define ZM_BF_SUPPORT_36(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34,p35) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33&data.p34&data.p35;if(version);}
#define ZM_BF_SUPPORT_37(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34,p35,p36) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33&data.p34&data.p35&data.p36;if(version);}
#define ZM_BF_SUPPORT_38(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34,p35,p36,p37) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33&data.p34&data.p35&data.p36&data.p37;if(version);}
#define ZM_BF_SUPPORT_39(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34,p35,p36,p37,p38) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33&data.p34&data.p35&data.p36&data.p37&data.p38;if(version);}
#define ZM_BF_SUPPORT_40(Data,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34,p35,p36,p37,p38,p39) template<typename Archive> void serialize(Archive &ar, Data& data, const unsigned int version){ ar&data.p0&data.p1&data.p2&data.p3&data.p4&data.p5&data.p6&data.p7&data.p8&data.p9&data.p10&data.p11&data.p12&data.p13&data.p14&data.p15&data.p16&data.p17&data.p18&data.p19&data.p20&data.p21&data.p22&data.p23&data.p24&data.p25&data.p26&data.p27&data.p28&data.p29&data.p30&data.p31&data.p32&data.p33&data.p34&data.p35&data.p36&data.p37&data.p38&data.p39;if(version);}



//===============================
//opencv support

#ifdef __ZM_USE_OPENCV

namespace cv{

    template<typename Archive, typename _T>
    void serialize(Archive& ar, Point3_<_T>& p3,const unsigned int version){
        ar&p3.x&p3.y&p3.z;
    }

    template<typename Archive, typename _T>
    void serialize(Archive& ar, Point_<_T>& p2, const unsigned int version){
        ar & p2.x& p2.y;
    }

    template<typename Archive, typename _T>
    void serialize(Archive& ar, Size_<_T>& s, const unsigned int version){
        ar & s.width& s.height;
    }
    template<typename Archive, typename _T, int N>
    void serialize(Archive& ar, Vec<_T,N>& v, const unsigned int version){
        for(int i = 0; i< N; i++)
            ar& v[i];
    }

    ZM_BF_SUPPORT_6(KeyPoint,angle,class_id,octave,pt,response,size);


}//cv


namespace boost{namespace serialization{

    template<typename _T,typename Archive>
    void _save(Archive& ar, const cv::Mat& img, const unsigned int version)
    {
        for(int j =0; j<img.rows;j++){
            const _T* ptr = img.ptr<_T>(j);
            for(int i=0; i<img.cols; i++){
                _T v = ptr[i];
                ar&v;
            }
        }
    }

	template<typename Archive>
	void _save_png(Archive& ar, const cv::Mat& img, const unsigned int version)
	{
		std::vector<uchar> bf;
		cv::imencode(".png", img, bf);

		ar & bf;
	}

    template<typename Archive>
    void save(Archive& ar, const cv::Mat& img, const unsigned int version)
    {
        cv::Size sz = img.size();
        int type = img.type();
        ar&sz&type;

        if(!img.empty()){

            switch(img.type()){
            case CV_8U:
                _save<uchar>(ar, img,version);
                break;

            case CV_8UC3:
                //_save<cv::Vec3b>(ar, img,version);
				_save_png(ar, img, version);
                break;

            case CV_32F:
                _save<float>(ar, img,version);
                break;

            case CV_64F:
                _save<double>(ar, img,version);
                break;

            default:
                assert(0);
            }
        }
    }

    template<typename _T,typename Archive>
    void _load(Archive& ar, cv::Mat& img, const unsigned int version)
    {

        for(int j =0; j<img.rows;j++){
            _T* ptr = img.ptr<_T>(j);
            for(int i=0; i<img.cols; i++){
                ar&ptr[i];
            }
        }
    }

	template<typename Archive>
	void _load_png(Archive& ar, cv::Mat& img, const unsigned int version)
	{
		std::vector<uchar> bf;
		ar & bf;
		img = cv::imdecode(bf, cv::IMREAD_COLOR);
	}


    template<typename Archive>
    void load(Archive& ar, cv::Mat& img, const unsigned int version)
    {

        cv::Size sz;
        int type=0;
        ar&sz&type;
        img = cv::Mat(sz,type);

        if(!img.empty()){
            switch(img.type()){
                case CV_8U:
                    _load<uchar>(ar, img,version);
                    break;

                case CV_8UC3:
                    //_load<cv::Vec3b>(ar, img,version);
					_load_png(ar, img, version);
                    break;

                case CV_32F:
                    _load<float>(ar, img,version);
                    break;

                case CV_64F:
                    _load<double>(ar, img,version);
                    break;

                default:
                    assert(0);
            }
        }
    }

}}


namespace cv{

    template<typename Archive>
    void serialize(Archive& ar, cv::Mat& img, const unsigned int version)
    {
        boost::serialization::split_free(ar, img, version);
    }


	template<typename Archive>
	void serialize(Archive& ar, cv::Scalar& c, const unsigned int version)
	{
		ar & c[0] & c[1] & c[2] & c[3];
	}

}//cv


#endif


#ifdef __ZM_USE_EIGEN

namespace boost{namespace serialization{
	template<typename Archive
		, typename Scalar
		, int Options>
    void save(Archive& ar
			, const Eigen::Quaternion< Scalar, Options >& q
			, const unsigned int version)
    {
		Scalar w = q.w();
		Scalar x = q.x();
		Scalar y = q.y();
		Scalar z = q.z();

		ar & w & x & y & z;
	}
  
	template<typename Archive
		, typename Scalar
		, int Options>
    void load(Archive& ar
			, Eigen::Quaternion< Scalar, Options >& q
			, const unsigned int version)
	{
		Scalar w, x,y,z;
		ar &w &x &y &z;

		//std::cout<<"w = "<<w<<" - x = "<<x<<" - y = "<<y<<" - z = "<<z<<std::endl;
		q=Eigen::Quaternion< Scalar, Options >(w,x,y,z);
	}

}}//

namespace Eigen{
	template<typename Archive, typename Scalar, int Options = AutoAlign>
	void serialize(Archive& ar
			, Eigen::Quaternion< Scalar, Options >& q
			, const unsigned int version)
	{
		 boost::serialization::split_free(ar, q, version);	
	}
}//Eigen


#endif

#ifdef USE_SOPHUS
	namespace boost{namespace serialization{
		template<typename Archive
			, typename Scalar
			, int Options>
		void save(Archive& ar
			, const Sophus::SE3< Scalar, Options >& se3
			, const unsigned int version)
		{
			Eigen::Quaternion<Scalar> q = se3.so3().unit_quaternion();	
			Eigen::Matrix<Scalar,3,1> t = se3.translation();
			ar & q & t;
		}

		template<typename Archive
			, typename Scalar
			, int Options>
		void load(Archive& ar
			, Sophus::SE3< Scalar, Options >& se3
			, const unsigned int version)
		{
			Eigen::Quaternion<Scalar> q;
			Eigen::Matrix<Scalar,3,1> t;
			
			ar & q & t;
			se3 =  Sophus::SE3< Scalar, Options >(q,t);
		}
	}}//

	//LG<<"t = "<<se3.translation();
	//Eigen::Quaterniond q = se3.so3().unit_quaternion();



	namespace Sophus{
		template<typename Archive, typename Scalar, int Options>
		inline void serialize(Archive& ar
			, SE3< Scalar, Options >& se3
			, const unsigned int version)
		{
			boost::serialization::split_free(ar, se3, version);	
		}

	}//


#endif



namespace algo{
	typedef  zm::FBuffer FBuffer;
	typedef  zm::Buffer Buffer;
};
    




