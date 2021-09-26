#include <iostream>
#include "finstcpcommand.h"
#include <boost/lexical_cast.hpp>
#include "PLC_Manage.h"
#include "comm/simplelog.h"
#include <boost/thread.hpp>
#include "ADODatabase/ApiClient.h"

PLC_Manage::PLC_Manage() {
	plc_status_ = true;
	fail_count_ = 0;

}

PLC_Manage::~PLC_Manage() {
	StopScan();
}

std::map<std::string, std::map<int, std::string>> PLC_Manage::GetPLCMap() {
	return plc_map_;
}
// 1.初始化部分
bool PLC_Manage::Initial() {
	bool result = true;
	// 初始化连接状态
	WCS_CON_ = DATABASE_MANAGE.Get_WCS_DB();
	ResetReadStatus();
	ResetSendStatus();
	// 更新库位状态：禁止所有库位
	WCS_CON_->plcForbidAllStorage();
	if (GetCononect())
	{// 获取连接成功，读取PLC消息
		result = TestCononect();
	}
	StartScan();
	return result;
}

/*
1.1 获取连接。没有PLC返回True
*/
bool PLC_Manage::GetCononect() {
	try
	{
		bool result = true;
		result = WCS_CON_->LoadPLCMap(&plc_map_, table_name_, table_fields_);
		// 获取连接
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		for (auto var : plc_map_) {
			auto plc = var.second;
			if (all_con.find(plc[PLC_IP]) == all_con.end())
			{
				finsTcpCommand* finstcpcommand = MULTIPLC_MANAGE.init_plc(plc[PLC_IP], atoi(plc[PLC_PORT].c_str()), atoi(plc[PLC_REMOTE_NODE].c_str()));
				if (finstcpcommand)
				{
					all_con[plc[PLC_IP]] = finstcpcommand;
				}
				else
				{
					// PLC 连接失败
					result = false;
				}
			}
		}
		return result;
	}
	catch (...)
	{
		return false;
	}
}

// 1.2 测试连接 TODO：多线程危险
bool PLC_Manage::TestCononect() {
	bool result = true;
	std::map <std::string, bool> tmp_ip_pond;
	if (!plc_map_.empty())
	{
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		for each (auto var in plc_map_)
		{
			std::map<int, std::string> plc = var.second;
			if (tmp_ip_pond.find(plc[PLC_IP]) == tmp_ip_pond.end())
			{
				tmp_ip_pond[plc[PLC_IP]] = ForcedReadMsg(plc[DEV_NAME]);
				result = result && tmp_ip_pond[plc[PLC_IP]];

				if (result == false) {
					break;
				}
			}
		}
	}
	fail_count_ = 0;
	plc_status_ = result;
	return result;
}

// 1.3 重置发送状态
void PLC_Manage::ResetSendStatus() {
	WCS_CON_->updatePLCMsgStatus(IDLE);
}
// 1.4 重置读取状态
void PLC_Manage::ResetReadStatus() {
	WCS_CON_->updatePLCReadStatus(IDLE);
}

