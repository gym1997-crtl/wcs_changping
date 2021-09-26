/*******************************************************************************
*  @file      RabbitMqClient.h 2019\2\28
*  @author    libing<libing26444@hundsun.com>
*  @brief     RabbitMq封装
******************************************************************************/

#pragma once
#include "amqp.h"
#include "amqp_tcp_socket.h"
#include "amqp_time.h"
#include <string>
#include <vector>

/**
*   @brief 消息结构
**/
class CMessage
{
public:
	CMessage(std::string data, amqp_basic_properties_t properties, std::string  routekey,
		bool bMandatory = true, bool bImmediate = false)
		:m_data(data),
		m_properties(properties),
		m_routekey(routekey),
		m_bMandatory(bMandatory),
		m_bImmediate(bImmediate)
	{

	}

	CMessage(const CMessage &other)
	{
		this->m_data = other.m_data;
		this->m_properties = other.m_properties;
		this->m_routekey = other.m_routekey;
		this->m_bMandatory = other.m_bMandatory;
		this->m_bImmediate = other.m_bImmediate;
	}

	CMessage operator=(const CMessage &other)
	{
		if (this == &other)
			return *this;
		this->m_data = other.m_data;
		this->m_properties = other.m_properties;
		this->m_routekey = other.m_routekey;
		this->m_bMandatory = other.m_bMandatory;
		this->m_bImmediate = other.m_bImmediate;
		return *this;
	}

	/**
	* m_bMandatory 消息必须路由到队列，由消费者来取
	*
	**/
	bool m_bMandatory;

	/**
	* m_bImmediate 消息是否要立即发送到消费者
	*
	**/
	bool m_bImmediate;

	/**
	* m_routekey 消息路由 默认所有消息的路由都以 “msg.”开头
	*
	**/
	std::string  m_routekey;

	/**
	* m_data 消息内容（目前RabbitMq只支持字符串，如要传json，只需写json格式即可，{\"test\":\"hello\"}）
	*
	**/
	std::string  m_data;

	/**
	* m_properties 消息的属性(包括消息头)
	*
	**/
	amqp_basic_properties_t m_properties;
};

/**
*   @brief 消息队列
**/
class CQueue
{
public:
	CQueue(std::string strName, bool nDurable = true, bool nPassive = false,
		bool bAutoDelete = false, bool bExclusive = false)
		:m_name(strName),
		m_durable(nDurable),
		m_bPassive(nPassive),
		m_bAutoDelete(bAutoDelete),
		m_bExclusive(bExclusive)
	{

	}

	CQueue(const CQueue &other)
	{
		this->m_name = other.m_name;
		this->m_durable = other.m_durable;
		this->m_bAutoDelete = other.m_bAutoDelete;
		this->m_bExclusive = other.m_bExclusive;
		this->m_bPassive = other.m_bPassive;
	}

	CQueue operator=(const CQueue &other)
	{
		if (this == &other)
			return *this;
		this->m_name = other.m_name;
		this->m_durable = other.m_durable;
		this->m_bAutoDelete = other.m_bAutoDelete;
		this->m_bExclusive = other.m_bExclusive;
		this->m_bPassive = other.m_bPassive;
		return *this;
	}

	/**
	* m_name 消息队列名称
	*
	**/
	std::string   m_name;

	/**
	* m_durable 队列是否持久化(当mq服务端断开重启后，队列是否还存在)
	*
	**/
	bool		  m_durable;

	/**
	* m_exclusive 是否是专用队列（当前连接不在时，队列是否删除）
	*		如果m_exclusive = 1，那么当当前连接断开时，队列也被删除
	*		否则，当当前连接断开时，队列依旧存在
	**/
	bool		  m_bExclusive;


	/**
	* m_auto_delete 没有consumer时，队列是否自动删除
	*
	**/
	bool		  m_bAutoDelete;

	/**
	* passive 检测queue是否存在
	*	设为true，
	*		若queue存在则创建命令成功返回（调用其他参数不会影响queue属性），
	*		若不存在不会创建queue，返回错误。
	*	设为false，
	*		如果queue不存在则创建，调用成功返回。
	*		如果queue已经存在，并且匹配现在queue的话则成功返回，如果不匹配则queue声明失败。
	**/
	bool		  m_bPassive;
};

