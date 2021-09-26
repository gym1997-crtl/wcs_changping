#include "RabbitMQService.h"
#include "RabbitMqClient.h"
#include "Manage/Storage_Manage.h"
#include "comm/simplelog.h"

#include <deque>
#include <string.h>

#include "QJsonParseError"
#include "QJsonDocument"
#include <QJsonObject>

RabbitMQService::~RabbitMQService() {

	//mqClient_->DisConnect();
	delete mqClient_;
	mqClient_ = nullptr;

	delete exchange_;
	exchange_ = nullptr;
	
	for each (auto var in all_queue_)
	{
		delete var.second;
	}
	StopScan();
}

void RabbitMQService::setRabbitMQServiceNotifier(RabbitMQ_Service_Notifier * notifier) {
	rabbitmq_service_notifier = notifier;
}

bool RabbitMQService::Init() {
	
	if (Config_.FileExist("config.txt"))
	{
		Config_.ReadFile("config.txt");
		ReadRabbitMQService();
	}

	//mqClient_ = new CRabbitMqClient(host);
	//if (0 != mqClient_->Connect(virtualHost))
	//{
	//	log_error("RabbitMQService::Init: connect fail , please check your network");
	//}
	// 开启线程监听
	rabbitmq_service_listen_.reset(new boost::thread(boost::bind(&RabbitMQService::timerEvent, this)));
	rabbitmq_apply_unit_listen_.reset(new boost::thread(boost::bind(&RabbitMQService::checkUnit, this)));
	rabbitmq_apply_get_goods_listen_.reset(new boost::thread(boost::bind(&RabbitMQService::checkGetGoods, this)));
	return true;
}

void RabbitMQService::ReadRabbitMQService() {

	if (Config_.KeyExists("Rabbit_Mq_IP"))
	{
		host = Config_.Read<std::string>("Rabbit_Mq_IP");
		//std::cout<<"Read AMS DSN:"<<_AGV_Management_DSN<<std::endl;  
	}
	if (Config_.KeyExists("Rabbit_Mq_Host"))
	{
		virtualHost = Config_.Read<std::string>("Rabbit_Mq_Host");
		//std::cout<<"Read AMS DSN:"<<_AGV_Management_DSN<<std::endl;  
	}
	return;
}

bool RabbitMQService::StopScan() {
	if (rabbitmq_service_listen_)
	{
		rabbitmq_service_listen_->interrupt();
		rabbitmq_service_listen_->join();
	}
	if (rabbitmq_apply_unit_listen_)
	{
		rabbitmq_apply_unit_listen_->interrupt();
		rabbitmq_apply_unit_listen_->join();
	}
	if (rabbitmq_apply_get_goods_listen_)
	{
		rabbitmq_apply_get_goods_listen_->interrupt();
		rabbitmq_apply_get_goods_listen_->join();
	}
	return true;
}