// 2 主线程
// 2.1 数据库与cache IO
bool PLC_Manage::DatabaseIO(WCS_Database *WCS_CON_) {
	if ( WCS_CON_ == nullptr)
	{
		WCS_CON_ = this->WCS_CON_;
	}
	bool result = false;
	if (plc_map_.empty())
	{
		result = WCS_CON_->LoadPLCMap(&plc_map_, table_name_, table_fields_);
		return result;
	}

	// 从数据库加载数据
	std::map<std::string, std::map<int, std::string>> tmp_plc_map;
	result = WCS_CON_->LoadPLCMap(&tmp_plc_map, table_name_, table_fields_);

	for each (auto var in tmp_plc_map)
	{
		std::string plc_name = var.first;
		std::map<int, std::string> point_plc = var.second; // 数据库中的数据

		// 发送状态
		if (plc_map_[plc_name][MSG_STATUS] == SENDED && point_plc[MSG_STATUS] == IDLE)
		{
			boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
			plc_map_[plc_name][MSG_STATUS] = IDLE;
		}
		else if (plc_map_[plc_name][MSG_STATUS] == SENDED && point_plc[MSG_STATUS] == SENDING)
		{
			// 写数据库
			if (plc_map_[plc_name][PLC_TRIGGER] == point_plc[PLC_TRIGGER])
			{
				point_plc[MSG_STATUS] = SENDED;
				WCS_CON_->updatePLCMsgStatus(plc_map_[plc_name][DEV_NAME], plc_map_[plc_name][MSG_STATUS]);
			}
			else if (plc_map_[plc_name][PLC_TRIGGER] != point_plc[PLC_TRIGGER])
			{
				plc_map_[plc_name][PLC_TRIGGER] = point_plc[PLC_TRIGGER];
				plc_map_[plc_name][MSG_STATUS] = SENDING;
			}
		}
		else if (plc_map_[plc_name][MSG_STATUS] == IDLE && point_plc[MSG_STATUS] == SENDING)
		{
			boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
			plc_map_[plc_name][MSG_STATUS] = SENDING;
		}
		else if (plc_map_[plc_name][MSG_STATUS] != point_plc[MSG_STATUS])
		{
			//数据库缓存不一致，按照数据库来，同时报错
			boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
			std::stringstream ss;
			ss << "PLC_Manage::DatabaseIO: " << plc_name << " : cache:" << plc_map_[plc_name][MSG_STATUS] << " ,database:" << point_plc[MSG_STATUS];
			log_info_color(log_color::red, ss.str().c_str());
			plc_map_[plc_name][MSG_STATUS] = point_plc[MSG_STATUS];
		}

		// 读取状态
		if (point_plc[READ_STATUS] != AUTO)
		{
			if (plc_map_[plc_name][READ_STATUS] == READED && point_plc[READ_STATUS] == IDLE)
			{
				plc_map_[plc_name][READ_STATUS] = IDLE;
			}
			else if (plc_map_[plc_name][READ_STATUS] == READED && point_plc[READ_STATUS] == READING)
			{
				// 写数据库
				point_plc[READ_STATUS] = READED;
				point_plc[PLC_TRIGGER] = plc_map_[plc_name][PLC_TRIGGER];
				WCS_CON_->updatePLCStatus(plc_map_[plc_name][DEV_NAME], plc_map_[plc_name][PLC_TRIGGER]);
				WCS_CON_->updatePLCReadStatus(plc_map_[plc_name][DEV_NAME], plc_map_[plc_name][READ_STATUS]);
			}
			else if (plc_map_[plc_name][READ_STATUS] == IDLE && point_plc[READ_STATUS] == READING)
			{
				plc_map_[plc_name][READ_STATUS] = READING;
			}
			else if (plc_map_[plc_name][READ_STATUS] != point_plc[READ_STATUS])
			{
				//数据库缓存不一致，按照数据库来，同时报错
				boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
				std::stringstream ss;
				ss << "PLC_Manage::DatabaseIO: " << plc_name << " : cache:" << plc_map_[plc_name][READ_STATUS] << " ,database:" << point_plc[READ_STATUS];
				log_info_color(log_color::red, ss.str().c_str());
				plc_map_[plc_name][READ_STATUS] = point_plc[READ_STATUS];
			}
		}
		else
		{
			// 写数据库
			if (plc_map_[plc_name][READ_STATUS] != AUTO)
			{
				// 第一次更改为 AUTO
				plc_map_[plc_name][READ_STATUS] = AUTO;
			}
			else if (plc_map_[plc_name][PLC_TRIGGER] != point_plc[PLC_TRIGGER])
			{
				// 不同时更改数据库
				WCS_CON_->updatePLCStatus(plc_map_[plc_name][DEV_NAME], plc_map_[plc_name][PLC_TRIGGER]);
			}
		}
	}
	UpdateStorage();
	return result;
}

// 2.2.1 发送消息
bool PLC_Manage::SendMsg(std::string dev_name, std::string status) {
	try
	{
		bool result = false;
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		auto plc = &plc_map_[dev_name];

		std::stringstream ss;
		ss << "PLC_Manage::SendMsg to " << plc->at(DEV_NAME) << " value " << status;
		log_info(ss.str().c_str());
		if (plc->at(MSG_STATUS) == IDLE || plc->at(PLC_TRIGGER) != status)
		{
			// 更新 缓存 与 数据库
			plc->at(PLC_TRIGGER) = status;
			WCS_CON_->updatePLCStatus(plc->at(PLC_VIRTUAL_PORT), plc->at(PLC_TRIGGER));
			plc->at(MSG_STATUS) = SENDING;
			WCS_CON_->updatePLCMsgStatus(plc->at(PLC_VIRTUAL_PORT), plc->at(MSG_STATUS));
			result = false;
		}
		else if (plc->at(MSG_STATUS) == SENDED && plc->at(PLC_TRIGGER) == status)
		{
			// 发送成功
			result = true;
		}
		else if (plc->at(MSG_STATUS) == SENDING)
		{
			// 正在等待发送
			result = false;
		}

		return result;
	}
	catch (...)
	{
		return 0;
	}
}
// 2.2.2 发送消息
bool PLC_Manage::SendMsg(std::string dev_name, int status, bool reset_request /*= false*/) {
	bool result = SendMsg(dev_name, std::to_string(status));
	if (result && reset_request == false)
	{
		ResetSendStatus(dev_name);
	}
	return result;
}
// 2.2.3 发送消息
bool PLC_Manage::SendMsg(std::string dev_name, bool status, bool reset_request /*= false*/) {
	bool result = SendMsg(dev_name, status ? TRUE_STR : FALSE_STR);
	if (result && reset_request == false)
	{
		ResetSendStatus(dev_name);
	}
	return result;
	//return SendMsg(dev_name, status ? TRUE_STR : FALSE_STR);
}