/**
*   @brief 交换机
**/
class CExchange
{
public:
	CExchange(std::string name, std::string type = "direct",
		bool durable = true, bool passive = true, bool auto_delete = false, bool internal = false)
		:m_name(name),
		m_type(type),
		m_bDurable(durable),
		m_bPassive(passive),
		m_bAutoDelete(auto_delete),
		m_bInternal(internal)
	{

	}

	CExchange(const CExchange &other)
	{
		this->m_name = other.m_name;
		this->m_bDurable = other.m_bDurable;
		this->m_type = other.m_type;
		this->m_bAutoDelete = other.m_bAutoDelete;
		this->m_bInternal = other.m_bInternal;
		this->m_bPassive = other.m_bPassive;
	}

	CExchange operator=(const CExchange &other)
	{
		if (this == &other)
			return *this;
		this->m_name = other.m_name;
		this->m_bDurable = other.m_bDurable;
		this->m_type = other.m_type;
		this->m_bAutoDelete = other.m_bAutoDelete;
		this->m_bInternal = other.m_bInternal;
		this->m_bPassive = other.m_bPassive;
		return *this;
	}

	/**
	* m_name 交换机名称
	*
	**/
	std::string   m_name;

	/**
	* m_type 指定exchange类型，"fanout"  "direct" "topic"三选一
	*	"fanout" 广播的方式，发送到该exchange的所有队列上(不需要进行bind操作)
	*	"direct" 通过路由键发送到指定的队列上(把消息发送到匹配routing key的队列中。)
	*	"topic" 通过匹配路由键的方式获取，使用通配符*，#
	**/
	std::string   m_type;

	/**
	* m_durable 交换机是否持久化(当mq服务端断开重启后，交换机是否还存在)
	**/
	bool		  m_bDurable;

	/**
	* m_auto_delete 连接断开时，交换机是否自动删除
	*
	**/
	bool		  m_bAutoDelete;

	/**
	* m_internal 默认为0，没有使用到
	*
	**/
	bool		  m_bInternal;

	/**
	* passive 检测exchange是否存在
	*	设为true，
	*		若exchange存在则命令成功返回（调用其他参数不会影响exchange属性），
	*		若不存在不会创建exchange，返回错误。
	*	设为false，
	*		如果exchange不存在则创建exchange，调用成功返回。
	*		如果exchange已经存在，并且匹配现在exchange的话则成功返回，如果不匹配则exchange声明失败。
	**/
	bool		  m_bPassive;
};

//RabbitMq服务端ip，端口，用户名，密码
static const char connect_host[] = "127.0.0.1"; // "192.168.48.22";// "10.20.23.167";
static const int connect_port = 5672;
static const char connect_user[] = "zhiyin"; // "admin";
static const char connect_pwd[] = "zhiyin"; // "admin";

//频道号，队列名，交换机名，路由名
//static int channel_id = 10;
//static const char queue_name[] = "message_push_default_queue2";
//static const char exchange_name[] = "message_push_default_exchange2";
//static const char routing_keys_name[] = "test.1";
static int channel_id = 11;
//static const char queue_name[] = "agv.topic";
static const char exchange_name[] = "RabbitMQExchange";
//static const char routing_keys_name[] = "test.1";


