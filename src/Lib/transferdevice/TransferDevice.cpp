#include <boost/date_time/posix_time/posix_time.hpp>
#include "comm/Log.h"
#include "comm/Comm.h"

#include "transferdevice/SerialPort.h"
#include "transferdevice/TCP_Client.h"
#include "transferdevice/TCP_Server.h"

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost::gregorian;

mTransferDeviceP cTransferDevice::m_mTransferDeviceP;

Manage<cTransferDevice> cTransferDevice::list_;

int cTransferDevice::m_bufSize = BUF_MAX_SIZE;
int cTransferDevice::id_all_ = 0;

int cConnPara::SERIALPORT = 1;
int cConnPara::NETWORK = 2;
int cConnPara::TCPCLIENT = 3;
int cConnPara::TCPSERVER = 4;
int cConnPara::UPD = 5;
//********************************************************************
//  CConnPara   函数注释
//  函数名称:   CConnPara 
//  函数类型:   构造函数 
//  函数参数:   无
//  返回值  :   无
//  作者    :   wanghongtao
//  创建时间:   2010/4/20 13:48
//  描述    :   构造函数
//*********************************************************************
cConnPara::cConnPara()
{
 	m_iType = SERIALPORT;
 
#ifdef _WIN32
 	sDeviceName = "\\\\.\\COM1"; //���ں�
#else
	sDeviceName = "/dev/ttyUSB0"; //���ں�
#endif

 	nBaud=57600;      //������
 
 	chParity= 'N';   //校验位
 	nDataBits=8;  //数据位
 	nStopBits=1;  //停止位
 
 	iAdd=6;      //设备地址
 
 	iDefSample = 1;  //默认采样周期
 	iTimeout=80;     //超时时间(秒)-重要参数（ReflashTime必须小于lReflash帧间隔；必须大于byTimeout帧超时时间）
 	//	byTimeoutMax=1;  //超时重试次数
 	lReflash = 100; //更新周期（毫秒）数据帧之间的间隔-重要参数（ReflashTime必须小于lReflash帧间隔；必须大于byTimeout帧超时时间）
	//tcp client
 	m_nNetType = cConnPara::TCPCLIENT;  //网络通讯类型（tcp、udp）
 	m_nLocalPort = 2001; //本地端口
	m_nRemoteIP = "192.168.2.100";  //远程IP
	m_nRemotePort = 2000;//远程端口
	//tcp server
	n_listen_port = 2011; // 监听本地端口

}
//********************************************************************
//      ~CConnPara    函数注释
//  函数名称  :   ~CConnPara 
//  函数类型  :   析构函数 
//  函数参数  :   无
//  返回值  :     无
//    作者    :    wanghongtao
//    创建时间:    2010/4/20 13:48
//    描述  :      析构函数
//*********************************************************************
cConnPara::~cConnPara()
{

}
//********************************************************************
//      CheckConn    函数注释
//  函数名称  :   CheckConn 
//  函数类型  :   public 
//  函数参数  :   CConnPara* pConnPara 需要比较的参数指针
//  返回值  :     bool：true一致 false不一致
//    作者    :    wanghongtao
//    创建时间:    2010/4/20 13:48
//    描述  :      比较通讯参数是否一致
//*********************************************************************
bool cConnPara::CheckConn(const cConnPara& ConnPara)
{
	if (m_iType ==  ConnPara.m_iType)
	{
		if (m_iType == cConnPara::SERIALPORT )
		{	
			if ((sDeviceName == ConnPara.sDeviceName) && (nBaud == ConnPara.nBaud) && (chParity == ConnPara.chParity) && (nDataBits == ConnPara.nDataBits) && (nStopBits == ConnPara.nStopBits))
			{
				return true;
			}
		}
		if (m_iType == cConnPara::NETWORK )
		{
			if (m_nNetType == cConnPara::TCPCLIENT)
			{
				if (m_nLocalPort == ConnPara.m_nLocalPort) 	
				{
					if (m_nRemoteIP == ConnPara.m_nRemoteIP)
					{
						if (m_nRemotePort == ConnPara.m_nRemotePort)
						{
							return true;
						}
					}
					
				}
			}
			if (m_nNetType == cConnPara::TCPSERVER)
			{
				if (n_listen_port ==  ConnPara.n_listen_port)
				{
					return true;
				}
			}
 			
		}
	}
	return false;
}