// 2.3.1 读取消息
bool PLC_Manage::ReadMsg(std::string dev_name, bool* plc_status, bool reset_request /*= false*/) {
	try
	{
		bool result = false;
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		auto plc = &plc_map_[dev_name];

		if (plc->at(DEV_TYPE) == BOOL_TYPE)
		{
			if (plc->at(READ_STATUS) == READED || plc->at(READ_STATUS) == AUTO)
			{// 读取完成
				*plc_status = plc->at(PLC_TRIGGER) == TRUE_STR;
				//WCS_CON_->updatePLCReadStatus(plc[PLC_VIRTUAL_PORT], plc[READ_STATUS]);
				result = true;
			}
			else if (plc->at(READ_STATUS) == READING)
			{//正在读取
				result = false;
			}
			else if (plc->at(READ_STATUS) == IDLE)
			{
				plc->at(READ_STATUS) = READING;
				//WCS_CON_->updatePLCReadStatus(plc[PLC_VIRTUAL_PORT], plc[READ_STATUS]);
				result = false;
			}
		}
		else {
			// 错误的类型
		}
		if (result && reset_request == false)
		{
			ResetReadStatus(dev_name);
		}
		return result;
	}
	catch (...)
	{
		return 0;
	}
}
// 2.3.2 读取消息
bool PLC_Manage::ReadMsg(std::string dev_name, int* plc_status, bool reset_request /*= false*/) {
	try
	{
		bool result = false;
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		auto plc = &plc_map_[dev_name];

		if (plc->at(DEV_TYPE) == SHORT_TYPE)
		{
			if (plc->at(READ_STATUS) == READED || plc->at(READ_STATUS) == AUTO)
			{// 读取完成
				*plc_status = atoi(plc->at(PLC_TRIGGER).c_str());
				result = true;
			}
			else if (plc->at(READ_STATUS) == READING)
			{//正在读取，读取成功后改为 READED ，从数据库取后重置为 IDLE
				result = false;
			}
			else if ((plc->at(READ_STATUS) == IDLE) && plc->at(MSG_STATUS) != SENDING)
			{
				plc->at(READ_STATUS) = READING;
				//WCS_CON_->updatePLCReadStatus(plc[PLC_VIRTUAL_PORT], plc[READ_STATUS]);
				result = false;
			}
		}
		else {
			// 错误的类型
		}
		if (result && reset_request == false)
		{
			ResetReadStatus(dev_name);
		}
		return result;
	}
	catch (...)
	{
		return 0;
	}
}

// 2.4 重置发送状态
void PLC_Manage::ResetSendStatus(std::string plc_name) {
	plc_map_[plc_name][MSG_STATUS] = IDLE;
	// 数据库
}
// 2.5 重置读取状态
void PLC_Manage::ResetReadStatus(std::string plc_name) {
	plc_map_[plc_name][READ_STATUS] = plc_map_[plc_name][READ_STATUS] == AUTO ? AUTO : IDLE;
}


// 2.6 主线程 光电检测库位
void PLC_Manage::UpdateStorage() {
	boost::shared_lock<boost::shared_mutex> lk(storage_mutex);
	for (auto var : storage_plc_)
	{
		std::string plc_name = var.first;
		std::deque<int> point_plc_status = var.second;
		if (point_plc_status.size() >= 28)
		{
			int count = 0;
			for each (auto var in point_plc_status)
			{
				count += var;
			}
			if (count > 25) {
				WCS_CON_->setCurrentStorageStatus("s_storage_station_status", "FULL", plc_name);
			}
			else if (count < 5)
			{
				WCS_CON_->setCurrentStorageStatus("s_storage_station_status", "EMPTY", plc_name);
			}
		}
	}
	return;
}


// 以下新开线程，内存与PLC交互

