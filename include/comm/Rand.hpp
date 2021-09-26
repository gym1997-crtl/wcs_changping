#ifndef _RAND_WANGHONGTAO_20151024_
#define _RAND_WANGHONGTAO_20151024_

#include <boost/random.hpp>


class MyRand{

public:

	MyRand(){};
	~MyRand(){};

	int randInt(int min,int max)
	{
		boost::uniform_int<> real(min, max);
		return real(gen);
	};

	double randFloat(double min,double max)
	{
		boost::uniform_real<double> real(min, max);
		return real(gen);
	};

// 	double rand01(){
//         //0-1上的实数
// 		boost::random::uniform_01<boost::random::mt19937&> u01(gen);
// 
//         //正态分布，参数分别为均值、方差
// 		boost::random::detail::normal_distribution<> nd(0, 1);
// 		
// 		double res = nd(u01);
//         return res;
// 	};


private:
	boost::random::mt19937 gen;

};

class TimeRand{

public:

	TimeRand(){};
	~TimeRand(){};

	int randInt(int min,int max,boost::random::mt19937 &gen)
	{
		boost::uniform_int<> real(min, max);
		return real(gen);
	};

	double randFloat(double min,double max,boost::random::mt19937 &gen)
	{
		boost::uniform_real<double> real(min, max);
		return real(gen);
	};




};
#endif//_RAND_WANGHONGTAO_20151024_
