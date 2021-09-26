
#include "comm/Object.h"


std::map<int,U32> Object::id_arrange_list_;

Object::Object()
{
	id_ = 0;
}

Object::~Object()
{

}
U32 Object::ID()
{
	return id_;
}


U32 Object::GetNewID( int type )
{
	std::map<int,U32>::iterator it = id_arrange_list_.find(type);//没有就新增
	if (it != id_arrange_list_.end())//已经存在该类型
	{
		it->second = it->second +1;
		return it->second;
	}
	else
	{
		id_arrange_list_[type] = 0;
		return 0;
	}
	
}
void Object::ClearType(int type)
{
	std::map<int,U32>::iterator it = id_arrange_list_.find(type);//没有就新增
	if (it != id_arrange_list_.end())//已经存在该类型
	{
		id_arrange_list_.erase(it);
	}
}
void Object::Init()
{
	id_ = GetNewID(type());
}
// void Object::Init( int type ) 
// {
// 	id_ = GetNewID(type);
// }

void Object::Init( U32 id )
{
	id_ = id;
	
	if (id_arrange_list_.count(type()) ==0 )
	{
		id_arrange_list_[type()] = 0;
	}
	else
	{
		if (id_arrange_list_[type()] < id)
		{
			id_arrange_list_[type()] = id;
		}
	}
}



