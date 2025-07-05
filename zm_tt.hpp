#pragma once

#include <boost/date_time.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>


namespace zm
{
	inline int64_t getTickCount() {
		boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
		return boost::numeric_cast<int64_t>(now.time_of_day().total_milliseconds());
	}

	inline void sleep(int64_t tick)
	{
		using namespace std::chrono_literals;

		std::this_thread::sleep_for(std::chrono::milliseconds(tick));
	}

	inline std::string GetTimeId_Days() {
		boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
		return boost::str(boost::format("%1%_%2%_%3%")
			% now.date().year()
			% now.date().month()
			% now.date().day());
	}


	inline std::string GetTimeId_Full() {
		boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
		return boost::str(boost::format("%1%_%2%_%3%&%4%-%5%-%6%")
			% now.date().year()
			% now.date().month()
			% now.date().day()
			% now.time_of_day().hours()
			% now.time_of_day().minutes()
			% now.time_of_day().seconds()
		);
	}

	inline std::string GetTimeId_Short() {
		boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
		return boost::str(boost::format("%1%_%2%_%3%")
			% now.time_of_day().hours()
			% now.time_of_day().minutes()
			% now.time_of_day().seconds()
		);
	}



	class TT
	{
	public:
		TT() {
			start_tk_ = getTickCount();
		}
		int64_t Delta() const {
			int64_t end_tk = getTickCount();
			int64_t delta = end_tk - start_tk_;

			return delta;
		}
		int64_t delta() const {
			int64_t end_tk = getTickCount();
			int64_t delta = end_tk - start_tk_;

			return delta;
		}

		int64_t delta_with_reset() {
			int64_t tk = delta();
			reset();
			return tk;
		}

		void Reset() {
			start_tk_ = getTickCount();
		}
		void reset() {
			start_tk_ = getTickCount();
		}

	private:
		int64_t start_tk_{0};
	};


	struct EnsureWaitTick
	{
		EnsureWaitTick(int64_t tick) {
			interval_ = tick;
			startTick_ = zm::getTickCount();
		}
		void wait() {
			int64_t curTick = zm::getTickCount();
			int64_t sp = startTick_ + interval_ - curTick;
			//if (startTick_ + interval_ > curTick) {
			if (sp > 0) {
				//uint64_t sp = curTick - startTick_ - interval_;
				//LG << "ensure wait tick sleep: " << sp
				//	<<" curTick = "<<curTick
				//	<<"  startTick = "<<startTick_
				//	<<" interval = "<<interval_;
				zm::sleep(int64_t(sp));
			}
		}
		~EnsureWaitTick() {
			wait();
		}

	private:
		int64_t startTick_;
		int64_t interval_;
	};

}//