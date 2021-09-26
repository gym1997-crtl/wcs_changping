#include "ApiServer.h"

#include <QString>
#include <QHostInfo>
#include <QTcpServer>
#include <QJsonParseError>
#include <QJsonObject>
#include <QDomNode>
#include <QNetworkReply>
#include <QUuid>

#include "comm/simplelog.h"
#include "ApiClient.h"

//************************************
// Method:    Initial
// FullName:  ApiServer::Initial
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void ApiServer::Initial()
{
	QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
	std::stringstream ss;
	ss << "ApiServer::Initial: Start Listen these IP Address:";
	log_info(ss.str().c_str());
	loadPortServer(QHostAddress("127.0.0.1"));
	foreach(QHostAddress address, info.addresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol) {
			// 开启监听所有本地端口
			loadPortServer(address);
		}
	}
}

// 默认 未知操作前往 -1
void ApiServer::InitialLauncher(int num, bool(*operation)(ApiMsg *) ) {
	launcher[std::to_string(num)] = operation;
}

void ApiServer::InitialLauncher(std::string key, bool(*operation)(ApiMsg *)) {
	launcher[key] = operation;
}

/// <summary>
/// Inserts the order API.
/// 加载API，监听指定端口，获取新连接
/// </summary>
/// <param name="host">The host.</param>
/// Creator:MeiXu
/// CreateDate:2021/2/7
void ApiServer::loadPortServer(QHostAddress host) {
	QTcpServer* server = new QTcpServer(this);
	//host = QHostAddress("http://" + listen_ip + listen_path);
	server->listen(host, listen_port);
	connect(server, &QTcpServer::newConnection,
		[=]() {
		getNewConnection(server);
	}
	);
	allServer.push_back(server);
	std::stringstream ss1;
	ss1 << "listen address:" << host.toString().toStdString() << ":" << std::to_string(listen_port);
	log_info(ss1.str().c_str());
	return;
}

void ApiServer::getNewConnection(QTcpServer* server) {
	// 获取连接 
	QTcpSocket* cli;
	cli = server->nextPendingConnection();
	// ApiMsg 保存信息
	ApiMsg* this_msg = new ApiMsg(this);
	all_requests_content_[cli] = this_msg;
	// 超时记录
	int timer = startTimer(default_time_out);
	all_requests_[timer] = cli;

	connect(cli, &QTcpSocket::readyRead,
		[=]() {
		// 读取数据
		QByteArray content = cli->readAll();
		bool analysis_status = all_requests_content_[cli]->readMsg(content);//index != -1;
		if (analysis_status)
		{
			bool launch_result = launchOperation(all_requests_content_[cli]);
			killTimer(timer);
			reply(cli);
		}
	}
	);
	connect(cli,
		QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
		[=]() {
		log_error("ApiServer::loadServer: SocketError");
	}
	); /* 错误反馈 */
	connect(cli,
		&QTcpSocket::disconnected,
		[=]() {
		cli->deleteLater();
		this_msg->deleteLater();
	}
	); /* 断开反馈 */
}

//************************************
// Method:    timerEvent
// FullName:  ApiServer::timerEvent
// Access:    private 
// Returns:   void
// Parameter: QTimerEvent * event
// Author:    Meixu
// Date:	  2021/07/06
// 超时事件处理
//************************************
void ApiServer::timerEvent(QTimerEvent *event) {
	int aa = event->timerId();
	auto point_msg = all_requests_content_[all_requests_[event->timerId()]];
	point_msg->generateReturnBody(false, TimeoutError, VNAME(TimeoutError));
	reply(all_requests_[event->timerId()]);
	killTimer(aa);
	log_error("ApiServer::timerEvent: Read timeout");
	return ;
}

//bool ApiServer::readyRead(QTcpSocket* client) {
//	QByteArray content = client->readAll();
//	return all_requests_content_[client]->readMsg(content);//index != -1;
//}

bool ApiServer::launchOperation(ApiMsg* msg) {
	bool result = false;
	if (launcher.find(msg->operationCode) != launcher.end())
	{
		result = (launcher[msg->operationCode])(msg);
	}
	else if (launcher.find("-1") != launcher.end())
	{
		result = (launcher["-1"])(msg);
	}
	else
	{
		result = (launcher["-1"])(msg);
	}
	return result;
}