//************************************
// Method:    UpdataFromPLC
// Description: 开启线程，定制扫描指定PCL
// Author:    Meixu
// Date:      2021/04/14
// Returns:   void
//************************************
void PLC_Manage::StartScan() {
	if (!plc_status_update_)
	{
		plc_status_update_.reset(new boost::thread(boost::bind(&PLC_Manage::timerEvent, this)));
	}
}
//3.2 关闭线程
bool PLC_Manage::StopScan() {
	if (plc_status_update_)
	{
		plc_status_update_->interrupt();
		plc_status_update_->join();
	}
	return true;
}
//3.3 线程主函数
void PLC_Manage::timerEvent() {
	try
	{
		while (!plc_status_update_->interruption_requested())
		{
			//中断点，interrupted退出点
			boost::this_thread::interruption_point();
			if (!plc_map_.empty())
			{
				SendMsgToPLC();// 发送待发送消息至PLC
				ReadMsgFromPLC(true);
			}
			//每隔1秒扫描一次
			// boost::this_thread::sleep(boost::chrono::milliseconds(200));
		}
	}
	catch (const std::exception&) {

	}
	catch (int)
	{
		//log_info("PLC_Manage::UpdataFromPLC interrupted!");
	}
	catch (...)
	{
		//log_info("PLC_Manage::UpdataFromPLC interrupted!");
	}
}

// 从 数据库 更新数据，待发送消息发送到 PLC
bool PLC_Manage::SendMsgToPLC() {
	try
	{
		bool result = false;
		// 遍历获取到的数据
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		for each (auto var in plc_map_)
		{
			std::string plc_name = var.first;
			auto plc = var.second;
			if (plc[MSG_STATUS] == SENDING && plc_status_)
			{
				// 该地址可连通
				if (all_con[plc[PLC_IP]]) {
					// 写到远程PLC
					bool send_result = false;

					if (plc[DEV_TYPE] == BOOL_TYPE)
					{
						// 判断plc[PLC_TRIGGER]格式是否正确，正确则写入 n_status
						if (plc[PLC_TRIGGER] == TRUE_STR || plc[PLC_TRIGGER] == FALSE_STR)
						{
							bool n_status = plc[PLC_TRIGGER] == TRUE_STR;
							send_result = all_con[plc[PLC_IP]]->fins_writebit(plc[PLC_VIRTUAL_PORT].c_str(), &n_status, 1);// 发送
							if (send_result)
							{// 发送成功，更改数据库为发送成功
								plc_map_[plc_name][MSG_STATUS] = SENDED;
								// result = WCS_CON_->updatePLCMsgStatus(plc[PLC_VIRTUAL_PORT], plc[MSG_STATUS]);
							}
							else
							{// 发送失败
								FailConnectCount();
							}
						}
						else
						{
							// 内容不正确
							std::stringstream ss2;
							ss2 << "PLC_Manage::SendMsgToPLC Error: plc = " << plc[DEV_NAME] << "  PLC_TRIGGER = " << plc[PLC_TRIGGER];
							log_error(ss2.str().c_str());
						}
					}
					else if (plc[DEV_TYPE] == SHORT_TYPE)
					{
						short n_status = boost::lexical_cast<short>(plc[PLC_TRIGGER]);
						send_result = all_con[plc[PLC_IP]]->fins_writeword(plc[PLC_VIRTUAL_PORT].c_str(), &n_status, 1);// 发送数据
						if (send_result)
						{// 发送成功，更改数据库为不需要发送
							plc_map_[plc_name][MSG_STATUS] = SENDED;
							// result = WCS_CON_->updatePLCMsgStatus(plc[PLC_VIRTUAL_PORT], plc[MSG_STATUS]);
						}
						else
						{// 发送失败
							FailConnectCount();
						}
					}
					else
					{
						// 未知类型的PLC
						std::stringstream ss2;
						ss2 << "PLC_Manage::SendMsgToPLC Error: plc = " << plc[DEV_NAME] << "DEV_TYPE = " << plc[DEV_TYPE];
						log_error(ss2.str().c_str());
					}// 判断PLC类型
				}
				else {
					// 没有这个连接
					log_error("PLC_Manage::SendMsgToPLC  -  PLC connect failed !");
					break;
				}// PLC建立连接
			}// 判断是否需要发送消息
		}
		return true;
	}
	catch (...)
	{
		return 0;
	}
}

