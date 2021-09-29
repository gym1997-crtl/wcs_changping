
#ifndef _TASK_DEFINE_ED_H
#define _TASK_DEFINE_ED_H

#include <iostream>

typedef enum {
	NEW = 0,
	PENDING,
	DISPATCH,
	DISPATCHED,
	CHECK,
	ONGOING,
	REJECTED,
	FAILED,
	ABORTED,
	FORCE_COMPLETED,
	DONE,
	CHARGING
}SUB_TASK_STATUS;


typedef enum {
	AGV_RESPONSE_SUCC =1,
	AGV_RESPONSE_FAILED =2
}AGV_RESPONSE_WC;

typedef enum {
	TRAY = 0,
	GOODS = 1
}CageType;

typedef enum {
	IN_STORAGE = 1,
	OUT_STORAGE = 0
}WorkType;

typedef enum {
	BEGIN_GET = 1,
	GET_OVER = 2
}AGV_RESPONSE_RECEIVING;

typedef enum {
	AGV_TASK = 0,

	//DIRECT_FORWARD_GET = 11,			//正向行走并取货;
	//DIRECT_FORWARD_PUT = 12,			//正向行走并放货;
	//DIRECT_FORWARD_PATH = 13,			//直接去;
	//DIRECT_BACKWARD_PATH = 14,			//直接倒车去;
	//AGV_IN_SITU_CHARGING = 499,			//原地充电;
	//BACKWARD_GET = 15,                  //倒车去取货;
	//BACKWARD_PUT = 16,					//倒车去放货;
	//	T_FORWARD_BACKWARD = 3003,          //T车正向行走后再倒车;
	//L_FORWARD_BACKWARD = 3007           //L车正向行走后再倒车;

	DIRECT_FORWARD_GET = 1111,				//正向行走并取货;
	DIRECT_FORWARD_PUT = 1112,				//正向行走并放货;
	DIRECT_FORWARD_PATH = 1001,				//直接去;
	DIRECT_BACKWARD_PATH = 1002,			//直接倒车去;
	AGV_IN_SITU_CHARGING = 1040,			//原地充电;
	FAKE_AGV_IN_SITU_CHARGING = 1041,		//假原地充电;
	BACKWARD_GET = 1113,					//倒车去取货;
	BACKWARD_PUT = 1114,					//倒车去放货;
	FORWARD_STACK_PUT = 1108,				//正向行走并二层及以上堆叠放货;
	FORWARD_STACK_GET = 1109,				//正向行走并二层及以上堆叠取货;
	FORWARD_BACKWARD = 1005,				//正向行走后再倒车;
	FORK_DOWN_FORWARD_BACKWARD = 1116,	    //正向行走后再倒车;
	DIRECT_FORWARD_DOWN_FORK = 1117,        //正向行走到站点并降叉到库位高度;
	PARKING_FORWARD = 1004,        //停车任务，正向进入停车点，车头朝里
	LOCAL_WAITING_WARNING = 1055,
	LANDMARK_BEGIN_TASK = 1050,
	WEIGHTING_TASK = 1056,                  //称重任务
	LANDMARK_STOP_TASK = 1051,
	FAKE_DIRECT_FORWARD_GET = 1120,          //虚拟取货任务
	FORWARD_BACKWARD_PUT=1003 //正向行驶后倒车入库


}SUB_TASK_TYPE;


typedef enum {
	NONE_TASK = 0,
	CARRY_TASK = 1,
	PARKING_TASK = 2,
	CHARGING_TASK = 3,
	STACK_TASK = 4

}TASK_CHAIN_TYPE;


typedef enum {
	NONE = 0,
	BLOCKED,
	BEGIN,
	PARKING,
	BEGING_CHARGING,
	IS_CHARGING,

	PARKING_TURN,
	PARKING_TURN_CHECK,

	EQUIP_GET,
	EQUIP_GET_CHECK,
	BUFFER_PUT,
	BUFFER_PUT_CHECK,
	BUFFER_GET,
	BUFFER_GET_CHECK,
	EQUIP_PUT,
	EQUIP_PUT_CHECK,
	EQUIP_PUT_CONFIRM,
	EQUIP_PUT_CONFIRM_CHECK,
	EQUIP_PUT_RELEASE,
	EQUIP_PUT_RELEASE_CHECK,
	EQUIP_GET_CONFIRM,
	EQUIP_GET_CONFIRM_CHECK,
	BEGIN_CHECK,
	PARKING_CHECK,

	/*北京昌平项目状态*/
	GOODS_IN_GET_CONFIRM,//入库起始状态
	GOODS_IN_GET_CONFIRM_CHECK, //AGV入库行驶到取货点
	GOODS_IN_GET,//倒车取货
	GOODS_IN_GET_CHECK, //取货完成
	GOODS_IN_PUT, //去放货
	GOODS_IN_PUT_CHECK, //放货完成

	GOODS_OUT_GET,        //出库起始状态
	GOODS_OUT_GET_CHECK,   //移动到指定地点
	GOODS_OUT_PUT_CONFIRM,    //移动到放货确认点
	GOODS_OUT_PUT_CONFIRM_CHECK, //到达指定地点
	GOODS_OUT_PUT,  //去放货
	GOODS_OUT_PUT_CHECK, //放货完成


	OVER,
	ABORT,
	ERR
}TASK_CHAIN_STATUS;


typedef enum {

	CHANRING_PENDING,
	CHARGING_PAUSE,
	CHANRING_FAILED,
	CHANRING_CHARGING,
	CHANRING_STOP
}CHARGING_STATUS;

typedef enum {
	BEGING_INVOKE,
	STOP_INVOKE

}INVOKE_STATUS;
typedef struct _Task_Data
{
	int mean;
	int noise_deviation;
	std::string from;
	std::string to;

}Task_Data;

typedef struct _Task_Chain_Info
{
	std::string ORDER_ID_;
	std::string START_;
	std::string START_CONFIRM_;
	std::string TARGET_;
	std::string TARGET_CONFIRM_;
	int PRIORITY_;
	TASK_CHAIN_STATUS Status_;
	std::string STATUS_;
	std::string MODE_;
	std::string TYPE_;
	int AGV_ID_;
	std::string Timestamp_;
	std::string SYSTEM_;
	std::string PALLETNO_;
}Task_Chain_Info;

#endif //_TASK_DEFINE_ED_H