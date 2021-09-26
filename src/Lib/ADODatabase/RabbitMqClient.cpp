//#include "stdafx.h"
#include "RabbitMqClient.h"

CRabbitMqClient::CRabbitMqClient(std::string HostName /*= CONNECT_HOST*/, uint32_t port /*= CONNECT_PORT*/,
	std::string usr /*= CONNECT_USER*/, std::string psw /*= CONNECT_PWD */)
	:m_strHost(HostName),
	m_nPort(port),
	m_strUser(usr),
	m_strPwd(psw),
	m_connectState(NULL)
{

}

CRabbitMqClient::~CRabbitMqClient()
{
	DisConnect();
}

int32_t CRabbitMqClient::Connect(const std::string virtualHost /*= std::string("/")*/, std::string &ErrorReturn /*= ""*/)
{
	m_connectState = amqp_new_connection();//建立TCP连接
	if (!m_connectState)
	{
		ErrorReturn = "amqp_new_connection failed";
		return -1;
	}

	amqp_socket_t *socket = amqp_tcp_socket_new(m_connectState);
	if (!socket)
	{
		ErrorReturn = "amqp_tcp_socket_new failed";
		return -1;
	}

	int rc = amqp_socket_open(socket, m_strHost.c_str(), AMQP_PROTOCOL_PORT);  //打开建立的TCP连接，使用socket，主机名和端口号：
	if (rc != AMQP_STATUS_OK)
	{
		ErrorReturn = "amqp_socket_open failed";
		return -1;
	}

	amqp_rpc_reply_t rpc_reply = amqp_login(
		m_connectState,
		virtualHost.c_str(),
		1,
		AMQP_DEFAULT_FRAME_SIZE,
		AMQP_DEFAULT_HEARTBEAT,
		AMQP_SASL_METHOD_PLAIN,
		m_strUser.c_str(),
		m_strPwd.c_str()
	);
	if (rpc_reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		ErrorReturn = "amqp_login failed";
		return -1;
	}

	amqp_channel_open_ok_t *res =
		amqp_channel_open(m_connectState, channel_id);
	if (!res)
	{
		ErrorReturn = "amqp_channel_open failed";
		return -1;
	}

	return 0;
}

int32_t CRabbitMqClient::DisConnect(std::string &ErrorReturn /*= std::string("")*/)
{
	amqp_rpc_reply_t rpc_reply = amqp_channel_close(m_connectState, channel_id, AMQP_REPLY_SUCCESS);
	if (rpc_reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		ErrorReturn = "amqp_channel_close failed";
		return -1;
	}

	rpc_reply = amqp_connection_close(m_connectState, AMQP_REPLY_SUCCESS);
	if (rpc_reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		ErrorReturn = "amqp_connection_close failed";
		return -1;
	}

	int rc = amqp_destroy_connection(m_connectState);
	if (rc != AMQP_STATUS_OK)
	{
		ErrorReturn = "amqp_destroy_connection failed";
		return -1;
	}
	m_connectState = NULL;

	return 0;
}

int32_t CRabbitMqClient::DeclareExchange(CExchange &exchange, std::string &ErrorReturn /*= std::string("")*/)
{
	amqp_exchange_declare_ok_t *res = amqp_exchange_declare(
		m_connectState,
		channel_id,
		amqp_cstring_bytes(exchange.m_name.c_str()),
		amqp_cstring_bytes(exchange.m_type.c_str()),
		exchange.m_bPassive,
		exchange.m_bDurable,
		exchange.m_bAutoDelete,
		exchange.m_bInternal,
		amqp_empty_table);
	amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
	if (0 != GetErrorText(rpc_reply, "amqp_exchange_declare", ErrorReturn))
	{
		return -1;
	}

	return 0;
}

int32_t CRabbitMqClient::DeclareQueue(CQueue &queue, std::string &ErrorReturn /*= std::string("")*/)
{
	amqp_queue_declare_ok_t *res = amqp_queue_declare(
		m_connectState,
		channel_id,
		amqp_cstring_bytes(queue.m_name.c_str()),
		queue.m_bPassive,	/*passive*/ 	//检验队列是否存在（同exchange中的passive属性）
		queue.m_durable,	/*durable*/ 	//队列是否持久化(即使mq服务重启也会存在)
		queue.m_bExclusive,  /*exclusive*/ 	//是否是专用队列（当前连接不在时，队列是否删除）
		queue.m_bAutoDelete,/*auto_delete*/  //是否自动删除（什么时候删除？。。。）
		amqp_empty_table);
	amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
	if (0 != GetErrorText(rpc_reply, "amqp_queue_declare", ErrorReturn))
	{
		return -1;
	}

	return 0;
}