//************************************
// Method:     reply
// FullName:   ApiServer::reply
// Access:     private 
// Returns:    void
// Parameter:  QTcpSocket * cli
// Author:     Meixu
// Date:	   2021/07/08
// Description:调用此函数前必须确保 client 对应的 msg 中 return_body 已经填充完毕
//************************************
void ApiServer::reply(QTcpSocket* cli) {
	QByteArray return_msg;
	if (all_requests_content_.find(cli) == all_requests_content_.end())
	{
		// 找不到对应消息
		return_msg = "{}";
		return;
	}
	else
	{
		auto point_msg = all_requests_content_[cli];
		// 请求报文打印
		log_info(point_msg->toString().toStdString().c_str());
		// 响应消息打印
		return_msg = point_msg->getResponseMsg();
		log_info(return_msg);

	}
	// 发送响应消息
	cli->write(return_msg);
	cli->flush();
	cli->close();
	all_requests_content_[cli]->deleteLater();
	all_requests_content_.erase(cli);
}

//************************************
// Method:     send
// FullName:   ApiServer::send
// Access:     public 
// Returns:    bool
// Parameter:  std::string path
// Parameter:  ContentType content_type
// Parameter:  QJsonObject body
// Parameter:  bool operation
// Parameter:  QJsonObject
// Author:     Meixu
// Date:	   2021/08/03
// Description:
//************************************
bool ApiServer::send(std::string path, ContentType content_type, QJsonObject body, bool operation(QJsonObject, QJsonObject))
{
	//QNetworkRequest head = ApiMsg::generateApplyHead(applicationjson, "", 625, "/");
	// 建立连接
	if (accessManager == nullptr)
	{
		accessManager = new QNetworkAccessManager(this);
	}
	// 组建请求头
	QNetworkRequest head;
	QString url = QString("http://" + QString(path.c_str()));
	head.setUrl(QUrl(url));
	head.setRawHeader("Content-Type", ApiMsg::ContentTypeStr.at(content_type).c_str());
	head.setRawHeader("Accept", ApiMsg::ContentTypeStr.at(content_type).c_str());
	if (content_type == textxml_soap)
	{
		head.setRawHeader("SOAPAction", "http://xmlme.com/WebServices/GetSpeech");
	}

	// body 转码
	body.insert("uuid", createUuid(ApiMsg::TranscodeToByte(body, content_type)));// 按照Json格式生成uuid
	QByteArray bytebody = ApiMsg::TranscodeToByte(body, content_type);
	head.setRawHeader("Content-Length", QString(bytebody.size()).toLocal8Bit());

	// 发送
	QNetworkReply *network_reply = accessManager->post(head, bytebody);
	connect(network_reply, &QNetworkReply::readyRead,
		[=]() {
		// 读取数据
		QByteArray response_body = network_reply->readAll();
		QJsonObject data;
		bool analysis_result = ApiMsg::AnalysisDatatoJson(response_body, content_type, &data);
		
		if ((operation)(data, body))
		{
			// 操作成功
		}
		else
		{
			// 发送消息成功，获取响应消息成功，但对响应消息的处理失败
			analysis_result;
		}
	}
	);
	connect(network_reply, &QNetworkReply::finished,
		[=]() {
		network_reply->deleteLater();
	});
	return true;
}

/// <summary>
/// Creates the UUID.
/// </summary>
/// <param name="data">The data.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/7
QString ApiServer::createUuid(QString data) {
	qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
	QUuid id;
	id = QUuid::createUuidV5(id, QString(data + timestamp));
	return id.toString().replace("{", "").replace("}", "");
}

//////////////////////////////////////////////////////////////////////////
std::map<ContentType, std::string> ApiMsg::ContentTypeStr =
{
{unknown, "*/*" },
{applicationjson, "application/json"},
{applicationxml, "application/xml"},
{applicationsoapxml, "application/soap+xml"},
{textxml, "text/xml"},
{textxml_soap, "text/xml"},
};