void PLC_Manage::ReadMsgFromPLC(bool auto_update) {
	try
	{
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		for each (auto var in plc_map_)
		{
			std::string plc_name = var.first;
			auto plc = var.second;
			if (plc[READ_STATUS] == READING) {
				// 读取一次，成功后改为IDLE
				if (ForcedReadMsg(plc[DEV_NAME])) {
					plc_map_[plc_name][READ_STATUS] = READED;
					// WCS_CON_->updatePLCReadStatus(plc[PLC_VIRTUAL_PORT], plc[READ_STATUS]);
				}
			}
			else if (auto_update && plc[READ_STATUS] == AUTO)
			{
				if (ForcedReadMsg(plc_name))
				{
					// 读取成功
					boost::unique_lock<boost::shared_mutex> lk(storage_mutex);
					if (storage_plc_.find(plc[DEV_NAME]) != storage_plc_.end())
					{
						// 在库位光电检测列表中，所以更新库位状态
						// 进队
						storage_plc_[plc_name].push_back(plc_map_[plc_name][PLC_TRIGGER] == TRUE_STR);
						if (storage_plc_[plc_name].size() > 30)
						{
							storage_plc_[plc_name].pop_front();
						}
					}
				}
				else
				{
					// 读取失败，队首出队一个
					if (!storage_plc_[plc_name].empty())
					{
						storage_plc_[plc_name].pop_front();
					}
				}
				
			}
			else if (plc[READ_STATUS] == READED)
			{

			}
			else if (plc[READ_STATUS] == IDLE)
			{

			}
		}
	}
	catch (...)
	{
		return;
	}
}

bool PLC_Manage::ForcedReadMsg(std::string plc_name) {
	bool result = false;
	try
	{
		if (all_con[plc_map_[plc_name][PLC_IP]]) {
			auto plc = plc_map_[plc_name];
			if (plc[DEV_TYPE] == SHORT_TYPE)
			{
				short status = -1;
				if (all_con[plc[PLC_IP]] && all_con[plc[PLC_IP]]->fins_readword(plc[PLC_VIRTUAL_PORT].c_str(), &status, 1)) {
					//ResetSendStatus(plc->at(PLC_VIRTUAL_PORT]);
					plc_map_[plc_name][MSG_STATUS] = plc[MSG_STATUS] == SENDING ? SENDING : IDLE;
					plc_map_[plc_name][PLC_TRIGGER] = std::to_string(boost::lexical_cast<int>(status));
					plc_map_[plc_name][READ_STATUS] = plc[READ_STATUS] == AUTO ? AUTO : READED;
					// WCS_CON_->updatePLCStatus(plc->at(PLC_VIRTUAL_PORT], plc->at(PLC_TRIGGER]);
					result = true;
				}
				else
				{
					//读取错误
					FailConnectCount();
					result = false;
				}
			}
			else if (plc[DEV_TYPE] == BOOL_TYPE)
			{
				bool status = true;
				if (all_con[plc[PLC_IP]] && all_con[plc[PLC_IP]]->fins_readbit(plc[PLC_VIRTUAL_PORT].c_str(), &status, 1))
				{
					//ResetSendStatus(plc->at(PLC_VIRTUAL_PORT]);
					plc_map_[plc_name][MSG_STATUS] = plc[MSG_STATUS] == SENDING ? SENDING : IDLE;
					plc_map_[plc_name][PLC_TRIGGER] = status ? TRUE_STR : FALSE_STR;
					plc_map_[plc_name][READ_STATUS] = plc[READ_STATUS] == AUTO ? AUTO : READED;
					result = true;
				}
				else
				{
					//读取错误
					FailConnectCount();
					result = false;
				}
			}
			else
			{
				// 未知类型PLC
				result = false;
			}
		}
		else {
			GetCononect();
			log_info("PLC connect failed !");
		}
		return result;
	}
	catch (...) {

		std::stringstream ss;
		ss << "PLC_Manage::ForcedReadMsg";

		//		log_info_color(log_color::red, ss.str().c_str());
		return false;
	}

}

//************************************
// Method:    FailConnectCount
// Description: 错误计数，与fail_count_、max_fail_connect_、plc_status_相关
// Author:    Meixu
// Date:      2021/04/15
// Returns:   void
//************************************
void PLC_Manage::FailConnectCount() {
	try
	{
		if (fail_count_ == 1)
		{
			// 更新库位状态：禁止所有库位
			WCS_CON_->plcForbidAllStorage();
		}
		fail_count_++;
		if (fail_count_ <= max_fail_connect_)
		{
			std::stringstream ss;
			ss << "PLC_Manage::FailConnectCount Fail (" << std::to_string(fail_count_) << ") Times";
			log_error(ss.str().c_str());
			plc_status_ = false;
		}
	}
	catch (...)
	{
		return;
	}
}