void RabbitMQService::timerEvent() {
	try
	{
		const std::string queue_name = "agv.request.wc";
		std::deque<std::string> all_order_insert;// = new std::deque<int>;
		std::string message;
		uint64_t delivery_tag;

		CRabbitMqClient client(host);
		if (0 != client.Connect(virtualHost))
		{
			log_error("RabbitMQService::timerEvent: reconnect fail , please check your network");
		}
		CExchange exchange(exchange_name_, "topic");
		CQueue queue("zc." + queue_name);

		client.DeclareQueue(queue);
		client.BindQueueToExchange(queue, exchange, queue_name);
		client.StateConsumer("zc." + queue_name);

		while (!rabbitmq_service_listen_->interruption_requested())
		{
			//中断点，interrupted退出点
			boost::this_thread::interruption_point();
			message = "";
			delivery_tag = 0;
			if (client.ConsumerMessage(message, delivery_tag, "zc." + queue_name))
			{
				CRabbitMqClient client(host);
				if (0 != client.Connect(virtualHost))
				{
					boost::this_thread::sleep(boost::chrono::milliseconds(2000));
					log_error("RabbitMQService::timerEvent: reconnect fail , please check your network");
				}
				client.DeclareQueue(queue);
				client.BindQueueToExchange(queue, exchange, queue_name);
				client.StateConsumer("zc." + queue_name);
				continue;
			}

			// 转JSON
			if (!message.empty())
			{
				QJsonParseError jsonError;
				QJsonDocument doucment = QJsonDocument::fromJson(message.c_str(), &jsonError);
				if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
				{ // JSON读取没有出错
					if (doucment.isObject())
					{
						// 接收传入数据
						QJsonObject object = doucment.object();
						bool valid = false;
						std::string taskId = ReadString(object, "taskId");
						auto pos = find(all_order_insert.begin(), all_order_insert.end(), taskId);
						if (pos == all_order_insert.end()) {
							all_order_insert.push_back(taskId);
							int taskStatus = (int)ReadNumber(object, "taskStatus");
							std::string unitId = ReadString(object, "unitId");
							//TODO 临时测试
							if (unitId.find("F9WC-") != std::string::npos)
							{
								int taskType = (int)ReadNumber(object, "taskType");
								std::string palletNo = ReadString(object, "palletNo");
								rabbitmq_service_notifier->RabbitMQInsertOrder(taskId, taskType, taskStatus, unitId, palletNo);
								//std::stringstream ss2;
								//ss2 << "RabbitMQService::InsertOrder: receive msg:" << message;
								//log_info_color(log_color::red, ss2.str().c_str());
							}
						}
						if (all_order_insert.size() >= 100) {
							all_order_insert.pop_front();
						}
					}
				}
				else
				{
					// 解析出错
					std::stringstream ss2;
					ss2 << "RabbitMQService::InsertOrder: fail read json : Message:" << message;
					log_error(ss2.str().c_str());
				}
			}
			if (delivery_tag != 0)
			{
				client.AckMessage(delivery_tag);
			}
		}
	}
	catch (...)
	{
		log_info("RabbitMQService::timerEvent interrupted!");
	}
}

void RabbitMQService::checkUnit() {
	try
	{
		const std::string queue_name = "agv.request.check";
		std::deque<std::string> all_order_insert;// = new std::deque<int>;
		std::string message;
		uint64_t delivery_tag;

		CRabbitMqClient client(host);
		if (0 != client.Connect(virtualHost))
		{
			log_error("RabbitMQService::checkUnit: reconnect fail , please check your network");
		}
		CExchange exchange(exchange_name_, "topic");
		CQueue queue("zc." + queue_name);
		//client.DeclareExchange(exchange);
		client.DeclareQueue(queue);
		client.BindQueueToExchange(queue, exchange, queue_name);
		client.StateConsumer("zc." + queue_name);
		while (!rabbitmq_service_listen_->interruption_requested())
		{
			//中断点，interrupted退出点
			boost::this_thread::interruption_point();
			message = "";
			delivery_tag = 0;
			if (client.ConsumerMessage(message, delivery_tag, "zc." + queue_name))
			{
				CRabbitMqClient client(host);
				if (0 != client.Connect(virtualHost))
				{
					boost::this_thread::sleep(boost::chrono::milliseconds(2000));
					log_error("RabbitMQService::checkUnit: reconnect fail , please check your network");
				}
				client.DeclareQueue(queue);
				client.BindQueueToExchange(queue, exchange, queue_name);
				client.StateConsumer("zc." + queue_name);
				continue;
			}

			// 转JSON
			if (!message.empty())
			{
				QJsonParseError jsonError;
				QJsonDocument doucment = QJsonDocument::fromJson(message.c_str(), &jsonError);
				if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
				{ // JSON读取没有出错
					if (doucment.isObject())
					{
						// 接收传入数据
						QJsonObject object = doucment.object();
						bool valid = false;
						std::string UnitId = ReadString(object, "UnitId");
						std::string TaskId = ReadString(object, "TaskId");
						int Status = (int) ReadNumber(object, "Status");
						std::string key = UnitId + TaskId;
						if (UnitId.find("F9WC-") != std::string::npos)
						{
							boost::unique_lock<boost::shared_mutex> lk(apply_unit_mutex_);
							all_apply_unit_status_[key] = Status;
							std::stringstream ss2;
							ss2 << "RabbitMQService::checkUnit: receive msg:" << message;
							log_info(ss2.str().c_str());
						}
					}
				}
				else
				{
					// 解析出错
					std::stringstream ss2;
					ss2 << "RabbitMQService::checkUnit: fail read json : Message:" << message;
					log_error(ss2.str().c_str());
				}
			}
			if (delivery_tag != 0)
			{
				client.AckMessage(delivery_tag);
			}
		}
	}
	catch (...)
	{
		log_info("RabbitMQService::checkUnit interrupted!");
	}
}

