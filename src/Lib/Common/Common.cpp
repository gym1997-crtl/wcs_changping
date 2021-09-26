#include <time.h>
#include "Common/Common.h"  
#include <boost/algorithm/string.hpp>

using namespace boost;

Common::Common()
{

}

Common::~Common()
{

}

std::string Common::getTime()
{
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
	return tmp;
}

int Common::SplitString(const std::string& input, const std::string& delimiter, std::vector<std::string>& results)
{
	int iPos = 0;
	int newPos = -1;
	int sizeS2 = (int)delimiter.size();
	int isize = (int)input.size();
	results.clear();

	if(  ( isize == 0 ) || ( sizeS2 == 0 ) )
	{
		return 0;
	}

	std::vector<int> positions;

	int numFound = 0;

	while ((newPos = input.find (delimiter, iPos)) != std::string::npos )
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
	return 1;
}