int32_t CRabbitMqClient::BindQueueToExchange(CQueue &queue, CExchange &exchange, const std::string bind_key, std::string &ErrorReturn /*= std::string("")*/)
{
	//队列与交换机绑定
	amqp_queue_bind_ok_t *res = amqp_queue_bind(
		m_connectState,		//连接
		channel_id,		//频道id
		amqp_cstring_bytes(queue.m_name.c_str()),	//队列
		amqp_cstring_bytes(exchange.m_name.c_str()),	//交换机
		amqp_cstring_bytes(bind_key.c_str()), //路由
		amqp_empty_table);
	amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
	if (0 != GetErrorText(rpc_reply, "amqp_queue_bind", ErrorReturn))
	{
		return -1;
	}

	return 0;
}

int32_t CRabbitMqClient::UnBindQueueToExchange(CQueue &queue, CExchange &exchange, const std::string bind_key, std::string &ErrorReturn /*= std::string("")*/)
{
	//队列与交换机绑定
	amqp_queue_unbind_ok_t *res = amqp_queue_unbind(
		m_connectState,		//连接
		channel_id,		//频道id
		amqp_cstring_bytes(queue.m_name.c_str()),	//队列
		amqp_cstring_bytes(exchange.m_name.c_str()),	//交换机
		amqp_cstring_bytes(bind_key.c_str()), //路由
		amqp_empty_table);
	amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
	if (0 != GetErrorText(rpc_reply, "amqp_queue_unbind", ErrorReturn))
	{
		return -1;
	}

	return 0;
}

int32_t CRabbitMqClient::PublishMessage(const CMessage &message, const std::string route_key, std::string &ErrorReturn /*= std::string("")*/)
{
	int retval = amqp_basic_publish(
		m_connectState,
		channel_id,		//频道id，没有要求，用同一个频道是ok的
		//amqp_cstring_bytes("amq.topic"),	//交换机
		amqp_cstring_bytes(exchange_name),	//交换机
		amqp_cstring_bytes(route_key.c_str()),	//路由
		message.m_bMandatory,	//消息必须路由到队列，由消费者来取
		message.m_bImmediate,	//消息是否要立即发送到消费者
		&message.m_properties,	//消息的属性，支持key-value模式
		amqp_cstring_bytes(message.m_data.c_str()) //消息内容
	);
	if (retval != AMQP_STATUS_OK)
	{
		amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
		if (0 != GetErrorText(rpc_reply, "amqp_basic_publish", ErrorReturn))
		{
			return -1;
		}
		printf("发送错误：%s\n", ErrorReturn.c_str());
	}
	printf("发送结果：%d\n", retval);

	return 0;
}

int32_t CRabbitMqClient::PublishMessage(std::vector<CMessage> &messageVec, std::string &ErrorReturn /*= std::string("")*/)
{
	int ret = 0;

	for (std::vector<CMessage>::iterator it = messageVec.begin(); it != messageVec.end(); ++it)
	{
		//发送多个消息时，暂时简化为只看发送最后一条消息的结果
		ret = PublishMessage(*it, ErrorReturn);
	}

	return ret;
}

int32_t CRabbitMqClient::StateConsumer(const std::string &queue_name_, std::string &ErrorReturn/* = std::string("")*/)
{

	//step 1
	amqp_basic_qos_ok_t *res = amqp_basic_qos(
		m_connectState,	//MQ连接
		channel_id,	//频道号
		0,		//这个参数从rabbitmq中没用到，默认为0
		50,		//设置为rabbitmq流量控制数量，缓存消息数目
		0		//glotal=true时表示在当前channel上所有的consumer都生效，否则只对设置了之后新建的consumer生效
	);
	if (!res)
	{
		amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
		if (0 != GetErrorText(rpc_reply, "amqp_basic_qos", ErrorReturn))
		{
			return -1;
		}
	}

	//step2
	amqp_basic_consume_ok_t *res2 = amqp_basic_consume(
		m_connectState,
		channel_id,
		amqp_cstring_bytes(queue_name_.c_str()),
		amqp_empty_bytes,
		/*no_local*/ 0,	//true if the server should not deliver to this consumer messages published on this channel’s connection
						//true：mq服务器不应将当前频道上的消息发送到此consumer
		/*no_ack*/ 0,	//是否需要确认消息后再从队列中删除消息
		/*exclusive*/ 0,
		amqp_empty_table);
	if (!res)
	{
		amqp_rpc_reply_t rpc_reply = amqp_get_rpc_reply(m_connectState);
		if (0 != GetErrorText(rpc_reply, "amqp_basic_consume", ErrorReturn))
		{
			return -1;
		}
	}
	return 0;
}



