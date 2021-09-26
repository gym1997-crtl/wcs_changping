#ifndef _TCP_SERVER_KYOSHO_20110904_
#define _TCP_SERVER_KYOSHO_20110904_

#include "transferdevice/TransferDevice.h"

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;

class cTCP_Server : public cTransferDevice
{

public:
	cTCP_Server(void);
	~cTCP_Server(void);

	bool Open();
	bool Close();
	void Start();
//	void Accept_handler(const system::error_code& ec);

	void Read();
	bool Write();
private:
	//ip::tcp::socket* m_sock;  //创建socket对象
	ip::tcp::acceptor* acceptor_;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	//ip::tcp::socket* sock_;
	sock_pt p_sock_;

};

#endif //_TCP_SERVER_KYOSHO_20110904_