void RabbitMQService::checkGetGoods() {
	try
	{
		const std::string queue_name = "agv.request.receiving";
		std::deque<std::string> all_order_insert;// = new std::deque<int>;
		std::string message;
		uint64_t delivery_tag;

		CRabbitMqClient client(host);
		if (0 != client.Connect(virtualHost))
		{
			log_error("RabbitMQService::checkGetGoods: reconnect fail , please check your network");
		}
		CExchange exchange(exchange_name_, "topic");
		CQueue queue("zc." + queue_name);
		//client.DeclareExchange(exchange);
		client.DeclareQueue(queue);
		client.BindQueueToExchange(queue, exchange, queue_name);
		client.StateConsumer("zc." + queue_name);
		while (!rabbitmq_service_listen_->interruption_requested())
		{
			//中断点，interrupted退出点
			boost::this_thread::interruption_point();
			message = "";
			delivery_tag = 0;
			if (client.ConsumerMessage(message, delivery_tag, "zc." + queue_name))
			{
				CRabbitMqClient client(host);
				if (0 != client.Connect(virtualHost))
				{
					boost::this_thread::sleep(boost::chrono::milliseconds(2000));
					log_error("RabbitMQService::checkGetGoods: reconnect fail , please check your network");
				}
				client.DeclareQueue(queue);
				client.BindQueueToExchange(queue, exchange, queue_name);
				client.StateConsumer("zc." + queue_name);
				continue;
			}

			// 转JSON
			if (!message.empty())
			{
				QJsonParseError jsonError;
				QJsonDocument doucment = QJsonDocument::fromJson(message.c_str(), &jsonError);
				if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
				{ // JSON读取没有出错
					if (doucment.isObject())
					{
						// 接收传入数据
						QJsonObject object = doucment.object();
						bool valid = false;
						std::string UnitId = ReadString(object, "UnitId");
						std::string TaskId = ReadString(object, "TaskId");
						int Status = (int)ReadNumber(object, "Status");
						std::string key = UnitId + TaskId;
						if (UnitId.find("F9WC-") != std::string::npos)
						{
							boost::unique_lock<boost::shared_mutex> lk(apply_get_goods_mutex_);
							all_apply_get_goods_status_[key] = Status;
							std::stringstream ss2;
							ss2 << "RabbitMQService::checkGetGoods: receive msg:" << message;
							log_info(ss2.str().c_str());
						}
					}
				}
				else
				{
					// 解析出错
					std::stringstream ss2;
					ss2 << "RabbitMQService::checkGetGoods: fail read json : Message:" << message;
					log_error(ss2.str().c_str());
				}
			}
			if (delivery_tag != 0)
			{
				client.AckMessage(delivery_tag);
			}
		}
	}
	catch (...)
	{
		log_info("RabbitMQService::checkGetGoods interrupted!");
	}
}

CRabbitMqClient* RabbitMQService::InitClient(std::string queue_name) {
	std::string err;
	auto client = new CRabbitMqClient(host);
	if (0 != client->Connect(virtualHost, err))
	{
		log_error(err.c_str());
		return nullptr;
	}
	return client;
}

// 消费者声明交换机-Exchange
CExchange* RabbitMQService::InitExchange(CRabbitMqClient* client) {
	if (!client)
	{
		client = InitClient();
	}
	std::string err;
	auto exchange = new CExchange("RabbitMQExchange", "topic");
	if (0 != client->DeclareExchange(*exchange, err))
	{
		log_error(err.c_str());
		return nullptr;
	}
	return exchange;
}

// TODO 添加参数 队列名 写死了
//CQueue* RabbitMQService::InitQueue(std::string queue_name, CRabbitMqClient* client, const std::string exchange_name) {
//	//std::string err;
//	//auto queue = new CQueue("zc." + queue_name);
//	//if (!client)
//	//{
//	//	client = InitClient();
//	//}
//	//if (0 != client->DeclareQueue(*queue, err))
//	//{
//	//	log_error(err.c_str());
//	//	return nullptr;
//	//}
//	//if (0 != client->BindQueueToExchange("zc." + queue_name, exchange_name, queue_name, err))
//	//{
//	//	log_error(err.c_str());
//	//	return nullptr;
//	//}
//	//return queue;
//	return nullptr;
//}


// 直接调用，监听一次工单下发。工单将通过 “STORAGE_MANAGE.Insert_Order” 下发
//void RabbitMQService::InsertOrder() {
//
//}