bool cConnPara::CanCreate( const cConnPara& ConnPara )
{
	if (m_iType ==  ConnPara.m_iType)
	{
		if (m_iType == cConnPara::SERIALPORT )
		{	
			if ( sDeviceName == ConnPara.sDeviceName ){
				if((nBaud == ConnPara.nBaud) && (chParity == ConnPara.chParity) && (nDataBits == ConnPara.nDataBits) && (nStopBits == ConnPara.nStopBits))
				{
					assert(false);  //所有参数都不同，之前已经处理过了，不可能发生。
					return false;
				}
				else
				{
					return false;
				}
			}
		}
		if (m_iType == cConnPara::NETWORK )
		{
			if (m_nNetType == cConnPara::TCPCLIENT)
			{
				if ((m_nLocalPort == ConnPara.m_nLocalPort) && (m_nRemoteIP == ConnPara.m_nRemoteIP) &&(m_nRemotePort == ConnPara.m_nRemotePort))
				{
					assert(false);  //所有参数都不同，之前已经处理过了，不可能发生。
					return false;
				}
				else{
					return true;
				}
			}
			if (m_nNetType == cConnPara::TCPSERVER)
			{
				if (n_listen_port == ConnPara.n_listen_port)
				{
					assert(false);  //所有参数都不同，之前已经处理过了，不可能发生。
					return false;
				}
				else{
					return true;
				}
			}
			
		}
	}
	return true;
}
void cConnPara::setDeviceName(std::string nm){
	
#ifdef _WIN32
	sDeviceName = "\\\\.\\";
	sDeviceName += nm;
#else
	sDeviceName = "/dev/";
	sDeviceName += nm;
#endif
}

std::string cConnPara::getDeviceName()
{
	return sDeviceName;
}

cTransferDevice::cTransferDevice(void)
{
	m_Status.SetClose();

	m_lReadBuffer.Init(BUF_MAX_SIZE);

	memset(m_szWriteBuffer,0,BUF_MAX_SIZE);
	m_nWriteBufferSize = 0;
	
	m_iInstanceCount = 0;

	m_threadRun = NULL;

	m_btime_out = false;
	
	id_ = CreateID();

	th_run_ = false;
}

cTransferDevice::~cTransferDevice(void)
{
//	Close();

}
cTransferDevice* cTransferDevice::GetInstance(const cConnPara& ConnPara )
{
	
	cTransferDevice* pTransferDevice = NULL;
	//查看是否已经存在相同参数的设备
  	mTransferDeviceP::const_iterator  cit = m_mTransferDeviceP.begin();
  	for (;cit!= m_mTransferDeviceP.end();++cit)
  	{
  		pTransferDevice = cit->second;
  		if (pTransferDevice->m_ConnPara.CheckConn(ConnPara))
  		{
			std::string device_name = pTransferDevice->m_ConnPara.getDeviceName();
			//LOGS_INFO("TransferDevice")<<"GetExistInstance:"<<pTransferDevice->m_ConnPara.nCommNO;
			/*LOGS("TransferDevice")<<"GetExistInstance:"<<device_name;*/
			pTransferDevice->m_iInstanceCount++;
  			return pTransferDevice;
  		}
  	}
	//查看参数是否有冲突
	cit = m_mTransferDeviceP.begin();
	for (;cit!= m_mTransferDeviceP.end();++cit)
	{
		pTransferDevice = cit->second;
		if (!pTransferDevice->m_ConnPara.CanCreate(ConnPara))
		{
			LOGS("TransferDevice")<<"Para Error:"<<pTransferDevice->m_ConnPara.getDeviceName();
			//LOGS_WARN("TransferDevice")<<"Para Error:"<<pTransferDevice->m_ConnPara.nCommNO;
			pTransferDevice = NULL;
			return pTransferDevice;
		}
	}

  
  	if (ConnPara.m_iType == cConnPara::SERIALPORT)
  	{
  		typedef mTransferDeviceP::value_type vType;
  
  		int iIndex = m_mTransferDeviceP.size();
		pTransferDevice = (cTransferDevice*)new cSerialPort();
		assert(pTransferDevice != NULL);
  		if(!pTransferDevice->Init(ConnPara))
  		{
  			delete pTransferDevice;
  			pTransferDevice = NULL;
  			return NULL;
  		}
		pTransferDevice->m_iInstanceCount = 1;
  		m_mTransferDeviceP.insert(vType(pTransferDevice->ID(),pTransferDevice));
  		
  		return pTransferDevice;
  	}
  	if ((ConnPara.m_iType == cConnPara::NETWORK) && (ConnPara.m_nNetType == cConnPara::TCPCLIENT))
  	{
  		typedef mTransferDeviceP::value_type vType;
  		
  		int iIndex = m_mTransferDeviceP.size();
  		pTransferDevice = (cTransferDevice*)new cTCPClient();
  		if(!pTransferDevice->Init(ConnPara))
  		{
  			delete pTransferDevice;
  			pTransferDevice = NULL;
  			return NULL;
  		}
		pTransferDevice->m_iInstanceCount = 1;
  		m_mTransferDeviceP.insert(vType(pTransferDevice->ID(),pTransferDevice));
 		return pTransferDevice;
 	}

	if ((ConnPara.m_iType == cConnPara::NETWORK) && (ConnPara.m_nNetType == cConnPara::TCPSERVER))
	{
		typedef mTransferDeviceP::value_type vType;

		int iIndex = m_mTransferDeviceP.size();
		pTransferDevice = (cTransferDevice*)new cTCP_Server();
		if(!pTransferDevice->Init(ConnPara))
		{
			delete pTransferDevice;
			pTransferDevice = NULL;
			return NULL;
		}
		pTransferDevice->m_iInstanceCount = 1;
		m_mTransferDeviceP.insert(vType(pTransferDevice->ID(),pTransferDevice));
		return pTransferDevice;
	}
 
 	return NULL;
}


