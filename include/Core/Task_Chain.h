
#ifndef _TASK_CHAIN_ED_H
#define _TASK_CHAIN_ED_H
#include <string>  
#include <map> 
#include <list>
#include <iostream>  
#include <boost/thread.hpp>
#include "Core/Task_Define.h"
#include "Core/Sub_Task.h"
#include "Common/Config.h"
#include "Manage/Battery_Manage.h"
#include "Manage/AGV_Manage.h"


class Task_Chain
{
public:

	Task_Chain();

	~Task_Chain();

	TASK_CHAIN_STATUS Task_Chain_Initial(int index, std::string order_id, std::string start, std::string target, std::string mode, std::string type, AGV* associate_AGV, int task_id, std::string palletno);

	TASK_CHAIN_STATUS Initial(int index, int order_id, Pallet_Task* associate_pallet_task, AGV* associate_AGV);

	TASK_CHAIN_STATUS Parking_Initial(int index, AGV* associate_AGV);

	TASK_CHAIN_STATUS forceParkingInitial(int index, AGV* associate_AGV);

	TASK_CHAIN_STATUS Charging_Initial(int index, AGV* associate_AGV);

	bool Check_Platfrom(std::string& Platfrom);

	TASK_CHAIN_STATUS Get_Status();

	void Set_Status(int status);

	AGV* Get_Associate_AGV();

	std::string Get_Start_Time();

	std::string Get_Over_Time();

	std::string Get_Duration();

	std::string Get_Sub_Task_Duration();

	std::string getStart();

	std::string getPalletno();

	std::string getConfirmStation();

	std::string getTargeted();

	std::string getTurnStation();

	std::string getInConfirmStation();

	std::string getOutConfirmStation();

	std::string getStackWaitStation();

	std::string getSafeStation();

	std::string getMode();

	std::string getType();

	std::string getTrayGet();

	std::string getTrayPut();

	std::string getGoodsGet();

	std::string getGoodsPut();

	std::string Get_Last_Direct();

	void setStart(std::string START);

	void setTargeted(std::string TARGETED);

	void setTrayGet(std::string tray_get);

	void setTrayPut(std::string tray_put);

	void setGoodsGet(std::string tray_get);

	void setGoodsPut(std::string tray_put);

	Task_Dispatch Get_Task_Dispatch()
	{
		return 	Task_Dispatch_;
	}
	void Check_Feedback(Sub_Task *Current_Sub_Task);

	std::list<Sub_Task *> Sub_Task_Chain_;

	void Set_Status(TASK_CHAIN_STATUS chain_status);

	void Set_Over_Time_And_Duration();

	Sub_Task* Move_To_Next_Sub_Task(Sub_Task * Current_Sub_Task, std::string current_carry_type);

	void Set_Last_Direct(std::string direct);


	AGV* Associate_AGV_;

	Config_File Config_;

	bool Dispatched_;

	int ALL_Task_ID_;

	int Task_ID_;

	std::string Order_ID_;

	int Index_;

protected:

	TASK_CHAIN_STATUS createTrayStorageTaskChain();

	TASK_CHAIN_STATUS createGoodsStorageTaskChain();

	TASK_CHAIN_STATUS createMoveStorageTaskChain();

	TASK_CHAIN_STATUS createParingTaskChain();

	TASK_CHAIN_STATUS createChargingTaskChain();

	TASK_CHAIN_STATUS createForcedChargeTaskChain();

private:

	bool Create_Sub_Task(std::string from, std::string to, int priority, int agv_type, SUB_TASK_TYPE task_type, int auto_dp, int agv_id, std::string carry_type, std::string task_mode, TASK_CHAIN_STATUS Begin_Status = TASK_CHAIN_STATUS::NONE, TASK_CHAIN_STATUS Over_Status = TASK_CHAIN_STATUS::NONE);

	bool Create_Sub_Task(std::string from, std::string to, int priority, int agv_type, SUB_TASK_TYPE task_type, int auto_dp, int agv_id, std::string carry_type, std::string task_mode, int task_extra_param_type, std::string task_extra_param, TASK_CHAIN_STATUS Begin_Status = TASK_CHAIN_STATUS::NONE, TASK_CHAIN_STATUS Over_Status = TASK_CHAIN_STATUS::NONE);

	void Begin_Sub_Task_Flow();

	void Unlocked_Storage(int chain_status);

	std::string Locking_Storage(int chain_status, Sub_Task *Current_Sub_Task);

	void Set_Start_Time();

	void Set_Sub_Task_Time_Over_And_Duration();

	void Set_Sub_Task_Time_Start();

	void setTurnStation(std::string turn_station);

	void setSafeStation(std::string safe_station);

	void setConfirmStation(std::string confirm_station);

	void setMode(std::string mode);

	void setType(std::string type);

	void setPalletno(std::string palletno);

	void Set_Task_Chain_Type(TASK_CHAIN_TYPE type);

	void Update_Task_Log();

	void stopChargingLog();

	void getBatteryConfig();

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	//判断出入库的任务终点是否为货位（用于判断任务是出库还是入库）
	bool TargetIsGoodsIn0rGoodsOutStation(const std::string target);

	float battery_high_range_;

	float battery_low_range_;

	float unlock_battery_level_;

	std::string EQUIP_NAME_;

	std::string PALLET_BUFFER_;

	std::string START_;

	std::string TARGETED_;

	std::string TRAY_GET_;

	std::string TRAY_PUT_;

	std::string GOODS_GET_;

	std::string GOODS_PUT_;

	std::string stackStation_;

	std::string turn_station_;

	std::string safe_station_;

	std::string confirm_station_;

	std::string in_confirm_station_;

	std::string out_confirm_station_;

	std::string MODE_;

	std::string PALLETNO_;

	std::string TYPE_;

	std::string Direct_;

	std::string Locked_;

	std::string Locked_last_;

	time_t start_time;

	time_t sub_task_start_time;

	std::string Start_Time_;

	std::string Over_Time_;

	std::string Duration_;

	std::string Sub_Task_Start_Time_;

	std::string Sub_Task_Over_Time_;

	std::string Sub_Task_Duration_;

	TASK_CHAIN_TYPE Task_Type_;

	int Task_Status_;

	bool Begin_Run_;

	bool Stop_Charge_;

	TASK_CHAIN_STATUS Chain_Status_;

	Order* Associate_Order_;

	Pallet_Task* Associate_Pallet_Task_;

	Task_Dispatch Task_Dispatch_;

	boost::mutex mu_chain_status_;
	boost::mutex mu_START_;
	boost::mutex mu_MID_;
	boost::mutex mu_TARGETED_;
	boost::mutex mu_stackStation_;
	boost::mutex mu_turn_station_;
	boost::mutex mu_safe_station_;
	boost::mutex mu_confirm_station_;
	boost::mutex mu_in_confirm_station_;
	boost::mutex mu_out_confirm_station_;
	boost::mutex mu_MODE_;
	boost::mutex mu_TYPE_;

	WCS_Database * WCS_DB_;
};

#endif //_TASK_CHAIN_ED_H