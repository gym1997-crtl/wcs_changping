#ifndef _SERIALPORT_KYOSHO_20110904_
#define _SERIALPORT_KYOSHO_20110904_

#include "transferdevice/TransferDevice.h"

class cSerialPort : cTransferDevice
{
private:
	boost::asio::serial_port* m_pSerialPort;
public:
	cSerialPort(void);
	~cSerialPort(void);
	
	bool Open();
	virtual bool Close();

	void Read();
	bool Write();

};

#endif //_SERIALPORT_KYOSHO_20110904_