bool cTransferDevice::Init( const cConnPara& ConnPara )
{
	m_ConnPara = ConnPara;

	m_lReadBuffer.Init(BUF_MAX_SIZE);

	memset(m_szWriteBuffer,0,BUF_MAX_SIZE);
	m_nWriteBufferSize = 0;

	return BeginThread();
}


bool cTransferDevice::BeginThread()
{
	if (m_threadRun!= NULL)
	{
		delete m_threadRun;
		m_threadRun = NULL;
	}

	LOGS("SerialPort")<<"Begin Device thread!!";

 	m_threadRun = new boost::thread(boost::bind(&cTransferDevice::ThreadRun,this));
 	if (m_threadRun)
 	{
 		return true;
 	}
 	else
 	{
 		return false;
 	}
}

void cTransferDevice::EndThread()
{
	th_run_ = false;

	if (m_threadRun != NULL)
	{
		m_ios.stop();
		m_ios.reset();
		SLEEP(10);
		//m_threadRun->interrupt();
		m_threadRun->join();

		delete m_threadRun;
		m_threadRun = NULL;

		LOGS("SerialPort")<<"End Device thread!!";
	}
	
}

int cTransferDevice::ThreadRun()
{	
	th_run_ = true;

try{
	while (th_run_)
	{
		if (Open())
		{

			SetOpen();
			Read();
			
			m_ios.run();
			m_ios.reset();

			boost::this_thread::interruption_point();
		}
		
		boost::this_thread::interruption_point();
		/*LOGS("SerialPort")<<"ReOpen Device";*/
		SLEEP(1000);

	}
	return 0;
}
catch(thread_interrupted)
{
	cout<<"thread interrupted"<<endl;
	return -1;
}
}

bool cTransferDevice::WriteData(/*In*/unsigned char* pData,int Len)
{

 	if (!m_Status.IsOpen())
 	{
 		return false;
 	}
	//m_read_write_Lock.lock();
	//mutex::scoped_lock lock(m_read_write_Lock); for wuhan 20130112
	//cout<<"write"<<endl;
	assert(pData!=NULL);


	if (!pData || Len > BUF_MAX_SIZE)
	{
		return false;
	}

	m_lReadBuffer.Clear();
	memset(m_szWriteBuffer,0,BUF_MAX_SIZE);
	m_nWriteBufferSize = Len;
	memcpy(m_szWriteBuffer,pData,Len);

	return Write();
}
int cTransferDevice::ReadData( /*Out*/unsigned char* pReceiveData,int& iLen,/*In*/int iReclen,int iTimeout)
{

	if (!m_Status.IsOpen())
	{
		//m_read_write_Lock.unlock();
		return 0;
	}
	
	if (iReclen == -1)
	{
		iReclen = m_lReadBuffer.Size();
	}

	if (iReclen > BUF_MAX_SIZE)
	{
		std::cout<<"buf out:"<<iReclen<<std::endl;
		iReclen = BUF_MAX_SIZE;
	}

	memset(pReceiveData,0,iReclen);
	iLen = 0;

	int len_tmp = 0;

	while(1){

		len_tmp = m_lReadBuffer.Size();
		if ( len_tmp >= iReclen)
		{

			//std::cout<<"read data over"<<std::endl;
			break;
		}
		if (iTimeout--)
		{
			SLEEP(1);
			//std::cout<<"sleep 1ms"<<std::endl;
		}
		else{
			//std::cout<<"-----------time out"<<std::endl;
			break;
		}
	}
	m_lReadBuffer.Read(pReceiveData,iLen);

	return iLen;

}

