#include "ApiClient.h"

#include <boost/serialization/singleton.hpp>
#include "DatabaseManage.h"
#include "comm/simplelog.h"
#include "Common/Common.h"
#include <QJsonObject>
#include <QUuid>

#include <Manage/Order_Manage.h>
#include <Manage/AGV_Manage.h>
#include <ADODatabase/ApiServer.h>
//class ClientMessage;
/// <summary>
/// APIs this instance.
/// </summary>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/19
/// 
ApiClient::ApiClient(QObject *parent) {
	// 默认前往 -1
	API_SERVER.InitialLauncher(-1, &this->UnknownOperation);
	// 请确保操作函数return前，msg->generateReturnBody调用完毕 [7/8/2021 Meixu]
	// 请确保返回内容不会嵌套层数过多，递归转化为xml时未作层数限制 [7/8/2021 Meixu]
	API_SERVER.InitialLauncher("RECEIVE_CARRY_TASK", &this->InsertOrder);
	API_SERVER.InitialLauncher("PALLET_TASK_CANCEL", &this->RevokeOrder);
	API_SERVER.InitialLauncher("TASK_PRIORITY_CHANGE", &this->UpdatePriority);
	API_SERVER.InitialLauncher("PALLET_PICK_DROP_TASK", &this->QueryAGVInfo);
	API_SERVER.InitialLauncher("REQUEST_ DEVICE_INFO", &this->QueryAGVInfo);
}

/// <summary>
/// Finalizes an instance of the <see cref="Api"/> class.
/// </summary>
/// Creator:MeiXu
/// CreateDate:2021/2/19
/// 
ApiClient::~ApiClient()
{
}

/// <summary>
/// Gets the server ip.
/// </summary>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/19
/// 
QString ApiClient::get_server_ip()
{
	return server_ip;
}

/// <summary>
/// Sets the server ip.
/// </summary>
/// <param name="ip_address">The ip address.</param>
/// Creator:MeiXu
/// CreateDate:2021/2/19
/// 
void ApiClient::set_server_ip(QString ip_address)
{
	server_ip = ip_address;
}