/**
*   @brief RabbitMq封装类
**/
class CRabbitMqClient
{
public:
	CRabbitMqClient(
		std::string HostName = connect_host,
		uint32_t port = connect_port,
		std::string usr = connect_user,
		std::string psw = connect_pwd
	);
	~CRabbitMqClient();

public:
	/**
	* 连接RabbitMq服务器
	*
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t Connect(const std::string virtualHost = std::string("/"), std::string &ErrorReturn = std::string(""));

	/**
	* 断开与RabbitMq服务器的连接
	*
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t DisConnect(std::string &ErrorReturn = std::string(""));

	/**
	* 交换机初始化
	*
	* @param[in]    exchange		交换机实例
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t DeclareExchange(CExchange &exchange, std::string &ErrorReturn = std::string(""));

	/**
	* 队列初始化
	*
	* @param[in]    queue			消息队列实例
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t DeclareQueue(CQueue &queue, std::string &ErrorReturn = std::string(""));

	/**
	* 将指定队列绑定到指定交换机上
	*
	* @param[in]    queue			消息队列实例
	* @param[in]    exchange		交换机实例
	* @param[in]    bind_key		路由名
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t BindQueueToExchange(CQueue &queue, CExchange &exchange, const std::string bind_key, std::string &ErrorReturn = std::string(""));

	/**
	* 解绑指定队列和指定交换机
	*
	* @param[in]    queue			消息队列实例
	* @param[in]    exchange		交换机实例
	* @param[in]    bind_key		路由名
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t UnBindQueueToExchange(CQueue &queue, CExchange &exchange, const std::string bind_key, std::string &ErrorReturn = std::string(""));

	/**
	* 发布单个消息
	*
	* @param[in]    message			消息实例
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t PublishMessage(const CMessage &message, const std::string route_key,std::string &ErrorReturn = std::string(""));

	/**
	* 发布批量消息
	*
	* @param[in]    messageVec		消息实例数组
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t PublishMessage(std::vector<CMessage> &messageVec, std::string &ErrorReturn = std::string(""));
	// TODO 添加注释 声明消费者
	int32_t StateConsumer(const std::string &queue_name_, std::string &ErrorReturn = std::string(""));
	/**
	* 从指定队列中取单个消息（同步操作）
	*
	* @param[in]    queue_name_		队列名称
	* @param[in]    timeout			超时时间，为NULL有可能导致阻塞
	* @param[out]   message			消息内容
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t ConsumerMessage(std::string &message, uint64_t &delivery_tag, const std::string &queue_name_, timeval timeout = { 5, 0 }, std::string &ErrorReturn = std::string(""));
	// TODO 添加注释 确认消息
	int32_t AckMessage(uint64_t delivery_tag);
	/**
	* 从指定队列中取指定数目消息（同步操作）
	*
	* @param[in]    queue_name_		队列名称
	* @param[in]    GetNum			消息树木
	* @param[in]    timeout			超时时间，为NULL有可能导致阻塞
	* @param[out]   messageVec		消息内容数组（大小不一定等于GetNum）
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t ConsumerMessage(std::vector<std::string> &messageVec, const std::string &queue_name_, uint32_t GetNum = 1000, timeval timeout = { 5, 0 }, std::string &ErrorReturn = std::string(""));

	//还有一个amqp_basic_get函数，没有用到，暂时不实现（区别于amqp_basic_consume，get是检索，consume是消费）
private:
	/**
	* 获取错误信息文本
	*
	* @param[in]    reply			amqp_rpc_reply_t对象
	* @param[in]    strModule		模块信息（一般传当前调用的RabbitMQ-API函数名）
	* @param[out]   ErrorReturn		错误信息
	* @return		int32_t			0表示成功，其他失败
	*/
	int32_t GetErrorText(const amqp_rpc_reply_t &reply, const std::string &strModule, std::string &ErrorReturn);

private:
	std::string m_strHost;
	std::string m_strUser;
	std::string m_strPwd;
	int32_t m_nPort;

	amqp_connection_state_t m_connectState;
};

