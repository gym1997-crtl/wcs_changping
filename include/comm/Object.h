#ifndef AGV_SIMULATER_OBJECT_20121101_
#define AGV_SIMULATER_OBJECT_20121101_

#include <map>
#include "comm/MyDefine.h"

class Object
{
public:
	Object();
	~Object();

	virtual int type() const = 0;

	//typedef enum{NONE,DATA,FRAME,TRANSFER,NODE_TOPOLOGY,EDGE_LINE,EDGE_BEZIER} Otype;
	typedef enum{NONE,DATA,FRAME,TRANSFER,NODE,EDGE,STATION,STORAGE,LAB,TASK_PATH,TASK_FORK,TASK_CARGO,TASK_AGV} Otype;
	
	U32 ID();

	virtual void Code(std::ofstream& of)=0;
	virtual bool DeCode(std::string data)=0;

	void Init();
	void Init(U32 id);

	static void ClearType(int type);		//清空类型
private:
	
	static U32 GetNewID(int type);	//类型新id
	
	U32 id_;

	static std::map<int,U32> id_arrange_list_;//id号分配 

};

#endif //AGV_SIMULATER_OBJECT_20121101_