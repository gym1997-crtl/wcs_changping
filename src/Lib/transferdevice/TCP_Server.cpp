#include "transferdevice/TCP_Server.h"
#include "comm/Log.h"
#include "comm/Comm.h"

cTCP_Server::cTCP_Server(void)
{

	acceptor_ = NULL;
}

cTCP_Server::~cTCP_Server(void)
{
}

bool cTCP_Server::Open()
{

	Start();
	return true;
}

bool cTCP_Server::Close()
{
	if (acceptor_)
	{
		delete acceptor_;
		acceptor_ = NULL;
	}
// 	if (sock_)
// 	{
// 		delete sock_;
// 		sock_ = NULL;
// 	}
	cTransferDevice::Close();
	return true;
}

void cTCP_Server::Read()
{
// 	if (m_Status.IsOpen())
// 	{
	try {
		p_sock_->async_read_some(buffer(m_szReadTemp,m_bufSize), boost::bind(
			&cTransferDevice::read_callback,(cTransferDevice*)this,
			boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
	} catch (std::exception& e) {
		m_Status.SetClose();
		LOGS("TCP Server") << "Close Connection port = "<< p_sock_->local_endpoint().port();
	}
// 	}
// 	else
// 	{
// 		cout<<"read err"<<endl;
// 	}
	
}

bool cTCP_Server::Write()
{
	try {
		if (!p_sock_->is_open())
			return 0;

		int total = 0;
		
		while (total < m_nWriteBufferSize) {
			int tmpLength = m_nWriteBufferSize - total > m_nWriteBufferSize ? m_nWriteBufferSize : m_nWriteBufferSize - total;

			size_t sz = p_sock_->write_some(buffer(m_szWriteBuffer + total,
				tmpLength));

			total += sz;
			//cout<<"sendData : length  = "<<tmpLength<<endl;
		}
		assert(total == m_nWriteBufferSize);
		//delete[] data;
		return true;
	} catch (std::exception& e) {
		m_Status.SetClose();
		LOGS("TCP Server") << "Close Connection port = "<< p_sock_->local_endpoint().port();
		return false;
	}
}

void cTCP_Server::Start()//�����첽���ӣ����ӷ���ʱAccept_handler������
{
	try
	{
		if (acceptor_)
		{
			delete acceptor_;
			acceptor_ = NULL;
		}


		if (!acceptor_)
		{
			acceptor_ = new ip::tcp::acceptor(m_ios,ip::tcp::endpoint(ip::tcp::v4(),m_ConnPara.n_listen_port));
		}
		
		
		sock_pt s(new ip::tcp::socket(m_ios));
		p_sock_ = s;
		acceptor_->accept(*p_sock_);
		cout<<"client connect"<<endl;
	}
	catch (std::exception &e)
	{
		return;
	}
// 	if ( (p_sock_) && (acceptor_))
// 	{
// 		acceptor_->async_accept(*p_sock_,bind(&cTCP_Server::Accept_handler,this,placeholders::error));
// 	}
	
}
// void cTCP_Server::Accept_handler(const system::error_code& ec)
// {
// 	if (ec) //���������
// 	{
// 		Start(); //�ٴ������첽����
// 		m_Status.SetClose();
// 		return;
// 	}
// 	else
// 	{
// 		
// 		// 	sock_->async_read_some(buffer(m_szReadTemp,m_bufSize), boost::bind(
// 		// 		&cTransferDevice::read_callback,(cTransferDevice*)this,
// 		// 		placeholders::error,placeholders::bytes_transferred));
// 		Read();
// 		m_Status.SetOpen();
// 		
// 		LOGS("TCP Server")<<"client:"<<p_sock_->remote_endpoint().address();
// 		
// 		//Start(); //�ٴ������첽����
// 	}
// 	
// }
//���غ������첽���ӣ���Ҫaccept��Ϊ��Ч