bool cTransferDevice::Close()
{	
	m_Status.SetClose();
	EndThread();
	SLEEP(500);
	return true;
}
bool cTransferDevice::Write()
{
	assert(false);
	return false;
}

void cTransferDevice::Read()
{
	assert(false);
}

void cTransferDevice::read_callback( const boost::system::error_code& error, std::size_t bytes_transferred)
{   
	//mutex::scoped_lock lock(m_readlock);

 	if (error )   
 	{     // No data was read!
		m_Status.SetClose();
		LOGS("TransferDevice")<<"Callback err !!"<<boost::system::system_error(error).what();
		return;   
 	} 


	m_lReadBuffer.Write(m_szReadTemp,bytes_transferred);

	Read();
 } 
void cTransferDevice::wait_callback( const boost::system::error_code& error) 
{  
	
	//Close();

} 

bool cTransferDevice::DelInstance(const cConnPara& ConnPara)
{
	cTransferDevice* pTransferDevice = NULL;
	mTransferDeviceP::iterator  it = m_mTransferDeviceP.begin();
	for (;it != m_mTransferDeviceP.end(); )
	{
		pTransferDevice = it->second;
		if (pTransferDevice->m_ConnPara.CheckConn(ConnPara))
		{
			pTransferDevice->m_iInstanceCount--;
			if (pTransferDevice->m_iInstanceCount <=0)
			{
				pTransferDevice->Close();
				delete it->second;
				it->second = NULL;
				m_mTransferDeviceP.erase(it++);
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			++it;
		}
	}
	return false;
}
cTransferDevice* cTransferDevice::GetInstance( int id )
{
	cTransferDevice* tf = cTransferDevice::GetNextDevice();
	
	while (tf)
	{
		if (tf->ID() == id)
		{
			return tf;
		}
		
		tf = cTransferDevice::GetNextDevice(tf);
	}
	return NULL;
}
cTransferDevice* cTransferDevice::GetNextDevice( cTransferDevice* pTransfer )
{
	mTransferDeviceP::iterator it;
	if (!pTransfer)
	{
		it = m_mTransferDeviceP.begin();
		
	}
	else{
		it = m_mTransferDeviceP.find(pTransfer->ID());
		it++;
	}
	if (it != m_mTransferDeviceP.end())
	{
		return it->second;
	}else
	{
		return NULL;
	}
}
void cTransferDevice::SetOpen()
{
	m_Status.SetOpen();
}

int cTransferDevice::CreateID()
{
	return id_all_++;
}

int cTransferDevice::tID()
{
	return id_;
}
void cTransferDevice::GetPara( cConnPara& ConnPara )
{
	ConnPara = m_ConnPara;
}


void cTransferDevice::Init()
{
	Object::Init();
	list_.AddtoList(this);
}

void cTransferDevice::Init( int id )
{
	Object::Init(id);
	list_.AddtoList(this);
}
cTransferDevice* cTransferDevice::Create()
{
	return list_.Create();
}
void cTransferDevice::Code( std::ofstream& of )
{

}

bool cTransferDevice::DeCode( std::string data )
{
	return false;
}

void cTransferDevice::Save( std::string path )
{

}

void cTransferDevice::Load( std::string path )
{

}

cTransferDevice* cTransferDevice::Get( int id )
{
	return list_.Get(id);
}

cTransferDevice* cTransferDevice::GetNext( int id /*= 0*/ )
{
	return list_.GetNext(id);
}

bool cTransferDevice::Open()
{
	return false;
}