bool ApiMsg::readMsg(QByteArray msg)
{
	bool result = false;
	request_msg += msg;
	int index = request_msg.indexOf("\r\n\r\n");
	if (index != -1)
	{
		// 解析head，并尝试解析body
		body = request_msg.mid(index + 4, request_msg.size() - index - 4);
		head = request_msg.mid(0, index + 4);
		if (analysisHead())
		{
			// 解析报文
			// TODO 根据字符串转为enum
			result = resolver(Content_Type_);
			
		}
	}
	return result;
}

// 根据传入类型，使用可能的解析器解析body
bool ApiMsg::resolver(ContentType content_type)
{
	bool result = false;
	if (content_type == applicationjson)
	{
		result = analysisBodyFromJson();
	}
	else if (content_type == applicationxml || content_type == textxml)
	{
		// 普通xml 或 soap1.1
		result = analysisBodyFromXml();
	}
	else if (content_type == applicationsoapxml)
	{
		// soap1.2
		// TODO 尚未测试
		result = analysisBodyFromXml();
	}
	else if (content_type == unknown)
	{
		result = analysisBodyFromXml();
		result = result || analysisBodyFromJson();
	}
	return result;
}

bool ApiMsg::analysisHead()
{
	QList<QByteArray> head_list = head.split('\n');
	for each (auto var in head_list)
	{
		if (var.size() <= 1)
		{
			continue;
		}
		QList<QByteArray> key_value = var.split(':');
		if (key_value.size() > 1)
		{
			QByteArray key = key_value.at(0).simplified();
			QByteArray value = key_value.at(1).simplified();
			if (key == "Content-Type")
			{
				// TODO 这里可能有;分割的多个类型，待处理
				//Content_Type_ = value;
				for each (auto var in ContentTypeStr)
				{
					if (value == var.second.c_str())
					{
						Content_Type_ = var.first;
						break;
					}
				}
			}
			else if ( key == "Accept")
			{
				//Accept_ = value;
				for each (auto var in ContentTypeStr)
				{
					if (value == var.second.c_str())
					{
						Accept_ = var.first;
						break;
					}
				}
			}
			else if (key == "Host")
			{
				Host_ = value;
				Host_ += ':';
				Host_ += key_value.at(2).simplified();
			}
		}
		else
		{
			apply_path = var.split(' ')[1];
		}
	}
	return head_list.size() != 0;
}

// 解析为 XML 格式，并尝试解析为 SOAP 协议
bool ApiMsg::analysisBodyFromXml() {
	bool result = false;
	QDomDocument doc;
	result = doc.setContent(body);
	if (result)
	{
		QDomElement root = doc.documentElement();
		QJsonObject json = xmlToJson(root, 5);
		body = QJsonDocument(json).toJson();
		result = analysisBodyFromJson();
		// 判断是否是soap协议
		//log_info(TranscodeToByte(json, applicationjson));
		Content_Type_ = applicationxml;
		if (json.contains("soap12:Body")) {
			Content_Type_ = applicationsoapxml;
			taskContent = ReadObject(json, "soap12:Body");
			//log_info(QJsonDocument(taskContent).toJson());
		}
		else if (json.contains("soap:Body"))
		{
			// soap1.1协议的Content-Type居然是text/xml [8/3/2021 Meixu]
			Content_Type_ = textxml_soap;
			taskContent = ReadObject(json, "soap:Body");
		}
	}
	return result;
}

