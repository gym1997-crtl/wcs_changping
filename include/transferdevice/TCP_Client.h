#ifndef _TCP_CLIENT_KYOSHO_20110904_
#define _TCP_CLIENT_KYOSHO_20110904_

#include "transferdevice/TransferDevice.h"

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;

class cTCPClient : cTransferDevice
{
private:

	ip::tcp::socket* m_sock;  //����socket����
	ip::tcp::endpoint* m_endpoint;  //�������Ӷ˵�

public:
	cTCPClient(void);
	~cTCPClient(void);

	bool Open();
	bool Close();

	void Read();
	bool Write();

};
#endif //_TCP_CLIENT_KYOSHO_20110904_