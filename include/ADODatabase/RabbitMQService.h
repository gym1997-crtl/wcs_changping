#ifndef RABBITMQ_SERVICE_H
#define RABBITMQ_SERVICE_H

#include <boost/serialization/singleton.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <string>
//#include <RabbitMqClient.h>
#include <map>

#include <QObject>
#include <QJsonObject>
#include <QString>

#include "Common/Config.h"

class CQueue;
class CExchange;
class CRabbitMqClient;
class RabbitMQ_Service_Notifier
{
public:
	virtual void RabbitMQInsertOrder(std::string taskId, int taskType, int taskStatus, std::string unitId, std::string palletNo) = 0;
};

class RabbitMQService
{
public:
	RabbitMQService() {
	}
	//explicit RabbitMQService(QObject *parent = nullptr);
	~RabbitMQService();
	// 通知接口
	RabbitMQ_Service_Notifier * rabbitmq_service_notifier;
	void setRabbitMQServiceNotifier(RabbitMQ_Service_Notifier * notifier);

	bool Init();
	bool StopScan();
	// 接口
	// 生产者
	// 通知库位状态改变，无需调用
	bool ReportStorageStatus(std::string CageName, int CageType, int CageState);
	// 通知工单状态改变
	bool ReportOrderStatus(std::string TaskId, int TaskStatus, int CarId, std::string PalletNo, std::string Location);
	// 通知AGV进出储位 
	bool ReportAgvAction(std::string CageName, int CageType, int WorkType, std::string PalletNo, int CarId);

	// 复杂逻辑
	// 接口1：申请进入水箱
	// 默认false，当查询到允许进入时，返回true
	bool ApplyUnit(std::string UnitId, std::string TaskId);
	// 接口2：开始取料，并询问是否需要打断
	// 2.1：同步
	// 发送1，可从Feedback中获取 true/false 得知是否允许搬货
	// 发送2，停止Feedback查询该任务
	bool ApplyGetGoods(std::string UnitId, std::string TaskId);
	// 2.2 异步
	// 当Apply发送1后，将持续返回 true/false 通知是否可以搬货，默认为 true
	// 当Apply发送2后，将不再查询，再次调用将返回true
	bool FeedbackUnitStatus(std::string UnitId, std::string TaskId);
	bool ReportStopGetGoods(std::string UnitId, std::string TaskId);

private:
	// 连接参数
	std::string host /*= "172.16.25.142"; */ = "127.0.0.1";
	const std::string username = "zhiyin";
	const std::string password = "zhiyin";
	std::string virtualHost = "/";
	const std::string exchange_name_ = "RabbitMQExchange";

	const std::vector<std::string> all_request_topic_name_ = { "agv.request.wc" , "agv.request.check", "agv.request.receiving" };
	const std::vector<std::string> all_response_topic_name_ = { "agv.response.wc", "agv.response.cachestate", "agv.response.cachepallet", "agv.response.check", "agv.response.receiving" };

	// 初始化
	Config_File Config_;
	void ReadRabbitMQService();
	CRabbitMqClient* InitClient(std::string queue_name = "");
	CExchange* InitExchange(CRabbitMqClient* client);
	//CQueue* InitQueue(std::string queue_name, CRabbitMqClient* client, const std::string exchange_name);
	// 解析json
	std::string ReadString(QJsonObject object, QString key);
	double ReadNumber(QJsonObject object, QString key);
	bool ReadBool(QJsonObject object, QString key);
	//连接
	CRabbitMqClient* mqClient_;
	CExchange* exchange_;
	std::map<std::string, CQueue* > all_queue_;
	
	//多线程相关
	boost::shared_ptr<boost::thread> rabbitmq_service_listen_;
	void timerEvent();

	// 监听申请水箱单元
	boost::shared_ptr<boost::thread> rabbitmq_apply_unit_listen_;
	void checkUnit();
	std::map<std::string, int> all_apply_unit_status_;
	mutable boost::shared_mutex apply_unit_mutex_;
	
	// 监听申请取货
	boost::shared_ptr<boost::thread> rabbitmq_apply_get_goods_listen_;
	void checkGetGoods();
	std::map<std::string, int> all_apply_get_goods_status_;
	mutable boost::shared_mutex apply_get_goods_mutex_;
	
	// 消费者
	//void InsertOrder();
	// 生产者
	bool SendMsg(std::string msg, std::string topic_name, bool t1, bool t2);
};

typedef boost::serialization::singleton<RabbitMQService> Singleton_RabbitMQ_Service;
#define RABBITMQ_SERVICE Singleton_RabbitMQ_Service::get_mutable_instance()

#endif //RABBITMQ_SERVICE_H