//************************************
// Method:     xmlToJson
// FullName:   ApiMsg::xmlToJson
// Access:     private 
// Returns:    QT_NAMESPACE::QJsonObject
// Parameter:  QDomElement point_node xml 文档
// Parameter:  int floor 解析层数
// Author:     Meixu
// Date:	   2021/07/29
// Description:将 point_node xml 文档 解析为json格式并返回。
//************************************
QJsonObject ApiMsg::xmlToJson(QDomElement point_node, int floor) {

	QJsonObject point_node_json;
	if (floor <= 0 || !point_node.hasChildNodes())
	{
		return point_node_json;
	}

	QDomNodeList next_floor = point_node.childNodes();
	for (int i = 0; i < next_floor.count(); i++)
	{
		QJsonObject child_node = xmlToJson(next_floor.at(i).toElement(), floor - 1);
		if (!child_node.isEmpty())
		{
			if (point_node_json.contains(next_floor.at(i).nodeName()))
			{
				// 获取之前的节点信息，拼接
				QJsonObject brother_node = ReadObject(point_node_json, next_floor.at(i).nodeName());
				brother_node.insert(child_node.begin().key(), child_node.begin().value());
				//log_error(QJsonDocument(brother_node).toJson());
				point_node_json.insert(next_floor.at(i).nodeName(), brother_node);
				//log_error(QJsonDocument(point_node_json).toJson());
			}
			else
			{
				point_node_json.insert(next_floor.at(i).nodeName(), child_node);
			}
		}
		else if (!next_floor.at(i).toElement().text().isEmpty())
		{
			point_node_json.insert(next_floor.at(i).nodeName(), next_floor.at(i).toElement().text());
		}
	}
	return point_node_json;
}

QDomDocument ApiMsg::jsonToXml(QJsonObject jsondata) {
	QDomDocument doc;
	// 添加xml标准头
	QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", R"(version="1.0" encoding="UTF-8")");
	doc.appendChild(instruction);
	// 添加根节点
	QDomElement root = doc.createElement(XML_ROOT);
	doc.appendChild(root);
	//添加元素节点到根节点
	readNextJsonToXml(jsondata, doc, &root);
	return doc;
}

//************************************
// Method:     xmlToSoap11
// FullName:   ApiMsg::xmlToSoap11
// Access:     private static 
// Returns:    QT_NAMESPACE::QDomDocument
// Parameter:  QDomDocument xml_doc
// Author:     Meixu
// Date:	   2021/07/29
// Description:带有xml头的wml文档转为soap协议格式
//************************************
QDomDocument ApiMsg::xmlToSoap11(QDomDocument xml_doc) {
	// 移除xml头
	xml_doc.removeChild(xml_doc.firstChild());
	// 添加soap头
	QDomElement strMacEnvelope = xml_doc.createElement("soap:Envelope");
	strMacEnvelope.setAttribute("xmlns:soap", "http://www.w3.org/2003/05/soap-envelope/");
	strMacEnvelope.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	strMacEnvelope.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");

	QDomElement root = xml_doc.documentElement();

	root.setTagName("soap:Body");
	strMacEnvelope.appendChild(root);
	xml_doc.appendChild(strMacEnvelope);
	
	return xml_doc;
}

QDomDocument ApiMsg::xmlToSoap12(QDomDocument xml_doc) {
	// 移除xml头
	xml_doc.removeChild(xml_doc.firstChild());
	// 添加soap头
	QDomElement strMacEnvelope = xml_doc.createElement("soap12:Envelope");
	strMacEnvelope.setAttribute("xmlns:soap12", "http://www.w3.org/2003/05/soap-envelope");
	strMacEnvelope.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	strMacEnvelope.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");

	QDomElement root = xml_doc.documentElement();

	root.setTagName("soap12:Body");
	strMacEnvelope.appendChild(root);
	xml_doc.appendChild(strMacEnvelope);

	return xml_doc;
}

bool ApiMsg::readNextJsonToXml(QJsonObject jsondata, QDomDocument doc, QDomElement *root) {
	auto keys = jsondata.keys();
	for each (auto var in keys)
	{
		QDomElement strMac = doc.createElement(var);//创建元素节点
		if (jsondata[var].isObject())
		{
			readNextJsonToXml(jsondata[var].toObject(), doc, &strMac);
		}
		else
		{
			QDomText strMacNodeText;
			switch (jsondata[var].type())
			{
			case QJsonValue::Type::Null:
				break;
			case QJsonValue::Type::String:
				strMacNodeText = doc.createTextNode(jsondata[var].toString());//创建元素文本
				break;
			case QJsonValue::Type::Bool:
				strMacNodeText = doc.createTextNode(QString::number(jsondata[var].toBool()));//创建元素文本
				break;
			case QJsonValue::Type::Double:
				strMacNodeText = doc.createTextNode(QString::number(jsondata[var].toDouble()));//创建元素文本
				break;
			default:
				break;
			}
			 
			strMac.appendChild(strMacNodeText);//添加元素文本到元素节点
		}

		root->appendChild(strMac);
	}
	return true;
}

