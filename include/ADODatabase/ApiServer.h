#ifndef API_SERVER_H_
#define API_SERVER_H_
#include <string>
#include <boost/serialization/singleton.hpp>

#include <QObject>
#include <QTcpServer>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QHostAddress>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QDomElement>

//#define unknown "*/*"
//#define applicationjson "application/json"
//#define applicationxml "application/xml"
//#define applicationsoapxml "application/soap+xml"
//#define textxml "text/xml"
//#define textxml_soap "text/xml"
// 获取变量名
#define VNAME(value) (#value)

class ApiMsg;
class ApiClient;
class ApiMessage;
using OperationError = enum {
	DefaultErrorCode = -1,//默认：未知错误
	OperationSuccess = 20,// 操作成功
	DatabaseError = 41,// 数据库操作失败
	UnknownOperationCode = 42, //未知操作码
	TimeoutError = 51,// 超时失败
};

using ContentType = enum {
	unknown,
	applicationjson,// json
	applicationxml,// xml
	applicationsoapxml, // soap1.2
	textxml,// xml
	textxml_soap// soap1.1
};



class ApiServer : public QObject
{
	Q_OBJECT

public:

	ApiServer(QObject *parent = nullptr) {};

	~ApiServer() {};
	// 监听所有本地IP的指定端口
	void Initial();

	bool send(std::string path, ContentType content_type, QJsonObject body, bool operation(QJsonObject, QJsonObject));

	void InitialLauncher(int num, bool(*operation)(ApiMsg *));

	void InitialLauncher(std::string key, bool(*operation)(ApiMsg *));
private:

	std::vector<QTcpServer*> allServer;
	std::map<std::string, bool(*)(ApiMsg *)> launcher;

	void loadPortServer(QHostAddress host);

	void getNewConnection(QTcpServer * server);

	//bool readyRead(QTcpSocket * client);

	void reply(QTcpSocket * cli);

	const static int default_time_out = 10000;// 10s
	const int listen_port = 625;

	bool launchOperation(ApiMsg* msg);
	// 记录传入连接的定时器
	std::map<int, QTcpSocket*> all_requests_;
	// 记录传入连接的数据
	std::map<QTcpSocket*, ApiMsg*> all_requests_content_;
	
	QString createUuid(QString data);

	QNetworkAccessManager *accessManager;

private slots:
	// 处理超时消息
	void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
};
//////////////////////////////////////////////////////////////////////////
#define XML_ROOT "root"

class ApiMsg : public QObject
{
	Q_OBJECT

public:

	static std::map<ContentType, std::string> ContentTypeStr;

	ApiMsg(QObject *parent = nullptr) {};
	~ApiMsg() {};
	// 持续读，当报文解析成功时返回true, 此时, 以下各字段解析为请求报文的值
	bool readMsg(QByteArray msg);

	// head
	ContentType Content_Type_ = unknown;
	ContentType Accept_ = unknown;	// head
	QByteArray apply_path;
	QByteArray Host_;
	// body
	QJsonObject bodyContent;// 整个 JSON 数据
	// 标准格式下的4个关键字
	std::string uuid;
	std::string callCode;
	std::string operationCode;
	QJsonObject taskContent;

	void generateReturnBody(bool valid, int code = DefaultErrorCode, const char* msg = VNAME(DefaultErrorCode), QJsonObject *object = new QJsonObject());

	QByteArray getResponseMsg();

	QString toString();
	
	// 读取 QJsonObject 的 key 指向的值
	static std::string ReadString(QJsonObject object, QString key);

	static QJsonObject ReadObject(QJsonObject object, QString key);

	static double ReadNumber(QJsonObject object, QString key);

	static bool ReadBool(QJsonObject object, QString key);

	static QJsonObject xmlToJson(QDomElement point_node, int floor);

	static QDomDocument jsonToXml(QJsonObject jsondata);
	
	static QDomDocument xmlToSoap11(QDomDocument xml_doc);

	static QDomDocument xmlToSoap12(QDomDocument xml_doc);
	
	static QString CurrentTime();
	
	//static QNetworkRequest generateApplyHead(ContentType content_type, std::string ip = "127.0.0.1", int port = 625, std::string path = "/");

	static bool AnalysisDatatoJson(QByteArray data, ContentType content_type, QJsonObject * return_data);
	
	static QByteArray TranscodeToByte(QJsonObject data, ContentType content_type);
private:

	QByteArray request_msg;// 收到的所有消息
	QByteArray head;
	QByteArray body;

	// return head
	QByteArray return_head;
	// return body
	QJsonObject return_body;
	QJsonObject task_content;

	bool analysisHead();
	bool resolver(ContentType content_type);
	bool analysisBodyFromXml();
	bool analysisBodyFromJson();

	QByteArray generateReturnHead(int lenth = 0);

	static bool readNextJsonToXml(QJsonObject jsondata, QDomDocument doc, QDomElement *root);

	static inline bool AnalysisDataFromXml(QByteArray data, QDomDocument *return_data);

	static bool AnalysisDataFromJson(QByteArray data, QJsonObject * return_data);

	// QJsonObject 转码为 不同格式的 QByteArray
	static QByteArray TranscodeToByteJson(QJsonObject data);

	static QByteArray TranscodeToByteXml(QJsonObject data);

	static QByteArray TranscodeToByteSoap11(QJsonObject data);

	static QByteArray TranscodeToByteSoap12(QJsonObject data);

};

typedef boost::serialization::singleton<ApiServer> Singleton_Api_Server;
#define API_SERVER Singleton_Api_Server::get_mutable_instance()

#endif // #ifndef API_SERVER_H_