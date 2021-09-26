
#ifndef COMMON_ED_H
#define COMMON_ED_H
 
#include<vector>
#include <iostream>  
#include <sstream>  



class Common
{

public:

	Common();

	~Common();

	static std::string getTime();

	static int SplitString(const std::string& input, const std::string& delimiter, std::vector<std::string>& results);

};
#endif //COMMON_ED_H