bool ApiMsg::analysisBodyFromJson() {
	bool result = false;
	QJsonParseError jsonError;
	QJsonDocument doucment = QJsonDocument::fromJson(body, &jsonError);
	if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
	{ // JSON读取没有出错
		if (doucment.isObject())
		{
			// 接收传入数据
			bodyContent = doucment.object();
			//QVariantMap map = bodyContent.toVariantMap();
			uuid = ReadString(bodyContent, "uuid");
			operationCode = ReadString(bodyContent, "bizType");
			callCode = ReadString(bodyContent, "callCode");
			std::string tmp_string = ReadString(bodyContent, "taskJson");
			QJsonDocument task_doucment = QJsonDocument::fromJson(tmp_string.c_str(), &jsonError);
			if (!task_doucment.isNull() && (jsonError.error == QJsonParseError::NoError) && task_doucment.isObject()) {
				taskContent = task_doucment.object();
			}
			else
			{
				taskContent = ReadObject(bodyContent, "taskContent");
			}
		}
		result = true;
		Content_Type_ = applicationjson;
	}
	return result;
}

/// <summary>
/// get current time.
/// </summary>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/24
/// 
QString ApiMsg::CurrentTime() {
	return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}


/// <summary>
/// Reads the string from JsonObject
/// </summary>
/// <param name="object">The object.</param>
/// <param name="key">The key.</param>
/// <returns></returns>
/// Creator:MeiXu
/// CreateDate:2021/2/19
std::string ApiMsg::ReadString(QJsonObject object, QString key) {
	std::string value = "";
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isString())
		{  
			// 判断 value 是否为字符串
			value = object.value(key).toString().toLocal8Bit().toStdString();
		}
		else if (json_value.isDouble())
		{
			value = std::to_string((int)object.value(key).toDouble());
		}
		else if (json_value.isBool())
		{
			value = object.value(key).toBool() == true ? "true" : "false";
		}
		else if (json_value.isObject())
		{
			value = (QString(QJsonDocument(object.value(key).toObject()).toJson())).toStdString();
		}
	}
	return value;
}

