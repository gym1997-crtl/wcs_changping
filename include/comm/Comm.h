#ifndef _COMM_KYOSHO_20110903_
#define _COMM_KYOSHO_20110903_

//#include <algorithm>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
//


//#include <boost/algorithm/string.hpp>
//#include <boost/xpressive/xpressive_dynamic.hpp>
//#include <boost/filesystem.hpp>
#include <boost/math/common_factor_rt.hpp>
#include <iostream>



//using namespace std;
//using namespace boost;
//using namespace boost::BOOST_FILESYSTEM_NAMESPACE;

class cComm
{
public:
	cComm(void);
	~cComm(void);

	static void sleep(float time);
	static int SplitString(const std::string& input, const std::string& delimiter, std::vector<std::string>& results);
	static void StringUpper(std::string& strDes);

    static std::string trim(std::string & str);
  

	template<typename T>
	static bool RangeIt(T &res,T min,T max){

		if (res < min)
		{
			res = min;
			return false;
		}
		if (res > max)
		{
			res = max;
			return false;
		}
		return true;
	};
	template<typename T>
	static bool SaveGetFromBuffer(T& res,char* buffer,T tmin,T tmax){
		T t;
		memcpy(&t,buffer,sizeof(T));
		if (!RangeIt(t,tmin,tmax))
		{
			memset(&tmax,0,sizeof(T));
			return false;
		}else
		{
			res = t;
			return true;
		}
	};
	template<typename T>
	static bool SetBufferOfType(char* buffer,const T& source)
	{
		if (!buffer)
		{
			return false;
		}
		memset(buffer,0,sizeof(T));
		memcpy(buffer,&source,sizeof(T));
		return true;
	};
	template<typename T>
	static bool num_valid(const char* str){
		try{
			boost::lexical_cast<T>(str);
			return true;
		}
		catch(boost::bad_lexical_cast)
		{
			return false;
		}
	};
	template <class T> 
	static std::string ConvertToString(T value) {
		std::stringstream ss;
		ss << value;
		return ss.str();
	};
	template <class T>
	static T ConvertToNum(T &res,const std::string &str){
		try
		{
			res = boost::lexical_cast<T>(str.c_str());
			return res;
		}
		catch (boost::bad_lexical_cast& e)
		{
			
		}
		return res;
	};
	template<class T>
	static T Max(T t1 ,T t2){
		if (t1 > t2)
		{
			return t1;
		}
		else
		{
			return t2;
		}
	};
	template<class T>
	static T Min(T t1 ,T t2){
		if (t1 < t2)
		{
			return t1;
		}
		else
		{
			return t2;
		}
	};
	template<class T>
	static T Lcm(T t1, T t2)
	{
		return boost::math::lcm(t1,t2);
	};

	static std::string ByteToHexString(unsigned char* pData,int iLen);
	static int HexStringToByte(unsigned char** pChar,int& iLen,std::string strHex);

	//static void Find_files(const path& dir,const string& filename,vector<path>& v);
	static void Find_files(const std::string &strdir,const std::string& filename,std::vector<std::string>& v);
	static std::string GetRunPath();
	static bool FileExist(std::string strPath);
	static std::string Get_FileName(std::string strPath);
	static std::string Get_FileType(std::string strPath);
	static std::string Get_FilePath(std::string strPath);

	static bool load();
	static unsigned char* bit_value_;
	static unsigned int GetBit(const unsigned char &data,const unsigned char &pos );
};
#include "KHBoostInterproc.h"
class Config
{
public:
	template<typename Type>
	static bool getConfig(std::string name, Type &out)
	{
		bool    is_success = false;
		std::string  param_val;

		//
		try
		{
			BI::managed_shared_memory        cfg_data(BI::open_only, name.c_str());
			BI::named_mutex                  cfg_data_mtx(BI::open_only, "cfg_data_mtx");
			BI::scoped_lock<BI::named_mutex> lock(cfg_data_mtx);

			std::pair<BIString*, std::size_t> pair = cfg_data.find<BIString>(name.c_str());
			if( 0 != pair.first )
			{
				std::stringstream sstr;
				sstr<<(*pair.first);
				sstr>>out;
				//std::cout<<"****"<<name<<"***"<<param_val<<std::endl;

				is_success = true;
			}
		}
		catch(boost::interprocess::interprocess_exception &ex)
		{
			//std::cout<<"*** No such param! name:***"<<name<<" ***default value:"<<out<<std::endl;
		}

		return is_success;
	};

	static bool getConfig(std::string name, std::string &out)
	{
		bool    is_success = false;

		//
		try
		{
			BI::managed_shared_memory        cfg_data(BI::open_only, name.c_str());
			BI::named_mutex                  cfg_data_mtx(BI::open_only, "cfg_data_mtx");
			BI::scoped_lock<BI::named_mutex> lock(cfg_data_mtx);

			std::pair<BIString*, std::size_t> pair = cfg_data.find<BIString>(name.c_str());
			if( 0 != pair.first )
			{
				std::stringstream sstr;
				sstr<<(*pair.first);

				out = sstr.str();


				is_success = true;
			}
		}
		catch(boost::interprocess::interprocess_exception &ex)
		{
			std::cout << ex.get_error_code() <<"*** No such param! name:***"<<name<<" default value:"<<out<<std::endl;
		}

		return is_success;
	};
};

#define SLEEP(time) cComm::sleep(time)
#define SDelete( ptr )    do { if ( ptr ) { delete ( ptr ); ( ptr ) = 0; } } while(0)
#endif //_COMM_KYOSHO_20110903_
