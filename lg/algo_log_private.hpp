
#ifndef __ZM_LOG_H
#define __ZM_LOG_H


#define LOG_RELEASE_SHORT_FILE_NAME

#ifndef LOG_MODEL_NAME
#define LOG_MODEL_NAME "algo"
#endif

#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME "algo.log"
#endif

//#define LOG_USE_BOOST

#ifdef LOG_USE_BOOST
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#endif


#ifdef WIN32
#define __func__ __FUNCTION__
#endif

#ifdef _USE_MFC
void exter_output_debug_string_a(const char* a);
#endif

// This define must be before including "cpplog.hpp"



#ifdef ZM_RELEASE

#define ZM_LOG_LEVEL(level, logger) __log_private::CustomLogMessage("AM", "AM", __LINE__, (level), logger).getStream()

#else

#define ZM_LOG_LEVEL(level, logger) __log_private::CustomLogMessage(__FILE__, __func__, __LINE__, (level), logger).getStream()


#endif

//#include "./log/cpplog.hpp"
#include "cpplog_1.hpp"


namespace __log_private{

    struct LoggerConfigure{
        std::string modelName;

        static LoggerConfigure& Instance(){
            static LoggerConfigure cfg;
            return cfg;
        }
    };


    class CustomLogMessage : public cpplog::LogMessage
    {
    public:
        CustomLogMessage(const char* file, const char* function,
            unsigned int line, cpplog::loglevel_t logLevel,
            cpplog::BaseLogger &outputLogger)
            : cpplog::LogMessage(file, line, logLevel, outputLogger, false),
            m_function(function)
        {
            InitLogMessage();
        }

        static const char* shortLogLevelName(cpplog::loglevel_t logLevel)
        {
            switch (logLevel)
            {
            case ZM_LL_TRACE: return "T";
            case ZM_LL_DEBUG: return "D";
            case ZM_LL_INFO:  return "I";
            case ZM_LL_WARN:  return "W";
            case ZM_LL_ERROR: return "E";
            case ZM_LL_FATAL: return "F";
            default:       return "O";
            };
        }

    protected:
		virtual void InitLogMessage()
		{
			std::stringstream ss;
#ifdef _DEBUG
			ss
				<< "[" << LOG_MODEL_NAME << "][" << shortLogLevelName(m_logData->level) << "|"
				<< m_logData->fileName << ":"
				<< m_logData->line <<"]["
				<< m_logData->utcTime.tm_hour << ":"
				<< m_logData->utcTime.tm_min << ":"
				<< m_logData->utcTime.tm_sec 
				<< "] ";

#else
            std::string short_file_name = m_logData->fileName;

#ifdef LOG_RELEASE_SHORT_FILE_NAME
            if (short_file_name.size() > 3) {
                short_file_name.resize(3);
            }
#endif

            ss
                << "[" << LOG_MODEL_NAME << "]["
                << short_file_name << ":"
                << m_logData->line
                << "]["
                << shortLogLevelName(m_logData->level)
                << "]["
                << m_logData->utcTime.tm_year + 1900 << "-"
                << m_logData->utcTime.tm_mon + 1 << "-"
                << m_logData->utcTime.tm_mday << " "
                << m_logData->utcTime.tm_hour << ":"
                << m_logData->utcTime.tm_min << ":"
                << m_logData->utcTime.tm_sec << "] ";
            /*
            if (release_full_log){
                ss
                    << "[" << title_ << "]["
                    << m_logData->fileName << ":"
                    << m_logData->line
                    << "]["
                    << shortLogLevelName(m_logData->level)
                    << "]["
                    << m_logData->utcTime.tm_year + 1900 << "-"
                    << m_logData->utcTime.tm_mon + 1 << "-"
                    << m_logData->utcTime.tm_mday << " "
                    << m_logData->utcTime.tm_hour << ":"
                    << m_logData->utcTime.tm_min << ":"
                    << m_logData->utcTime.tm_sec << "] ";
            }
            else{
                ss
                    << "[" << title_ << "]["
                    << shortLogLevelName(m_logData->level)
                    << "]["
                    << m_logData->utcTime.tm_year + 1900 << "-"
                    << m_logData->utcTime.tm_mon + 1 << "-"
                    << m_logData->utcTime.tm_mday << " "
                    << m_logData->utcTime.tm_hour << ":"
                    << m_logData->utcTime.tm_min << ":"
                    << m_logData->utcTime.tm_sec << "] ";
            }
            */
#endif
            std::string strHead = ss.str();
            m_logData->stream << strHead;
            //m_logData->head_length = (unsigned int)strHead.length();
        }
        const char* _get_function(){return m_function;}
    private:
        const char *m_function;
    };

};