/// <summary>
/// Reads the string from JsonObject
/// </summary>
/// <param name="object">The object.</param>
/// <param name="key">The key.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/19
std::string RabbitMQService::ReadString(QJsonObject object, QString key){
	std::string value = "";
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isString())
		{  // 判断 value 是否为字符串
			value = object.value(key).toString().toLocal8Bit().toStdString();
		}
	}
	return value;
}

/// <summary>
/// Reads the int.
/// </summary>
/// <param name="object">The object.</param>
/// <param name="key">The key.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/19
double RabbitMQService::ReadNumber(QJsonObject object, QString key) {
	double value = -1;
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isDouble())
		{  // 判断 value 是否为数字
			value = json_value.toDouble();
		}
	}
	return value;
}

/// <summary>
/// Reads the bool.
/// </summary>
/// <param name="object">The object.</param>
/// <param name="key">The key.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/20
/// 
bool RabbitMQService::ReadBool(QJsonObject object, QString key) {
	bool value = false;
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isBool())
		{  // 判断 value 是否为数字
			value = json_value.toBool();
		}
	}
	return value;
}

// 生产者
bool RabbitMQService::SendMsg(std::string msg, std::string route_key, bool t1, bool t2) {
	bool result = false;

	// 组装 properties
	amqp_basic_properties_t properties;
	memset(&properties, 0, sizeof(properties));
	properties._flags = AMQP_BASIC_DELIVERY_MODE_FLAG
		| AMQP_BASIC_CONTENT_TYPE_FLAG		//content_type属性有效
		| AMQP_BASIC_HEADERS_FLAG			//headers 属性有效
		| AMQP_BASIC_TYPE_FLAG;
	properties.delivery_mode = AMQP_DELIVERY_NONPERSISTENT;	//消息持久(即使mq重启，还是会存在，前提是队列也是持久化的)
	properties.content_type = amqp_cstring_bytes("application/json");
	properties.type = amqp_cstring_bytes("java.lang.String");

	CMessage message(msg, properties, route_key, t1, t2);
	std::string err = "RabbitMQService::SendMsg client is empty";

	log_info_color(log_color::black, (route_key + " : send : " + msg).c_str());
	if (mqClient_ == nullptr || 0 != mqClient_->PublishMessage(message, route_key, err))
	{
		log_error(err.c_str());
		result = false;
	}
	else
	{
		result = true;
	}

	return result;
}

// 无需调用，通知库位状态更改：
bool RabbitMQService::ReportStorageStatus(std::string CageName, int CageType, int CageState) {
	bool result = false;
	const std::string queue_name = "agv.response.cachestate";

	QJsonObject json_data;
	json_data.insert("CageName", CageName.c_str());
	json_data.insert("CageType", CageType);
	json_data.insert("CageState", CageState);
	result = SendMsg(QString(QJsonDocument(json_data).toJson()).toStdString().c_str(), queue_name, true, false);

	return result;
}

/*
调用形式
//RABBITMQ_SERVICE.ReportStorageStatus("CageName", 1, 1);
//RABBITMQ_SERVICE.ReportOrderStatus("TaskId", 1, 1, "PalletNo", "Location");
//RABBITMQ_SERVICE.ReportAgvAction("CageName", 1,1,"PalletNo", 1);
//RABBITMQ_SERVICE.ApplyUnit("UnitId", "TaskId");
//RABBITMQ_SERVICE.ApplyGetGoods("UnitId", "TaskId", 1);
*/
// （同步）通知工单执行状态，返回是否发送成功
bool RabbitMQService::ReportOrderStatus(std::string TaskId, int TaskStatus, int CarId, std::string PalletNo, std::string Location) {
	bool result = false;
	const std::string queue_name = "agv.response.wc";
	
	QJsonObject json_data;
	json_data.insert("TaskId", TaskId.c_str());
	json_data.insert("TaskStatus", TaskStatus);
	json_data.insert("CarId", CarId);
	json_data.insert("PalletNo", PalletNo.c_str());
	json_data.insert("Location", Location.c_str());
	result = SendMsg(QString(QJsonDocument(json_data).toJson()).toStdString().c_str(), queue_name, true ,false);

	return result;
}