QString ApiClient::CurrentTime() {
	return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

/// <summary>
/// Creates the UUID.
/// </summary>
/// <param name="data">The data.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/7
QString ApiClient::createUuid(QString data) {
	qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
	QUuid id;
	id = QUuid::createUuidV5(id, QString(data + timestamp));
	return id.toString().replace("{", "").replace("}", "");
}

//////////////////////////////////////////////////////////////////////////
// 以下为向外提供的接口 [8/2/2021 Meixu]

bool ApiClient::InsertOrder(ApiMsg* msg) {
	bool result = false;
	// 处理请求
	Order order_in;
	order_in.ORDER_ID_ = msg->ReadString(msg->taskContent, "taskNo");
	order_in.START_ = msg->ReadString(msg->taskContent, "fromPoint");
	order_in.TARGETED_ = msg->ReadString(msg->taskContent, "toPoint");
	order_in.PRIORITY_ = (int)msg->ReadNumber(msg->taskContent, "priority");
	order_in.MODE_ ="MODE";
	order_in.TYPE_ = "CARRY";
	order_in.PALLETNO = msg->ReadString(msg->taskContent, "containerNo");
	result = STORAGE_MANAGE.Insert_Order(order_in.ORDER_ID_, order_in.START_, order_in.TARGETED_, order_in.PRIORITY_, "NEW", order_in.MODE_, order_in.TYPE_,-1,order_in.PALLETNO);
	// 构建响应消息
	msg->generateReturnBody(result, DatabaseError, VNAME(DatabaseError));

	return result;
}

bool ApiClient::RevokeOrder(ApiMsg * msg)
{
	bool result = false;
	// 处理请求
	std::string order_id = msg->ReadString(msg->taskContent, "taskNo");
	result = ORDER_MANAGE.Revoke_Order(order_id);
	// 响应消息
	msg->generateReturnBody(result, DatabaseError, VNAME(DatabaseError));
	return result;
}

bool ApiClient::QueryOrderInfo(ApiMsg* msg)
{
	bool result = false;
	// 处理请求
	std::string order_id = msg->ReadString(msg->taskContent, "orderId");
	Order* order = new Order();
	result = ORDER_MANAGE.QueryOrderInfo(order_id, order);
	QJsonObject a;
	// 响应消息
	if (result)
	{
		a.insert("orderId", order->ORDER_ID_.c_str());
		a.insert("start", order->START_.c_str());
		a.insert("target", order->TARGETED_.c_str());
		a.insert("priority", order->PRIORITY_);
		a.insert("status", order->STATUS_.c_str());
		a.insert("mode", order->MODE_.c_str());
		a.insert("agvId", order->AGV_ID_);
	}
	delete order;
	QJsonObject b;
	b.insert("taskContent", a);
	msg->generateReturnBody(result, DatabaseError, VNAME(DatabaseError), &b);
	return result;
}

bool ApiClient::QueryAGVInfo(ApiMsg * msg)
{
	bool result = false;
	// 处理请求
	int agv_id = (int)msg->ReadNumber(msg->taskContent, "deviceNo");
	std::map<int, AGV*> AGV_list = AGV_MANAGE.Get_All_AGV();

	QJsonObject a;
	// 响应消息
	if (AGV_list.find(agv_id) != AGV_list.end())
	{
		a.insert("robotCode", AGV_list[agv_id]->AGV_ID_);
		a.insert("posX", AGV_list[agv_id]->AGV_Pos_.x);
		a.insert("posY", AGV_list[agv_id]->AGV_Pos_.y);
		a.insert("status", AGV_list[agv_id]->AGV_Status_);
		a.insert("batteryLevel", AGV_list[agv_id]->Battery_Level_);
		a.insert("speed", "-1");
		a.insert("podCode", "123");
		a.insert("mapCode", "102");
		result = true;
	}
	QJsonObject b;
	b.insert("taskContent", a);
	msg->generateReturnBody(result, DatabaseError, VNAME(DatabaseError), &b);
	return result;
}

bool ApiClient::UpdatePriority(ApiMsg * msg)
{
	bool result = false;
	// 处理请求
	std::string order_id = msg->ReadString(msg->taskContent, "taskNo");
	std::string priority = msg->ReadString(msg->taskContent, "priority");
	result = ORDER_MANAGE.Update_Priority(order_id,priority);
	// 响应消息
	msg->generateReturnBody(result, DatabaseError, VNAME(DatabaseError));
	return result;
}


bool ApiClient::UnknownOperation(ApiMsg * msg)
{
	bool result = false;
	// TODO 打印日志
	// 响应消息
	msg->generateReturnBody(false, UnknownOperationCode, VNAME(UnknownOperationCode));
	return true;
}


//////////////////////////////////////////////////////////////////////////
// 以下为调用其他接口 [8/2/2021 Meixu]
bool ApiClient::EquipmentStatusChangeNotification(std::string agvId, std::string status, std::string errorCode, int agv_id) {
	// 组装消息
	QJsonObject json_data;
	json_data.insert("agvId", QJsonValue(QString::fromStdString(agvId)));
	QJsonObject body_data;
	body_data.insert("taskContent", json_data);

	// 发送请求并声明响应函数
	API_SERVER.send("127.0.0.1:625/", applicationsoapxml, body_data, &this->reply);
	return true;
}


//任务汇报完成
bool ApiClient::TaskFinishReport(std::string taskNo,std::string deviceNo, std::string containerNo, std::string point,std::string actionType ) {
	// 组装消息
	QJsonObject json_data;
	json_data.insert("taskNo", QJsonValue(QString::fromStdString(taskNo)));
	json_data.insert("deviceNo", QJsonValue(QString::fromStdString(deviceNo)));
	json_data.insert("containerNo", QJsonValue(QString::fromStdString(containerNo)));
	json_data.insert("point", QJsonValue(QString::fromStdString(point)));
	json_data.insert("actionType", QJsonValue(QString::fromStdString(actionType)));
	QJsonObject body_data;
	body_data.insert("taskJson", json_data);

	// 发送请求并声明响应函数
	API_SERVER.send("127.0.0.1:625/", applicationsoapxml, body_data, &this->reply);
	return true;
}

//询问取货、放货是否可以执行
bool ApiClient::QueryIsCanGetOrPut(std::string taskNo, std::string point, std::string flag) {
	
	std::map<std::string, int>::iterator itor = reponse_result.find(taskNo + "QueryIsCanGetOrPut");
	//已经收到回复
	if (2 == itor->second)
	{
		return true;
	}
	//已经收到回复
	if (1 == itor->second)
	{
		return false;
	}
	//判断是否为第一次调用
	if (itor == reponse_result.end())
	{
		reponse_result.insert(std::map<std::string, int>::value_type(taskNo + "QueryIsCanGetOrPut", 0));
	}
	// 组装消息
	QJsonObject json_data;
	json_data.insert("taskNo", QJsonValue(QString::fromStdString(taskNo)));
	json_data.insert("point", QJsonValue(QString::fromStdString(point)));
	json_data.insert("flag", QJsonValue(QString::fromStdString(flag)));
	QJsonObject body_data;
	body_data.insert("taskJson", json_data);

	// 发送请求并声明响应函数
	API_SERVER.send("127.0.0.1:625/", applicationsoapxml, body_data, &this->ReplyQueryIsCanGetOrPut);
	reponse_result[taskNo + "QueryIsCanGetOrPut"] = 1;
	return false;
}

//上报AGV状态
bool ApiClient::DeviceInfoReport(std::string deviceNo, std::string errorCode, std::string  message, std::string deviceType, int workMode)
{
	// 组装消息
	QJsonObject json_data;
	json_data.insert("deviceNo", QJsonValue(QString::fromStdString(deviceNo)));
	json_data.insert("errorCode", QJsonValue(QString::fromStdString(errorCode)));
	json_data.insert("message", QJsonValue(QString::fromStdString(message)));
	json_data.insert("deviceType", QJsonValue(QString::fromStdString(deviceType)));
	json_data.insert("workMode", QJsonValue(QString::number(workMode)));
	QJsonObject body_data;
	body_data.insert("taskJson", json_data);

	// 发送请求并声明响应函数
	API_SERVER.send("127.0.0.1:625/", applicationsoapxml, body_data, &this->reply);
	return true;
}


bool ApiClient::reply(QJsonObject response, QJsonObject body) {
	
	ApiMsg::ReadBool(response, "valid");
	
	return true;
}

bool ApiClient::ReplyQueryIsCanGetOrPut(QJsonObject response, QJsonObject body) {

	ApiMsg::ReadBool(response, "valid");
	std::string taskNo = ApiMsg::ReadString(body, "taskNo");
	reponse_result[taskNo + "QueryIsCanGetOrPut"] = 2;
	return true;
}