namespace cpplog{

    class _FilteringLogger : public FilteringLogger{
    public:
        _FilteringLogger(loglevel_t level, BaseLogger* forwardTo)
            :FilteringLogger(level, forwardTo){}

        void SetLevel(loglevel_t level){
            m_lowestLevelAllowed = level;
        }
    };

    //std::count
    class _StdLogger :public _FilteringLogger{
    public:
        _StdLogger()
            :_FilteringLogger(ZM_LL_TRACE, new StdErrLogger)
        {}
        virtual ~_StdLogger(){}
    };

    //outputdebugstring
    class __DbgViewLogger :public BaseLogger{
        virtual bool sendLogMessage(LogData* logData){
#ifdef _USE_MFC
            helpers::fixed_streambuf* const sb = &logData->streamBuffer;
            exter_output_debug_string_a(sb->c_str());
        //    OutputDebugStringA(sb->c_str());
#endif
            return true;
        }
    };

    //write file
    class _FileLogger :public _FilteringLogger{
    public:
        _FileLogger()
            :_FilteringLogger(ZM_LL_INFO, new FileLogger(LOG_FILE_NAME, false))
        {
            
        }
        _FileLogger(const std::string& fileName)
            :_FilteringLogger(ZM_LL_INFO, new FileLogger(fileName, false))
        {}
    };

    class _DbgViewLogger :public _FilteringLogger{
    public:
        _DbgViewLogger() :
            _FilteringLogger(ZM_LL_TRACE, new __DbgViewLogger)
        {}
        virtual ~_DbgViewLogger(){}
    };


    class ZmLogger : public BaseLogger{
    public:
        enum LOGGER_WAY{
            STD_OUT,
            FILE_OUT,

        };

    public:
        ZmLogger(){
            stdLogger_ = new _StdLogger;
            dbgViewLogger_ = new _DbgViewLogger;
            fileLogger_ = new _FileLogger;
        }
        void SetStdOutLevel(int level){
            if (stdLogger_)
                stdLogger_->SetLevel(level);
        }
#ifdef LOG_USE_BOOST
        void useTimeIdLog(const std::string& dic){
            namespace bf = boost::filesystem;

            auto ensureDic = [](const bf::path& dic)
            {
                if (dic.empty())
                    return;

                bf::path p(dic);

                if (bf::is_directory(p) && bf::exists(p)){
                    return;
                }
                
                bf::create_directories(p);
            };


            auto getTimeId_Full = []()->std::string{
                boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
                return boost::str(boost::format("%1%_%2%_%3%__%4%-%5%-%6%")
                    % now.date().year()
                    % now.date().month()
                    % now.date().day()
                    % now.time_of_day().hours()
                    %now.time_of_day().minutes()
                    %now.time_of_day().seconds()
                );
            };

            auto gen_UUIDStr=[]()->std::string{
                boost::uuids::uuid uuid = boost::uuids::random_generator()();
                std::string strId = boost::lexical_cast<std::string>(uuid);
                return strId;
            };

            std::string logName = getTimeId_Full() + "___"+gen_UUIDStr() + ".log";

            bf::path p(dic);
            ensureDic(p);

            p/=logName;
            std::string logPath = p.string();
            std::cout<<"logPath: "<<logPath<<std::endl;

            if(fileLogger_)
                delete fileLogger_;
            fileLogger_ = new _FileLogger(logPath);
        }
#endif

        virtual bool sendLogMessage(LogData* logData){
            if (stdLogger_)
                stdLogger_->sendLogMessage(logData);
            if (dbgViewLogger_)
                dbgViewLogger_->sendLogMessage(logData);
            if (fileLogger_)
                fileLogger_->sendLogMessage(logData);

            return true;
        }

    private:
        _StdLogger* stdLogger_;
        _DbgViewLogger* dbgViewLogger_;
        _FileLogger* fileLogger_;
    };
};




namespace __log_private{

    class _G_Log{
    public:
        static cpplog::ZmLogger& GetLogger(){
            static cpplog::ZmLogger logger;
            return logger;
        }
    };
};

#define glog __log_private::_G_Log::GetLogger()



#ifdef _WIN32

#ifdef min
    #undef min
#endif


#ifdef max
    #undef max
#endif


#endif

#endif
