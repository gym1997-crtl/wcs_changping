#include <boost/thread.hpp>
#include <ctime>

#include "comm/Comm.h"
#include "comm/TimerDiff.h"

cTimerDiff::cTimerDiff(void)
{
	Begin();
	End();

	
}

cTimerDiff::~cTimerDiff(void)
{
}

void cTimerDiff::Begin() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	beginTime = t;
}

long long cTimerDiff::End() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	endTime = t;

	boost::posix_time::time_duration t3 = (endTime - beginTime);

	return t3.total_microseconds();

}
void cTimerDiff::ms_begin() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	ms_beginTime = t;
}

long long cTimerDiff::ms_end() {
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	ms_endTime = t;

	boost::posix_time::time_duration t3 = (ms_endTime - ms_beginTime);

	return t3.total_microseconds();

}
long long cTimerDiff::GetTime() const{
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());
	boost::posix_time::time_duration t3 = (t - beginTime);
	
	return t3.total_microseconds();
}
std::string cTimerDiff::get_now(){

		time_t tNowTime;
		time(&tNowTime);

		tm* tLocalTime = localtime(&tNowTime);

		std::stringstream ss;
		ss<<tLocalTime->tm_year+1900 <<"-"<<tLocalTime->tm_mon+1 <<"-"<<tLocalTime->tm_mday<<"-"<<tLocalTime->tm_hour <<" "<< tLocalTime->tm_min <<" "<< tLocalTime->tm_sec;
		return ss.str();
}
void cTimerDiff::PrintString(){
	//printf("@Use Time = %f\n",GetTime());
}

void cTimerDiff::ms_loop( int ms )
{
	float do_time = ms_end() / 1e3;

	if (do_time > ms)
	{
		ms_begin();
		return;
	}else{
		do_time = ms - do_time;
		if ((do_time > 0)  && (do_time < 100000) )
		{
			//std::cout<<"sleep:"<<do_time<<std::endl;
			SLEEP(do_time);
		}
		else{
			std::cout<<" err call !! "<<do_time<<std::endl;
		}
		
	}
	ms_begin();
}

long long cTimerDiff::total_ms()
{
	std::string s1 = "1970-01-01 00:00:00.000000";
	boost::posix_time::ptime epoch(boost::posix_time::time_from_string(s1));
	//boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
	boost::posix_time::ptime t(
		boost::posix_time::microsec_clock::local_time());

	boost::posix_time::time_duration time_from_epoch =
		t - epoch;
	long long dt = time_from_epoch.total_microseconds();

	return dt;

	//return time_from_epoch.total_seconds();

}