QJsonObject ApiMsg::ReadObject(QJsonObject object, QString key) {
	QJsonObject value;
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isObject())
		{  // 判断 value 是否为字符串
			value = object.value(key).toObject();
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
double ApiMsg::ReadNumber(QJsonObject object, QString key) {
	double value = -1;
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isDouble())
		{  // 判断 value 是否为数字
			value = json_value.toDouble();
		}
		else
		{
			value = json_value.toString().toDouble();
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
bool ApiMsg::ReadBool(QJsonObject object, QString key) {
	bool value = false;
	if (object.contains(key))
	{  // 包含指定的 key
		QJsonValue json_value;
		json_value = object.value(key);
		if (json_value.isBool())
		{  // 判断 value 是否为Bool
			value = json_value.toBool();
		}
		else if (json_value.isString())
		{
			QString msg = json_value.toString();
			value = msg.toUpper() == "TRUE";// 转成大写后是否 为“TRUE”
		}
		else if (json_value.isDouble())
		{
			value = json_value.toDouble() != 0;
		}
	}
	return value;
}

QByteArray ApiMsg::generateReturnHead(int length) {

	return_head = "";
	return_head += "HTTP/1.1 200 OK\r\n";
	if (length > 0)
	{
		return_head += "Content-Length: " + QString(std::to_string(length).c_str()) + "\r\n";
	}
	Accept_ = Accept_ == Unknown ? Content_Type_ : Accept_;
	return_head += ("Content-Type: " + ContentTypeStr.at(Accept_) + "\r\n").c_str();
	return_head += ("Accept: " + ContentTypeStr.at(Accept_) + "\r\n").c_str();
	return_head += "\r\n";
	return return_head;
}

//************************************
// Method:     generateReturnBody
// FullName:   ApiMsg::generateReturnBody
// Access:     public 
// Returns:    void
// Parameter:  bool valid
// Parameter:  int code
// Parameter:  const char * msg
// Author:     Meixu
// Date:	   2021/07/09
// Description:生成响应消息的第一层内容
// 如果 valid 为 true ，则 code 与 msg 将由 OperationSuccess 填充
// 否则，由指定错误填充
//************************************
void ApiMsg::generateReturnBody(bool valid, int code /*= DefaultErrorCode*/, const char* msg /*= VNAME(DefaultErrorCode)*/, QJsonObject *object /*= new QJsonObject()*/) {
	if (return_body.find("valid") != return_body.end())
	{
		return;
	}
	object->insert("operateTime", CurrentTime());
	object->insert("valid", valid);
	if (valid)
	{
		object->insert("code", OperationSuccess);
		object->insert("message", VNAME(OperationSuccess));
	}
	else
	{
		object->insert("code", code);
		object->insert("message", msg);
	}
	return_body = *object;
}

//************************************
// Method:     getResponseMsg
// FullName:   ApiMsg::getResponseMsg
// Access:     public 
// Returns:    QT_NAMESPACE::QByteArray
// Author:     Meixu
// Date:	   2021/07/09
// Description:拼接响应消息
//************************************
QByteArray ApiMsg::getResponseMsg()
{
	if (!task_content.isEmpty())
	{
		return_body.insert("taskContent", task_content);
	}
	QByteArray return_body_char;
	QJsonDocument json_doc;
	if (Accept_ == unknown)
	{
		Accept_ = Content_Type_ == unknown ? applicationjson : Content_Type_;
	}
	if (Accept_ == applicationxml || Accept_ == textxml || Accept_ == applicationsoapxml)
	{
		QDomDocument doc = jsonToXml(return_body);
		if (Accept_ == applicationsoapxml)
		{
			return_body_char = xmlToSoap12(doc).toByteArray();
		}
		else if (Accept_ == textxml && Content_Type_ == textxml_soap)
		{
			return_body_char = xmlToSoap11(doc).toByteArray();
		}
		else
		{
			return_body_char = doc.toByteArray();
		}
	}
	else if (Accept_ == applicationjson)
	{
		json_doc.setObject(return_body);
		return_body_char = json_doc.toJson(QJsonDocument::Compact);
	}
	else {
		// 未知要求响应类型
	}
	generateReturnHead(return_body_char.length());
	return return_head + return_body_char;
}

QString ApiMsg::toString()
{
	return request_msg;
}


//************************************
// Method:     generateApplyHead
// FullName:   ApiMsg::generateApplyHead
// Access:     public static 
// Returns:    QT_NAMESPACE::QNetworkRequest
// Parameter:  std::string content_type : applicationjson / applicationsoapxml / textxml / applicationxml / unknown
// Parameter:  std::string ip
// Parameter:  int port
// Parameter:  std::string path
// Author:     Meixu
// Date:	   2021/08/02
// Description:
//************************************
//QNetworkRequest ApiMsg::generateApplyHead(ContentType content_type, std::string ip, int port, std::string path) {
//	/*****
//	POST /api/agv HTTP/1.1
//	Content-Type: application/xml
//	User-Agent: PostmanRuntime/7.28.2
//	Accept: *//*
//	Host: 127.0.0.1:625
//	Accept-Encoding: gzip, deflate, br
//	Connection: keep-alive
//	Content-Length: 389
//	*/
//	QNetworkRequest request;
//	QString url = QString("http://" + QString(ip.c_str()) + ":" + QString::number(port) + QString(path.c_str()));
//	request.setUrl(QUrl(url));
//	request.setRawHeader("Content-Type", ContentTypeStr.at(content_type).c_str());
//	//request.setRawHeader("Accept", content_type.c_str());
//
//	return request;
//}


//************************************
// Method:     AnalysisDatatoJson
// FullName:   ApiMsg::AnalysisDatatoJson
// Access:     public static 
// Returns:    bool
// Parameter:  QByteArray data
// Parameter:  std::string content_type
// Parameter:  QJsonObject * return_data
// Author:     Meixu
// Date:	   2021/08/02
// Description:根据指定格式解析字符串，并转码为 Json 
//************************************
bool ApiMsg::AnalysisDatatoJson(QByteArray data, ContentType content_type, QJsonObject *return_data) {
	bool result = false;
	if (content_type == applicationjson)
	{
		result = AnalysisDataFromJson(data, return_data);
	}
	else if (content_type == applicationsoapxml || content_type == textxml || content_type == applicationxml)
	{
		QDomDocument xml_data;
		result = AnalysisDataFromXml(data, &xml_data);
		if (result)
		{
			// 成功解析为XML文档
			*return_data = xmlToJson(xml_data.documentElement(), 5);
			if (return_data->contains("soap12:Body")) {
				*return_data = ReadObject(*return_data, "soap12:Body");
			}
		}
	}
	else if (content_type == unknown)
	{
		// 未知操作类型
	}
	return result;
}

//************************************
// Method:     AnalysisDataFromXml
// FullName:   ApiMsg::AnalysisDataFromXml
// Access:     public static 
// Returns:    bool
// Parameter:  QByteArray data
// Parameter:  QDomDocument * return_data
// Author:     Meixu
// Date:	   2021/08/02
// Description:输入的 data 转化为 XML 对象
//************************************
bool ApiMsg::AnalysisDataFromXml(QByteArray data, QDomDocument *return_data) {
	return return_data->setContent(data);
}

//************************************
// Method:     AnalysisDataFromJson
// FullName:   ApiMsg::AnalysisDataFromJson
// Access:     public static 
// Returns:    bool
// Parameter:  QByteArray data
// Parameter:  QJsonObject * return_data
// Author:     Meixu
// Date:	   2021/08/02
// Description:输入的 data 转化为 Json 对象
//************************************
bool ApiMsg::AnalysisDataFromJson(QByteArray data, QJsonObject *return_data) {
	bool result = false;
	QJsonParseError jsonError;
	QJsonDocument doucment = QJsonDocument::fromJson(data, &jsonError);
	if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
	{ // JSON读取没有出错
		if (doucment.isObject())
		{
			// 接收传入数据
			*return_data = doucment.object();
			result = true;
		}
	}
	return result;
}

//************************************
// Method:     TranscodeToByte
// FullName:   ApiMsg::TranscodeToByte
// Access:     public static 
// Returns:    QT_NAMESPACE::QByteArray
// Parameter:  QJsonObject data
// Parameter:  std::string content_type
// Author:     Meixu
// Date:	   2021/08/02
// Description:将 Json 对象转码后，输出为对应格式的字符串
//************************************
QByteArray ApiMsg::TranscodeToByte(QJsonObject data, ContentType content_type) {
	QByteArray result;
	QJsonDocument json_doc;
	if (content_type == applicationjson)
	{
		result = TranscodeToByteJson(data);
	} 
	else if (content_type == textxml_soap)
	{
		result = TranscodeToByteSoap11(data);
	}
	else if (content_type == applicationsoapxml)
	{
		result = TranscodeToByteSoap12(data);
	}
	else if (content_type == textxml || content_type == applicationxml)
	{
		result = TranscodeToByteXml(data);
	}
	else if (content_type == unknown)
	{
		// 未知操作类型
	}
	else
	{
		// 未知操作类型
	}
	return result;
}

QByteArray ApiMsg::TranscodeToByteJson(QJsonObject data) {
	QJsonDocument json_doc;
	json_doc.setObject(data);
	return json_doc.toJson(QJsonDocument::Compact);
}

QByteArray ApiMsg::TranscodeToByteXml(QJsonObject data) {
	QDomDocument doc = jsonToXml(data);
	return doc.toByteArray();
}

QByteArray ApiMsg::TranscodeToByteSoap11(QJsonObject data) {
	QDomDocument doc = jsonToXml(data);
	return xmlToSoap11(doc).toByteArray();
}

QByteArray ApiMsg::TranscodeToByteSoap12(QJsonObject data) {
	QDomDocument doc = jsonToXml(data);
	return xmlToSoap12(doc).toByteArray();
}