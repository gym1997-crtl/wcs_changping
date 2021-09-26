
#include "transferdevice/SerialPort.h"
#include "comm/Comm.h"
#include "comm/Log.h"

cSerialPort::cSerialPort(void)
{
	m_pSerialPort = NULL;
}

cSerialPort::~cSerialPort(void)
{
	if (m_pSerialPort != NULL)
	{
		delete m_pSerialPort;
		m_pSerialPort = NULL;
	}
	
}

bool cSerialPort::Open(){
try{

	if (m_pSerialPort != NULL)
	{
		std::cout<<"delete serial port"<<std::endl;
		delete m_pSerialPort;
		m_pSerialPort = NULL;
		std::cout<<"delete serial port over!"<<std::endl;
	}

	std::string strComNo;
  	//strComNo = "COM";

	m_pSerialPort = new boost::asio::serial_port(m_ios ,m_ConnPara.getDeviceName());

	m_pSerialPort->set_option(boost::asio::serial_port::baud_rate(m_ConnPara.nBaud));
	m_pSerialPort->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
	if (m_ConnPara.chParity == 'N')
	{
		m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
	}
	if (m_ConnPara.chParity == 'O') //��У��
	{
		m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::odd));
	}
	if (m_ConnPara.chParity == 'E')  //żУ��
	{
		m_pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::even));
	}
	
	if (m_ConnPara.nStopBits = 1)
	{
		m_pSerialPort->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
	}
	else
	{
		return false;
	}
	m_pSerialPort->set_option(boost::asio::serial_port::character_size(m_ConnPara.nDataBits));
	
	return true;
}
catch (std::exception &e)
{
	/*LOGS("SerialPort")<<"Serial port open err!";*/
	return false;
}
	
}
bool cSerialPort::Close()
{
	if (m_pSerialPort != NULL)
	{
		delete m_pSerialPort;
		m_pSerialPort = NULL;
	}
	

	cTransferDevice::Close();
	return true;
}

bool cSerialPort::Write()
{
	if(!m_pSerialPort){
		return false;
	}

	size_t len = m_pSerialPort->write_some(boost::asio::buffer(m_szWriteBuffer,m_nWriteBufferSize));
	if (m_nWriteBufferSize == len)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cSerialPort::Read()
{
	if(!m_pSerialPort){
		std::cout<<"err serial port read!"<<std::endl;
		return;
	}

	m_pSerialPort->async_read_some(boost::asio::buffer(m_szReadTemp,m_bufSize), 
		boost::bind(&cTransferDevice::read_callback,(cTransferDevice*)this,  
   		boost::asio::placeholders::error,   boost::asio::placeholders::bytes_transferred)); 
}
