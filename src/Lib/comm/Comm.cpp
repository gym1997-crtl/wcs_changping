

#include <cctype>


#include "boost/filesystem/path.hpp"  
#include "boost/filesystem/operations.hpp"  

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <boost/filesystem.hpp>

#include "comm/Comm.h"

#if defined(_WINDOWS)
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#else
#include <unistd.h>
#endif


using namespace boost;
using namespace boost::xpressive;
using namespace boost::filesystem;

#include <fstream>
#include <string>
#include <stdio.h>
#include <map>

using namespace std;

unsigned char* cComm::bit_value_ = new unsigned char[8];


cComm::cComm(void)
{
}

cComm::~cComm(void)
{
}
bool cComm::load()
{
	bit_value_[0] = 1;
	bit_value_[1] = 2;
	bit_value_[2] = 4;
	bit_value_[3] = 8;
	bit_value_[4] = 16;
	bit_value_[5] = 32;
	bit_value_[6] = 64;
	bit_value_[7] = 128;
	return true;
}

std::string cComm::trim(std::string & str){
  std::string::size_type pos = str.find_first_not_of(' ');
  if (pos == std::string::npos)
  {
      return str;
  }
  std::string::size_type pos2 = str.find_last_not_of(' ');
  if (pos2 != std::string::npos)
  {
      return str.substr(pos, pos2 - pos + 1);
  }
  return str.substr(pos);

}
int cComm::SplitString(const std::string& input, 
				const string& delimiter, vector<string>& results)
{
	int iPos = 0;
	int newPos = -1;
	int sizeS2 = (int)delimiter.size();
	int isize = (int)input.size();
	results.clear();

	if( 
		( isize == 0 )
		||
		( sizeS2 == 0 )
		)
	{
		return 0;
	}

	vector<int> positions;


	int numFound = 0;


	while ((newPos = input.find (delimiter, iPos)) != string::npos )
	{
		positions.push_back(newPos);
		iPos = newPos + sizeS2;
		numFound++;
	}

	if( numFound == 0 )
	{
		if (input.size()>0)
		{
			results.push_back(input);
		}
		return 1;
	}

	if (positions.back() != isize)
	{
		positions.push_back(isize);
	}
	

	

	int offset = 0; 
	std::string s("");

	for( int i=0; i < (int)positions.size(); ++i )
	{

		s = input.substr( offset, positions[i]- offset ); 

		offset = positions[i] + sizeS2;

 		if (s.length()>0 && !all(s,is_space()))
 		{
 			results.push_back(s);
 		}
		

	}
	return numFound;
}

void cComm::StringUpper(std::string& strDes)
{
	std::transform(strDes.begin(),strDes.end(),strDes.begin(),::toupper);  //ת��д
}

std::string cComm::ByteToHexString( unsigned char* pData,int iLen )
{
	std::string strTmp;

	char chTmp[8];
	for(int i = 0 ;i<iLen ;++i)
	{
		sprintf_s(chTmp, "%02X ", pData[i]);
		strTmp += chTmp;
	}
	return strTmp;
}
int cComm::HexStringToByte( unsigned char** pChar,int& iLen,std::string strHex )
{
	std::vector<std::string> v_str;
	SplitString(strHex," ",v_str);
	std::vector<std::string>::iterator it = v_str.begin();
	
	if (v_str.size() <=0)
	{
		return 0;
	}
	*pChar = new unsigned char[v_str.size()];
	memset(*pChar,0,v_str.size());

	int index(0);
	for (;it != v_str.end();++it)
	{
		if ((*it).length() > 2 ||(index >= v_str.size()))
		{
			continue;
		}
		else if ( (*it).length() == 1)
		{
			char ch[1] = {0};
			memcpy(ch,(*it).c_str(),1);
			if ((ch[0] >='0') && (ch[0] <='9'))      
				(*pChar)[index] = ch[0] - 48;//�ַ�0��ASCIIֵΪ48   
			else if ((ch[0]>='a') && (ch[0]<='f'))      
				(*pChar)[index] =ch[0] -'a' + 10;      
			else if ((ch[0]>='A') && (ch[0]<='F'))      
				(*pChar)[index] = ch[0]-'A'+10; 
		}
		else if ((*it).length() == 2)
		{
			char ch[1] = {0};
			memcpy(ch,(*it).c_str(),1);
			if ((ch[0] >='0') && (ch[0] <='9'))      
				(*pChar)[index] = ch[0] - 48;//�ַ�0��ASCIIֵΪ48   
			else if ((ch[0]>='a') && (ch[0]<='f'))      
				(*pChar)[index] = ch[0] -'a' + 10;      
			else if ((ch[0]>='A') && (ch[0]<='F'))      
				(*pChar)[index] = ch[0]-'A'+10; 

			ch[0] = 0 ;
			memcpy(ch,(*it).c_str()+1,1);
			if ((ch[0] >='0') && (ch[0] <='9'))      
				(*pChar)[index] = (*pChar)[index]*16 + (ch[0] - 48);//�ַ�0��ASCIIֵΪ48   
			else if ((ch[0]>='a') && (ch[0]<='f'))      
				(*pChar)[index] = (*pChar)[index]*16 + (ch[0] -'a' + 10);      
			else if ((ch[0]>='A') && (ch[0]<='F'))      
				(*pChar)[index] = (*pChar)[index]*16 + (ch[0]-'A'+10); 
		}

		index++;
	}
	iLen = v_str.size();
	return iLen;
}