int32_t CRabbitMqClient::ConsumerMessage(std::string &message, uint64_t &delivery_tag, const std::string &queue_name_, timeval timeout/* = { 5, 0 }*/, std::string &ErrorReturn/* = std::string("")*/)
{
	//step3
	amqp_envelope_t envelope;
	amqp_rpc_reply_t rpc_reply =
		amqp_consume_message(m_connectState, &envelope, &timeout, 0);
	
	
	if (rpc_reply.reply_type != AMQP_RESPONSE_NORMAL && rpc_reply.library_error != -13)
	{
		// 报错，且不是超时
		return -1;
	}
	
	message = std::string((char *)envelope.message.body.bytes, (char *)envelope.message.body.bytes + envelope.message.body.len);
	delivery_tag = envelope.delivery_tag;
	amqp_destroy_envelope(&envelope);

	return 0;
}

int32_t CRabbitMqClient::AckMessage(uint64_t delivery_tag)
{
	amqp_envelope_t envelope;
	int rpc_reply =
		amqp_basic_ack(
			m_connectState,
			channel_id,
			delivery_tag,
			0);

	return rpc_reply;
}

int32_t CRabbitMqClient::ConsumerMessage(std::vector<std::string> &messageVec, const std::string &queue_name_,
	uint32_t GetNum/* = 1000*/, timeval timeout/* = { 5, 0 }*/, std::string &ErrorReturn/* = std::string("")*/)
{
	while (GetNum--)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t rpc_reply =
			amqp_consume_message(m_connectState, &envelope, &timeout, 0);
		if (0 != GetErrorText(rpc_reply, "amqp_consume_message", ErrorReturn))
		{
			return -1;
		}

		size_t body_size = envelope.message.body.len;
		char *body = (char*)malloc(body_size + 1);
		memset(body, 0, body_size + 1);
		if (body)
		{
			memcpy(body, envelope.message.body.bytes, body_size);
		}
		std::string message = body;
		messageVec.push_back(message);
		free(body);
		amqp_destroy_envelope(&envelope);
	}

	return 0;
}

int32_t CRabbitMqClient::GetErrorText(const amqp_rpc_reply_t &reply, const std::string &strModule, std::string &ErrorReturn)
{
	char rtnmsg[1024] = { 0 };
	switch (reply.reply_type)
	{
	case AMQP_RESPONSE_NORMAL:
		return 0;
	case AMQP_RESPONSE_NONE:
		sprintf(rtnmsg, "%s: missing RPC reply type!\n", strModule.c_str());
		break;
	case AMQP_RESPONSE_LIBRARY_EXCEPTION:
		sprintf(rtnmsg, "%s: %s\n", strModule.c_str(), amqp_error_string2(reply.library_error));
		break;
	case AMQP_RESPONSE_SERVER_EXCEPTION:
		switch (reply.reply.id)
		{
		case AMQP_CONNECTION_CLOSE_METHOD:
		{
			amqp_connection_close_t *m = (amqp_connection_close_t *)reply.reply.decoded;
			sprintf(rtnmsg, "%s: server connection error %d, message: %.*s\n",
				strModule.c_str(),
				m->reply_code,
				(int)m->reply_text.len, (char *)m->reply_text.bytes);
			break;
		}
		case AMQP_CHANNEL_CLOSE_METHOD:
		{
			amqp_channel_close_t *m = (amqp_channel_close_t *)reply.reply.decoded;
			sprintf(rtnmsg, "%s: server channel error %d, message: %.*s\n",
				strModule.c_str(),
				m->reply_code,
				(int)m->reply_text.len, (char *)m->reply_text.bytes);
			break;
		}
		default:
			sprintf(rtnmsg, "%s: unknown server error, method id 0x%08X\n", strModule, reply.reply.id);
			break;
		}
		break;
	}
	ErrorReturn = rtnmsg;
	return -1;
}