//amqp_basic_properties_t属性填充可参照如下样例
/*
void GetProperties(amqp_basic_properties_t& properties)
{
	properties._flags = AMQP_BASIC_DELIVERY_MODE_FLAG
		| AMQP_BASIC_CONTENT_TYPE_FLAG		//content_type属性有效
		| AMQP_BASIC_HEADERS_FLAG			//headers属性有效
		| AMQP_BASIC_TYPE_FLAG;
	properties.delivery_mode = AMQP_DELIVERY_PERSISTENT;	//消息持久(即使mq重启，还是会存在，前提是队列也是持久化的)
	properties.content_type = amqp_cstring_bytes("application/json");
	properties.type = amqp_cstring_bytes("com.hundsun.jrescloud.demo.mq.producer.domin.User");

	//填充头部
	int nHeaderNum = 8;
	amqp_table_entry_t *pEntries = (amqp_table_entry_t*)malloc(sizeof(amqp_table_entry_t) * nHeaderNum);
	pEntries[0].key = amqp_cstring_bytes("cf_id");
	pEntries[0].value.value.bytes = amqp_cstring_bytes("666666");
	pEntries[0].value.kind = AMQP_FIELD_KIND_UTF8;

	pEntries[1].key = amqp_cstring_bytes("hs-mq-msg-uuid");
	char szTemp[256] = { 0 };
	static int sIndex = 1;
	sprintf_s(szTemp, 256, "7322e43b-a5b1-41cd-84%d7-eb52b1dc86cc", sIndex++);
	pEntries[1].value.value.bytes = amqp_cstring_bytes("7322e43b-a5b1-41cd-8487-eb52b1dc86cc");
	pEntries[1].value.kind = AMQP_FIELD_KIND_UTF8;

	pEntries[2].key = amqp_cstring_bytes("hs-mq-outputId");
	pEntries[2].value.value.bytes = amqp_cstring_bytes("user");
	pEntries[2].value.kind = AMQP_FIELD_KIND_UTF8;

	pEntries[3].key = amqp_cstring_bytes("retryCount");
	pEntries[3].value.value.u16 = 3;
	pEntries[3].value.kind = AMQP_FIELD_KIND_U16;

	pEntries[4].key = amqp_cstring_bytes("x-first-death-exchange");
	pEntries[4].value.value.bytes = amqp_cstring_bytes(exchange_name);
	pEntries[4].value.kind = AMQP_FIELD_KIND_UTF8;

	pEntries[5].key = amqp_cstring_bytes("x-first-death-queue");
	pEntries[5].value.value.bytes = amqp_cstring_bytes(queue_name);
	pEntries[5].value.kind = AMQP_FIELD_KIND_UTF8;

	pEntries[6].key = amqp_cstring_bytes("x-first-death-reason");
	pEntries[6].value.value.bytes = amqp_cstring_bytes("rejected");
	pEntries[6].value.kind = AMQP_FIELD_KIND_UTF8;

	//填充x_death
	int nTableNum = 6;
	amqp_table_entry_t *pTable = (amqp_table_entry_t*)malloc(sizeof(amqp_table_entry_t) * nTableNum);
	{
		pTable[0].key = amqp_cstring_bytes("count");
		pTable[0].value.value.u16 = 1;
		pTable[0].value.kind = AMQP_FIELD_KIND_U16;

		pTable[1].key = amqp_cstring_bytes("exchange");
		pTable[1].value.value.bytes = amqp_cstring_bytes(exchange_name);;
		pTable[1].value.kind = AMQP_FIELD_KIND_UTF8;

		pTable[2].key = amqp_cstring_bytes("queue");
		pTable[2].value.value.bytes = amqp_cstring_bytes(queue_name);;
		pTable[2].value.kind = AMQP_FIELD_KIND_UTF8;

		pTable[3].key = amqp_cstring_bytes("reason");
		pTable[3].value.value.bytes = amqp_cstring_bytes("rejected");;
		pTable[3].value.kind = AMQP_FIELD_KIND_UTF8;

		pTable[4].key = amqp_cstring_bytes("routing-keys");
		pTable[4].value.value.bytes = amqp_cstring_bytes(routing_keys_name);;
		pTable[4].value.kind = AMQP_FIELD_KIND_UTF8;

		pTable[5].key = amqp_cstring_bytes("time");
		pTable[5].value.value.bytes = amqp_cstring_bytes("1551280882");;
		pTable[5].value.kind = AMQP_FIELD_KIND_UTF8;
	}
	pEntries[7].key = amqp_cstring_bytes("x-death");
	pEntries[7].value.value.table.entries = pTable;
	pEntries[7].value.value.table.num_entries = nTableNum;
	pEntries[7].value.kind = AMQP_FIELD_KIND_TABLE;

	properties.headers.entries = pEntries;
	properties.headers.num_entries = nHeaderNum;
}
*/