void cComm::Find_files(const std::string &strdir,const std::string& filename,std::vector<std::string>& v)
//void cComm::Find_files(const path& dir,const std::string& filename,std::vector<path>& v)
{
	path dir(strdir);
	typedef recursive_directory_iterator rd_iterator;
	static xpressive::sregex_compiler rc;
	if(!rc[filename].regex_id())
	{
		std::string str = replace_all_copy(replace_all_copy(filename,".","\\."),"*",".*");
		rc[filename] = rc.compile(str);
	}
	typedef vector<path> result_type;
	if (!exists(dir) || !is_directory(dir))
	{
		return;
	}
	rd_iterator end;
	for (rd_iterator pos(dir);pos != end;++pos)
	{
		if (!is_directory(*pos) && regex_match(pos->path().filename().string(),rc[filename]))
		{
			v.push_back(pos->path().string());
		}
	}
}

std::string cComm::GetRunPath()
{
	return boost::filesystem::initial_path<boost::filesystem::path>().string();
}

bool cComm::FileExist(std::string strPath)
{
	return boost::filesystem::exists(strPath);
}

std::string cComm::Get_FileName(std::string strPath)
{
//	std::vector<std::string> v_path;
//	SplitString(strPath,".",v_path);
//	if ((v_path.size()<2))
//	{
//		if(v_path.size()==1){
//			return v_path[0];
//		}
//		else
//		{
//			return "";
//		}
//	}
//
//	std::string strPath_name = v_path[0];
//	std::vector<std::string> vp ;
//	cComm::SplitString(strPath_name,"\\",vp);
//	if (vp.size()>1)
//	{
//		return vp[vp.size()-1];
//	}else{
//		cComm::SplitString(strPath_name,"/",vp);
//		if (vp.size()>1)
//		{
//			return vp[vp.size()-1];
//		}
//	}
	const char* full_name = strPath.c_str();

	const char*  mn_first = full_name;
	const char*  mn_last  = full_name + strlen( full_name );
	if ( std::strrchr( full_name, '\\' ) != NULL )
		mn_first = strrchr( full_name, '\\' ) + 1;
	else if ( strrchr( full_name, '/' ) != NULL )
		mn_first = strrchr( full_name, '/' ) + 1;
	if ( strrchr( full_name, '.' ) != NULL )
		mn_last = strrchr( full_name, '.' );
	if ( mn_last < mn_first )
		mn_last = full_name + strlen( full_name );

	strPath.assign( mn_first, mn_last );

	return strPath;


}

std::string cComm::Get_FileType( string strPath )
{
	std::vector<std::string> v_path;
	SplitString(strPath,".",v_path);
	if ((v_path.size()>1))
	{
		return v_path[v_path.size() -1];
	}
	return strPath;
}
std::string cComm::Get_FilePath( std::string strPath )
{
	int iPos = 0;
	int newPos = -1;
	
	int sizeS2 = 1;

	while ((newPos = strPath.find ("/", iPos))>0)
	{
		iPos = newPos + sizeS2;
	}
	if (iPos == 0)
	{
		return "";
		//iPos = strPath.size();
	}
	std::string path = strPath.substr(0,iPos);

	return path;
}
unsigned int cComm::GetBit( const unsigned char &data,const unsigned char &pos )
{
	return data & bit_value_[pos];
}

void cComm::sleep(float time)
{
//  	boost::system_time const timeout = boost::get_system_time() + boost::posix_time::milliseconds((long)time);
//  	boost::thread::sleep(timeout);
#if defined(_WINDOWS)
	Sleep(time);
#else
	usleep(time*1000);
#endif
}