// （同步）通知AGV进出储位，返回是否发送成功
bool RabbitMQService::ReportAgvAction(std::string CageName, int CageType, int WorkType, std::string PalletNo, int CarId) {
	bool result = false;
	const std::string queue_name = "agv.response.cachepallet";

	QJsonObject json_data;
	json_data.insert("CageName", CageName.c_str());
	json_data.insert("CageType", CageType);
	json_data.insert("WorkType", WorkType);
	json_data.insert("PalletNo", PalletNo.c_str());
	json_data.insert("CarId", CarId);
	result = SendMsg(QString(QJsonDocument(json_data).toJson()).toStdString().c_str(), queue_name, true, false);

	return result;
}

// （异步）申请水箱单元，直到 滚筒线无货时，返回true，且仅返回一次
bool RabbitMQService::ApplyUnit(std::string UnitId, std::string TaskId) {
	bool result = false; // TODO 正式默认应为 false
	const std::string queue_name = "agv.response.check";
	std::string key = UnitId + TaskId;
	boost::unique_lock<boost::shared_mutex> lk(apply_unit_mutex_);
	if (all_apply_unit_status_.find(key) == all_apply_unit_status_.end())
	{
		all_apply_unit_status_[key] = 0;
	}
	else {

		QJsonObject json_data;
		// 0代表初始化，1代表已发送
		switch (all_apply_unit_status_[key])
		{
		case 0:
			//初始化，发送，并开启监听
			json_data.insert("UnitId", UnitId.c_str());
			json_data.insert("TaskId", TaskId.c_str());
			SendMsg(QString(QJsonDocument(json_data).toJson()).toStdString().c_str(), queue_name, true, false);
			break;
		case 1:
			// 已发送，返回无货，返回正确，出栈
			all_apply_unit_status_.erase(key);
			result = true;
			break;
		case 2:
		default:
			// 已发送，返回有货，返回错误
			all_apply_unit_status_[key] = 0;
			result = false;
			break;
		}
	}
	return result;
}


// （异步）满轮开始取货确认（true:确定能取货，AGV进入滚筒线取满轮）

bool RabbitMQService::ApplyGetGoods(std::string UnitId, std::string TaskId) {
	bool result = false;
	const std::string queue_name = "agv.response.receiving";
	std::string key = UnitId + TaskId;

	// 开始取料通知
	boost::unique_lock<boost::shared_mutex> lk(apply_get_goods_mutex_);
	if (all_apply_get_goods_status_.find(key) == all_apply_get_goods_status_.end())
	{
		// 不存在，则创建
		all_apply_get_goods_status_[key] = -1;
	}
	else {
		// 0代表初始化，1代表已发送
		QJsonObject json_data;
		switch (all_apply_get_goods_status_[key])
		{
		case -1:
			json_data.insert("UnitId", UnitId.c_str());
			json_data.insert("TaskId", TaskId.c_str());
			json_data.insert("Status", 1);
			if (SendMsg(QString(QJsonDocument(json_data).toJson()).toStdString().c_str(), queue_name, true, false))
			{
				all_apply_get_goods_status_[key] = 0;
			}
			result = false;
			break;
		case 0:
			//正在发送
			break;
		case 1:
			// 已发送，可以取，返回正确
			result = true;
			break;
		case 2:
			// 已发送，不可取，返回错误
		default:
			all_apply_get_goods_status_[key] = 0;
			result = false;
			
			break;
		}
	}

	return result;
}

// （异步）获取是否可以继续取货
bool RabbitMQService::FeedbackUnitStatus(std::string UnitId, std::string TaskId) {
	std::string key = UnitId + TaskId;
	boost::shared_lock<boost::shared_mutex> lk(apply_get_goods_mutex_);
	return all_apply_get_goods_status_[key] == 1;
}

// （同步）通知取货完成
bool RabbitMQService::ReportStopGetGoods(std::string UnitId, std::string TaskId) {
	bool result = true;
	const std::string queue_name = "agv.response.receiving";

	QJsonObject json_data;
	json_data.insert("UnitId", UnitId.c_str());
	json_data.insert("TaskId", TaskId.c_str());
	json_data.insert("Status", 2);
	result = SendMsg(QString(QJsonDocument(json_data).toJson()).toStdString().c_str(), queue_name, true, false);
	std::string key = UnitId + TaskId;
	// 加锁 map 中删除指定 key 
	boost::unique_lock<boost::shared_mutex> lk(apply_get_goods_mutex_);
	all_apply_get_goods_status_.erase(key);
	return result;
}
