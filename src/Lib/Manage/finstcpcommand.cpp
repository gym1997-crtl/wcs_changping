/*
 Copyright 2020 <copyright holder> <email>
 *
 */
#include <iostream>
#include "finstcpcommand.h"
#include <boost/array.hpp>
 //#include <boost/enable_shared_from_this.hpp>
finsTcpCommand::finsTcpCommand() :m_socket(0), plc_info(0)
{
	plc_info = 0;
	show_detail = false;
	communicate_response = false;

	m_connection_st = NO_CONNECTION;
	driver_call_id_ = 0;
	m_transmission_st = Transmission_Status::IDLE;
}

finsTcpCommand::~finsTcpCommand()
{
	if (m_socket != NULL) {
		m_socket->cancel();
		m_socket->close();
		delete m_socket;
		m_socket = 0;
		std::cout << " delete m_socket" << std::endl;
	}

	if (plc_info != NULL) {
		memset(plc_info->address, 0, 128);

		delete plc_info;
		plc_info = 0;
		std::cout << " delete plc_info" << std::endl;
	}

	boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(5000000));
}

void finsTcpCommand::init_plc(std::string _ip, int _port, int _remote_net)
{
	m_ip = _ip;
	m_port = _port;
	m_remote_node = _remote_net;

	plc_info = new fins_plc_st;
	memset(plc_info->address, 0, 128);
	memcpy(plc_info->address, m_ip.c_str(), m_ip.length());
	plc_info->port = (uint16_t)m_port;
	plc_info->remote_node = (uint8_t)m_remote_node;
	plc_info->plc_mode = FINS_MODE_CS;
}

bool finsTcpCommand::connect()
{

	try {
		//boost::system::error_code cnterror;
		boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(m_ip), m_port);
		m_socket = new boost::asio::ip::tcp::socket(_ioService);
		m_socket->connect(end_point);

	}
	catch (boost::system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();
		//return e.code().value();
		return false;
	}
	std::cout << "Connect to " << m_ip << " success!" << std::endl;
	return true;;
}

bool finsTcpCommand::shakehand(unsigned char local_node, int&error_no)
{
	unsigned char cmnd[20] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,local_node };

	fins_tcp_write(cmnd, 20);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 24, rec_len);
	std::string message = (char*)rec_buf;

	std::cout << " Client rec len :" << rec_len << "  msg:" << message << std::endl;
	std::cout << " local node :" << (int)rec_buf[19] << " remote_node:" << (int)rec_buf[23] << std::endl;

	plc_info->local_node = rec_buf[19];
	plc_info->remote_node = rec_buf[23];

	bool  shakehandsucc = false;
	if (rec_len == 24 && rec_buf[15] == 0)
	{
		std::cout << "shakehand()   success!" << std::endl;
		shakehandsucc = true;
	}

	else if (rec_len == 24 && rec_buf[15] == 0x21)
	{
		std::cout << "shakehand()   fail! ERROR 0x21 !" << rec_len << std::endl;
		error_no = rec_buf[15];
	}
	else
	{
		std::cout << "shakehand()   fail! len:" << rec_len << " error:" << (int)rec_buf[15] << std::endl;
		error_no = rec_buf[15];
		shakehandsucc = false;
	}

	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;

	return shakehandsucc;

}

void finsTcpCommand::disconnect()
{
	if (m_socket != NULL) {
		m_socket->close();
		delete m_socket;
		m_socket = 0;
		//std::cout << "disconnect() delete m_socket" << std::endl;
	}

	m_connection_st = NO_CONNECTION;
}
///////////
bool finsTcpCommand::asyc_connect()
{
	if (m_socket) {
		std::cout << " m_socket not null !" << std::endl;
		m_socket->cancel();
		m_socket->close();
		delete m_socket;
		m_socket = 0;
		boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(10000));
	}
	//std::cout << "Start  asyc_connect!" << std::endl;
	_ioService.stop();
	_ioService.reset();
	communicate_response = false;
	m_socket = new boost::asio::ip::tcp::socket(_ioService);

	m_socket->async_connect(
		boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(m_ip), m_port),
		boost::bind(&finsTcpCommand::handle_connect, this, boost::asio::placeholders::error));

	boost::asio::deadline_timer timer(_ioService, boost::posix_time::microsec(40000));
	timer.async_wait(boost::bind(&finsTcpCommand::time_out, this));

	//boost::thread  th(&finsTcpCommand::ios_run,this);
	_ioService.run();
	//std::cout << "asyc_connect()  over" << std::endl;
	if (m_connect == -1) {
		std::cout << "asyc_connect()  fail" << std::endl;
		return false;
	}
	else if (m_connect == 1 && m_socket != NULL)
	{
		std::cout << "asyc_connect()  success " << std::endl;

		//unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
		//memset(rec_buf, 0, FINS_CMND_BUF);
		//int rec_len = 0;
		//fins_tcp_read(rec_buf, 24, rec_len);
		//if (rec_len == 24 && rec_buf[15] == 0x21) 
		//{
		//	boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(200000));
		//	bool re_connect =  asyc_connect();
		//	std::cout << " ERROR 0x21  , Reconnect result:"<< re_connect << std::endl;
		//	return re_connect;
		//}

		return true;

	}
}

void finsTcpCommand::time_out()
{
	// std::cout<<"time_out() ,  response :"<<std::endl;

	boost::lock_guard<boost::mutex> lock(res_mutex);
	if (communicate_response)
	{
		//std::cout<<"time_out() ,  response :"<<communicate_response<<std::endl;
	}
	else
	{
		std::cout << "time_out() ,no  response :" << communicate_response << std::endl;
		_ioService.stop();
		_ioService.reset();
		if (m_socket != NULL) {
			m_socket->close();
			std::cout << "try  delete m_socket" << std::endl;
			delete m_socket;
			m_socket = 0;
			std::cout << " delete m_socket" << std::endl;
		}
	}

}

void  finsTcpCommand::handle_connect(const boost::system::error_code &err)
{
	if (err)
	{
		std::cout << "Connect error:" << err.message() << "\n";
		m_connect = -1;
	}
	else
	{
		m_connect = 1;
		//std::cout << "Successful connection\n";
		communicate_response = true;
	}
}


/*
* bool fins_readbit(const char* start,bool* resdata,std::size_t num_bits);
*
* 通过FINS协议从远程PLC的存储区读取一个位块。
*
* 该函数返回 成功或失败。
*
* 传入参数： start :   起始地址的char指针，格式类似“CIO0.1”，
*          resdata:  读取到的bool值指针，
*          num_bits: 需要读取的位数
*/
bool finsTcpCommand::fins_readbit(const char* start, bool* resdata, std::size_t num_bits)
{
	//std::cout<<"request  fins_readbit() "<<std::endl;
	boost::mutex::scoped_lock lock(driver_mu_);
	driver_call_id_++;

	bool ck = verify_transmission();
	if (!ck) {
		std::cout << "fins_readbit()  check_connection error !!!  return " << std::endl;
		return false;
	}

	fins_address_tp address;
	if (finslib_decode_address(start, &address))
		return false;

	const  fins_area_tp *area_ptr;
	area_ptr = finslib_search_area(plc_info, &address, 1, FI_RD, false);
	if (area_ptr == NULL)
		return false;

	short chunk_length = num_bits;
	fins_command_st * fins_sh = new fins_command_st;
	fins_init_command(fins_sh, 6, 0x01, 0x01);
	fins_sh->Frame[12 + 0] = area_ptr->area;
	fins_sh->Frame[12 + 1] = (address.main_address >> 8) & 0xff;
	fins_sh->Frame[12 + 2] = (address.main_address >> 0) & 0xff;
	fins_sh->Frame[12 + 3] = (address.sub_address) & 0xff;
	fins_sh->Frame[12 + 4] = (chunk_length >> 8) & 0xff;
	fins_sh->Frame[12 + 5] = (chunk_length >> 0) & 0xff;
	//    std::cout<<"area:"<<std::hex<<(int)area_ptr->area<<" address:"<<(int)address.main_address
	//    <<" sub:"<<(int)address.sub_address<<" len"<<chunk_length<<std::dec<<std::endl;

	unsigned char *send_buf = new  unsigned char[FINS_CMND_BUF];
	memset(send_buf, 0, FINS_CMND_BUF);
	memcpy(send_buf + 0, fins_sh->Header, 8);
	memcpy(send_buf + 8, fins_sh->command, 4);
	memcpy(send_buf + 12, fins_sh->error_code, 4);
	memcpy(send_buf + 16, fins_sh->Frame, 12 + 6);
	delete[] fins_sh;
	fins_sh = 0;


	fins_tcp_write(send_buf, 34);

	delete[] send_buf;
	send_buf = 0;
	//std::cout << " read bit  pause !" << std::endl;
	//boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(500000));
	//std::cout << " read bit  pause over !" << std::endl;
	//read back 
	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);

	int len = 30 + num_bits;
	int rec_len = 0;
	fins_tcp_read(rec_buf, len, rec_len);
	//std::string message  = (char*)rec_buf;

	//std::cout<<" Client rec len :"<<rec_len<<std::endl;
	bool no_error = false;
	if (rec_len != len)
	{
		std::cout << "  read len error  ,return, rec_len: " << rec_len << " , len" << len << std::endl;
		no_error = false;
	}
	else if (rec_buf[15] != 0) {
		std::cout << "  read data  contain error!!!  ,code: " << (int)rec_buf[15] << std::endl;
		no_error = false;
	}

	else
	{
		no_error = true;
		for (int a = 0; a < chunk_length; a++)
		{
			resdata[a] = rec_buf[30 + a];  // 28 is header len
		}
	}

	delete[] rec_buf;

	if (no_error == false)
		disconnect();
	return no_error;
}

/*
* bool fins_writebit(const char* start, const bool* data,std::size_t num_bits)
*
* 通过FINS协议从远程PLC的存储区写一个位块。
*
* 该函数返回 成功或失败。
*
* 传入参数： start :   起始地址的char指针，格式类似“CIO100.1”，
*          data:     需要写入值到的指针，
*          num_bits: 需要写入的位数
*/
bool finsTcpCommand::fins_writebit(const char* start, const bool* data, std::size_t num_bits)
{
	//std::cout << "request  fins_writebit() " << std::endl;
	boost::mutex::scoped_lock lock(driver_mu_);
	driver_call_id_++;

	bool cands = verify_transmission();
	if (!cands) {
		std::cout << "fins_writebit()  check_connection error !!!  return " << std::endl;
		return false;
	}

	fins_address_tp address;
	if (finslib_decode_address(start, &address)) return false;

	const  fins_area_tp *area_ptr;
	area_ptr = finslib_search_area(plc_info, &address, 1, FI_RD, false);
	if (area_ptr == NULL) return false;

	short chunk_length = num_bits;
	fins_command_st * fins_sh = new fins_command_st;
	fins_init_command(fins_sh, 6 + chunk_length, 0x01, 0x02);
	fins_sh->Frame[12 + 0] = area_ptr->area;
	fins_sh->Frame[12 + 1] = (address.main_address >> 8) & 0xff;
	fins_sh->Frame[12 + 2] = (address.main_address >> 0) & 0xff;
	fins_sh->Frame[12 + 3] = (address.sub_address) & 0xff;
	fins_sh->Frame[12 + 4] = (chunk_length >> 8) & 0xff;
	fins_sh->Frame[12 + 5] = (chunk_length >> 0) & 0xff;

	for (int k = 0; k < chunk_length; k++)
	{
		fins_sh->Frame[18 + k] = data[k];
	}

	//    std::cout<<"area:"<<std::hex<<(int)area_ptr->area<<" address:"<<(int)address.main_address
	//    <<" sub:"<<(int)address.sub_address<<" len"<<chunk_length<<std::endl;

	unsigned char *send_buf = new  unsigned char[FINS_CMND_BUF];
	memset(send_buf, 0, FINS_CMND_BUF);
	memcpy(send_buf + 0, fins_sh->Header, 8);
	memcpy(send_buf + 8, fins_sh->command, 4);
	memcpy(send_buf + 12, fins_sh->error_code, 4);
	memcpy(send_buf + 16, fins_sh->Frame, 18 + chunk_length);
	delete[] fins_sh;
	fins_sh = 0;

	fins_tcp_write(send_buf, 16 + 18 + chunk_length);

	delete[] send_buf;
	send_buf = 0;

	// read back 
	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);

	int len = 30;   //28 + 2Bytes endcode
	int rec_len = 0;
	fins_tcp_read(rec_buf, len, rec_len);

	//   std::cout<<" Client rec len :"<<rec_len<<std::endl;
	bool no_error = false;
	if (rec_len != len)
	{
		std::cout << "  read len error  ,return, rec_len: " << rec_len << " , len" << len << std::endl;
		no_error = false;
	}
	else if (rec_buf[15] != 0) {
		std::cout << "  read data  contain error!!!  ,code: " << (int)rec_buf[15] << std::endl;
		no_error = false;
	}

	else {
		no_error = true;
	}

	//     std::cout<<"msg:"<<std::endl;
	//     for(int j=0;j<rec_len;j++)
	//     {
	//       std::cout<<" "<<std::hex<<(int)rec_buf[j];//<<std::endl;
	//       
	//     } 
	//     std::cout<<std::endl;

	delete[] rec_buf;
	rec_buf = 0;
	if (no_error == false)
		disconnect();
	return no_error;
}

bool finsTcpCommand::fins_readword(const char* start, short* resdata, std::size_t num_bits)
{
	std::cout << "request  fins_readword() " << std::endl;
	boost::mutex::scoped_lock lock(driver_mu_);
	driver_call_id_++;
	std::cout << "start fins_readword() , id:" << driver_call_id_ << std::endl;

	bool ck = verify_transmission();
	if (!ck) {
		std::cout << "fins_readword()  check_connection error !!!  return " << std::endl;
		return false;
	}

	fins_address_tp address;
	if (finslib_decode_address(start, &address))
		return false;

	const  fins_area_tp *area_ptr;
	area_ptr = finslib_search_area(plc_info, &address, 16, FI_RD, false);
	if (area_ptr == NULL)
		return false;

	short chunk_length = num_bits;
	fins_command_st * fins_sh = new fins_command_st;
	fins_init_command(fins_sh, 6, 0x01, 0x01);
	fins_sh->Frame[12 + 0] = area_ptr->area;
	fins_sh->Frame[12 + 1] = (address.main_address >> 8) & 0xff;
	fins_sh->Frame[12 + 2] = (address.main_address >> 0) & 0xff;
	fins_sh->Frame[12 + 3] = (address.sub_address) & 0xff;
	fins_sh->Frame[12 + 4] = (chunk_length >> 8) & 0xff;
	fins_sh->Frame[12 + 5] = (chunk_length >> 0) & 0xff;

	unsigned char *send_buf = new  unsigned char[FINS_CMND_BUF];
	memset(send_buf, 0, FINS_CMND_BUF);
	memcpy(send_buf + 0, fins_sh->Header, 8);
	memcpy(send_buf + 8, fins_sh->command, 4);
	memcpy(send_buf + 12, fins_sh->error_code, 4);
	memcpy(send_buf + 16, fins_sh->Frame, 12 + 6);
	delete[] fins_sh;
	fins_sh = 0;


	fins_tcp_write(send_buf, 34);

	delete[] send_buf;
	send_buf = 0;

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);

	int len = 30 + num_bits * 2;
	int rec_len = 0;
	fins_tcp_read(rec_buf, len, rec_len);
	//std::string message  = (char*)rec_buf;

	//std::cout<<" Client rec len :"<<rec_len<<std::endl;
	bool no_error = false;
	if (rec_len != len)
	{
		std::cout << "  read len error  ,return, rec_len: " << rec_len << " , len" << len << std::endl;
		no_error = false;
	}
	else if (rec_buf[15] != 0) {
		std::cout << "  read data  contain error!!!  ,code: " << (int)rec_buf[15] << std::endl;
		no_error = false;
	}

	else
	{
		no_error = true;
		for (int a = 0; a < chunk_length; a++)
		{
			resdata[a] = 256 * rec_buf[30 + a * 2 + 0] + rec_buf[30 + a * 2 + 1];  // 28 is header len
		}
	}

	delete[] rec_buf;

	if (no_error == false)
		disconnect();
	std::cout << " fins_readword() , id:" << driver_call_id_ << " over!" << std::endl;
	return no_error;

}

bool finsTcpCommand::fins_writeword(const char* start, const short* data, std::size_t num_bits)
{
	std::cout << "request  fins_writeword() " << std::endl;
	boost::mutex::scoped_lock lock(driver_mu_);
	driver_call_id_++;
	std::cout << "start fins_writeword() , id:" << driver_call_id_ << std::endl;

	bool cands = verify_transmission();
	if (!cands) {
		std::cout << "fins_writeword()  check_connection error !!!  return " << std::endl;
		return false;
	}

	fins_address_tp address;
	if (finslib_decode_address(start, &address)) return false;

	const  fins_area_tp *area_ptr;
	area_ptr = finslib_search_area(plc_info, &address, 16, FI_RD, false);
	if (area_ptr == NULL) return false;

	short chunk_length = num_bits;
	fins_command_st * fins_sh = new fins_command_st;
	fins_init_command(fins_sh, 6 + chunk_length * 2, 0x01, 0x02);
	fins_sh->Frame[12 + 0] = area_ptr->area;
	fins_sh->Frame[12 + 1] = (address.main_address >> 8) & 0xff;
	fins_sh->Frame[12 + 2] = (address.main_address >> 0) & 0xff;
	fins_sh->Frame[12 + 3] = (address.sub_address) & 0xff;
	fins_sh->Frame[12 + 4] = (chunk_length >> 8) & 0xff;
	fins_sh->Frame[12 + 5] = (chunk_length >> 0) & 0xff;

	for (int k = 0; k < chunk_length; k++)
	{
		fins_sh->Frame[18 + k * 2 + 0] = (data[k] >> 8) & 0xff;
		fins_sh->Frame[18 + k * 2 + 1] = (data[k] >> 0) & 0xff;
		std::cout << "data[k] :" << data[k] << std::endl;
	}

	unsigned char *send_buf = new  unsigned char[FINS_CMND_BUF];
	memset(send_buf, 0, FINS_CMND_BUF);
	memcpy(send_buf + 0, fins_sh->Header, 8);
	memcpy(send_buf + 8, fins_sh->command, 4);
	memcpy(send_buf + 12, fins_sh->error_code, 4);
	memcpy(send_buf + 16, fins_sh->Frame, 18 + chunk_length * 2);
	delete[] fins_sh;
	fins_sh = 0;

	for (int n = 0; n < 36; n++)
	{
		std::cout << "n:" << n << "  " << (int)send_buf[n] << std::endl;
	}

	fins_tcp_write(send_buf, 16 + 18 + chunk_length * 2);

	delete[] send_buf;
	send_buf = 0;

	// read back 
	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);

	int len = 30;   //28 + 2Bytes endcode
	int rec_len = 0;
	fins_tcp_read(rec_buf, len, rec_len);

	//   std::cout<<" Client rec len :"<<rec_len<<std::endl;
	bool no_error = false;
	if (rec_len != len)
	{
		std::cout << "  read len error  ,return, rec_len: " << rec_len << " , len" << len << std::endl;
		no_error = false;
	}
	else if (rec_buf[15] != 0) {
		std::cout << "  read data  contain error!!!  ,code: " << (int)rec_buf[15] << std::endl;
		no_error = false;
	}

	else {
		no_error = true;
	}

	delete[] rec_buf;
	rec_buf = 0;
	if (no_error == false)
		disconnect();
	std::cout << " fins_writeword() , id:" << driver_call_id_ << " over!" << std::endl;
	return no_error;
}


bool  finsTcpCommand::fins_set_run()
{
	//bool cands = connect_and_shakehand();
	//if (!cands)
	//	return false;

	unsigned char cmnd[28] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
	0x80,0x00,0x02,0x00,plc_info->remote_node,0x00,0x00,plc_info->local_node,0x00,0x00,0x04,0x01 };
	fins_tcp_write(cmnd, 28);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 30, rec_len);
	std::string message = (char*)rec_buf;

	std::cout << " Client rec len :" << rec_len << "  msg:" << message << std::endl;
	//std::cout << " local node :" << (int)rec_buf[19] << " remote_node:" << (int)rec_buf[23] << std::endl;

	bool  setrun_succ = false;
	if (rec_len == 30 && rec_buf[15] == 0)
	{
		std::cout << "fins_set_run()   success!" << std::endl;
		setrun_succ = true;
	}

	else if (rec_len != 30)
	{
		std::cout << "setrun()  fail!  , rec len error !" << std::endl;
		setrun_succ = false;
	}
	else if (rec_buf[15] != 0)
	{
		std::cout << "setrun()  fail! error code :" << (int)rec_buf[15] << std::endl;
		setrun_succ = false;
	}

	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;

	return setrun_succ;
}

bool  finsTcpCommand::fins_set_stop()
{
	//bool cands = connect_and_shakehand();
	//if (!cands)
	//	return false;

	unsigned char cmnd[28] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
	0x80,0x00,0x02,0x00,plc_info->remote_node,0x00,0x00,plc_info->local_node,0x00,0x00,0x04,0x02 };
	fins_tcp_write(cmnd, 28);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 30, rec_len);
	std::string message = (char*)rec_buf;

	std::cout << " Client rec len :" << rec_len << "  msg:" << message << std::endl;
	//std::cout << " local node :" << (int)rec_buf[19] << " remote_node:" << (int)rec_buf[23] << std::endl;

	bool  setstop_succ = false;
	if (rec_len == 30 && rec_buf[15] == 0)
	{
		std::cout << "fins_set_stop()   success!" << std::endl;
		setstop_succ = true;
	}

	else if (rec_len != 30)
	{
		std::cout << "setstop()  fail!  , rec len error !" << std::endl;
		setstop_succ = false;
	}
	else if (rec_buf[15] != 0)
	{
		std::cout << "setstop()  fail! error code :" << (int)rec_buf[15] << std::endl;
		setstop_succ = false;
	}

	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;

	return setstop_succ;
}

bool  finsTcpCommand::fins_reset_ethernet()
{
	//bool cands = connect_and_shakehand();
	//if (!cands)
	//	return false;
	////
	unsigned char cmnd[28] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
0x80,0x00,0x02,0x00,plc_info->remote_node,0xFA,0x00,plc_info->local_node,0x00,0x00,0x04,0x03 };
	fins_tcp_write(cmnd, 28);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 30, rec_len);
	std::string message = (char*)rec_buf;

	std::cout << " Client rec len :" << rec_len << "  msg:" << message << std::endl;
	//std::cout << " local node :" << (int)rec_buf[19] << " remote_node:" << (int)rec_buf[23] << std::endl;

	bool  reset_eth_succ = false;
	if (rec_len == 0) {
		std::cout << "fins_reset_ethernet()   success!" << std::endl;
		reset_eth_succ = true;
	}
	else if (rec_len != 0)
	{
		std::cout << "fins_set_ethernet()   fail, error code :" << (int)rec_buf[15] << std::endl;
		reset_eth_succ = true;
	}


	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;

	return reset_eth_succ;
}

bool  finsTcpCommand::fins_read_ethernet_state()
{
	bool cands = connect_and_shakehand();
	if (!cands)
		return false;
	////

	unsigned char cmnd[28] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
	0x80,0x00,0x02,0x00,plc_info->remote_node,0xFA,0x00,plc_info->local_node,0x00,0x00,0x05,0x01 };
	fins_tcp_write(cmnd, 28);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 88, rec_len);
	std::string message = (char*)rec_buf;

	std::cout << " Client rec len :" << rec_len << "  msg:" << message << std::endl;
	//std::cout << " local node :" << (int)rec_buf[19] << " remote_node:" << (int)rec_buf[23] << std::endl;

	bool  read_ethernet_state_succ = false;
	if (rec_len == 88 && rec_buf[15] == 0)
	{
		std::cout << "fins_read_ethernet_state()   success!" << std::endl;
		read_ethernet_state_succ = true;
	}

	else if (rec_len != 88)
	{
		std::cout << "setrun()  fail!  , rec len error !" << std::endl;
		read_ethernet_state_succ = false;
	}
	else if (rec_buf[15] != 0)
	{
		std::cout << "setrun()  fail! error code :" << (int)rec_buf[15] << std::endl;
		read_ethernet_state_succ = false;
	}

	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;

	return read_ethernet_state_succ;
}

bool  finsTcpCommand::fins_read_connect_state(unsigned char conn)
{
	bool cands = connect_and_shakehand();
	if (!cands)
		return false;
	////
	unsigned char connection_point = 0x01;
	unsigned char cmnd[30] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x16,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
		0x80,0x00,0x02,0x00,plc_info->remote_node,0x00,0x00,plc_info->local_node,0x00,0x00,0x27,0x31,0x00,conn };
	fins_tcp_write(cmnd, 30);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 48, rec_len);
	std::string message = (char*)rec_buf;

	std::cout << " Client rec len :" << rec_len << "  msg:" << message << std::endl;
	//std::cout << " local node :" << (int)rec_buf[19] << " remote_node:" << (int)rec_buf[23] << std::endl;

	bool  read_connect_state_succ = false;
	if (rec_len == 48 && rec_buf[15] == 0)
	{
		std::cout << "read_connect_state_succ()   success, current state:" << (int)rec_buf[47] << std::endl;
		read_connect_state_succ = true;
	}

	else if (rec_len != 38)
	{
		std::cout << "read_connect_state_succ()  fail!  , rec len error !" << std::endl;
		read_connect_state_succ = false;
	}
	else if (rec_buf[15] != 0)
	{
		std::cout << "read_connect_state_succ()  fail! error code :" << (int)rec_buf[15] << std::endl;
		read_connect_state_succ = false;
	}

	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;

	return read_connect_state_succ;
}

void finsTcpCommand::get_plc_info(fins_plc_st* plc_struct)
{
	//plc_struct = plc_info;
	memcpy(plc_struct, plc_info, sizeof(fins_plc_st));
	//std::cout << " plc_info local node:" << (int)plc_info->local_node << std::endl;
}

void finsTcpCommand::fins_init_command(fins_command_st * fins_cmnd, int arealen, uint8_t mrc, uint8_t src)
{

	fins_cmnd->Header[0] = 0x46;   // 'F'
	fins_cmnd->Header[1] = 0x49;   // 'I'
	fins_cmnd->Header[2] = 0x4E;   // 'N'
	fins_cmnd->Header[3] = 0x53;   // 'S' 

	// FINS Header(8) + FINS Frame header(12) + arealen(6+num)
	int body_len = 8 + 12 + arealen;
	fins_cmnd->Header[4] = (body_len >> 24) & 0xff;
	fins_cmnd->Header[5] = (body_len >> 16) & 0xff;
	fins_cmnd->Header[6] = (body_len >> 8) & 0xff;
	fins_cmnd->Header[7] = (body_len) & 0xff;

	fins_cmnd->command[0] = 0x00;
	fins_cmnd->command[1] = 0x00;
	fins_cmnd->command[2] = 0x00;
	fins_cmnd->command[3] = 0x02;    // 2

	fins_cmnd->error_code[0] = 0x00;
	fins_cmnd->error_code[1] = 0x00;
	fins_cmnd->error_code[2] = 0x00;
	fins_cmnd->error_code[3] = 0x00;    // err 

	fins_cmnd->Frame[FINS_ICF] = 0x80;  // frame header total 12Bytes
	fins_cmnd->Frame[FINS_RSV] = 0x00;
	fins_cmnd->Frame[FINS_GCT] = 0x02;
	fins_cmnd->Frame[FINS_DNA] = 0x00;
	fins_cmnd->Frame[FINS_DA1] = plc_info->remote_node;
	fins_cmnd->Frame[FINS_DA2] = 0x00;
	fins_cmnd->Frame[FINS_SNA] = 0x00;
	fins_cmnd->Frame[FINS_SA1] = plc_info->local_node;
	fins_cmnd->Frame[FINS_SA2] = 0x00;
	fins_cmnd->Frame[FINS_SID] = 0x00;
	fins_cmnd->Frame[FINS_MRC] = mrc;   // 
	fins_cmnd->Frame[FINS_SRC] = src;   // 

}


void finsTcpCommand::fins_tcp_write(unsigned char* buf, int write_len)
{
	//std::cout<<"fins_tcp_write() begin "<<std::endl;

	if (m_socket == NULL) {
		std::cout << "m_socket == NULL  ,fins_tcp_write()  fail" << std::endl;
		return;
	}

	if (m_socket->is_open() == false) {
		std::cout << "m_socket is_open == false  ,fins_tcp_write()  fail" << std::endl;
		return;
	}

	_ioService.stop();
	_ioService.reset();
	//std::size_t  wrlen =    m_socket->write_some(boost::asio::buffer(buf,send_len));
	communicate_response = false;
	m_byte_write = 0;
	boost::asio::deadline_timer timer(_ioService, boost::posix_time::microsec(40000));
	timer.async_wait(boost::bind(&finsTcpCommand::time_out, this));

	boost::asio::async_write(*m_socket, boost::asio::buffer(buf, write_len),
		boost::bind(&finsTcpCommand::handle_tcp_write, this,
			boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred
		));

	_ioService.run();

	if (m_byte_write == write_len) {
		//std::cout<<"fins_tcp write success ,"<<std::endl;
	}
	else {
		std::cout << "fins_tcp write fail ," << std::endl;
	}

}

void finsTcpCommand::fins_tcp_read(unsigned char* buf, int len, int& rec_len)
{
	if (m_socket == NULL) {
		std::cout << "m_socket == NULL  ,fins_tcp_read()  fail" << std::endl;
		return;
	}

	if (m_socket->is_open() == false) {
		std::cout << "m_socket is_open == false  ,fins_tcp_read()  fail" << std::endl;
		return;
	}
	/*
		boost::array<unsigned char, 128> recbuf;
		boost::system::error_code error;
		if(m_socket->is_open()){
		  std::cout<<"fins_tcp_read()  ::, "<<m_socket->is_open()<<std::endl;
		}

		std::size_t readlen = m_socket->read_some(boost::asio::buffer(recbuf), error);
		// 打印客户端发来的数据
		std::cout << "client receive, reclen:"<<readlen<<" bufsize:"<<recbuf.size() <<",content:" << recbuf.data() << std::endl;
	*/
	//boost::array<unsigned char, FINS_CMND_BUF> recbuf;
   //std::cout<<"fins_tcp_read()  begin."<<std::endl;
	_ioService.stop();
	_ioService.reset();
	communicate_response = false;
	m_byte_read = 0;

	boost::asio::deadline_timer timer(_ioService, boost::posix_time::microsec(40000));
	timer.async_wait(boost::bind(&finsTcpCommand::time_out, this));

	boost::asio::async_read(*m_socket, boost::asio::buffer(buf, len),
		boost::bind(&finsTcpCommand::handle_tcp_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		));

	_ioService.run();

	if (m_byte_read == len) {
		//std::cout<<"fins_tcp read success ,read len:"<<m_byte_read<<std::endl;
	}
	else {
		std::cout << "fins_tcp read fail ," << std::endl;
	}

	rec_len = m_byte_read;
	//memcpy(buf,recbuf.data(),rec_len);

}

void finsTcpCommand::handle_tcp_read(const boost::system::error_code& _error, std::size_t byte_trans)
{
	//std::cout<<"call handle_read() ,byte_trans:"<<byte_trans<<std::endl;
	m_byte_read = byte_trans;
	boost::lock_guard<boost::mutex> lock(res_mutex);
	communicate_response = true;
}

void finsTcpCommand::handle_tcp_write(const boost::system::error_code& _error, std::size_t byte_trans)//const boost::system::error_code& _error
{
	//std::cout<<"call handle_write() ,byte_trans:"<<byte_trans<<std::endl;
	m_byte_write = byte_trans;
	boost::lock_guard<boost::mutex> lock(res_mutex);
	communicate_response = true;
}

bool finsTcpCommand::finslib_decode_address(const char *str, fins_address_tp *address)
{
	//std::cout<<"call fnc ,finslib_decode_address()!"<<std::endl;
	size_t num_char;
	uint32_t main_address;
	uint32_t sub_address;
	char name[4];
	const char *ptr;

	if (str == NULL || address == NULL) return true;

	num_char = 0;
	ptr = str;
	main_address = 0;
	sub_address = 0;

	while (isspace(*ptr)) ptr++;

	while (isalpha(*ptr) && num_char < 3) {

		name[num_char] = (char)toupper(*ptr);
		num_char++;
		ptr++;
	}
	if (isalpha(*ptr)) return true;

	while (num_char < 4) name[num_char++] = 0;

	while (isspace(*ptr)) ptr++;
	if (!isdigit(*ptr)) return true;

	while (isdigit(*ptr)) {

		main_address *= 10;
		main_address += *ptr - '0';
		ptr++;
		//std::cout<<"main_address:"<<main_address<<std::endl;
	}

	if (*ptr == '.') {

		ptr++;
		while (isdigit(*ptr)) {

			sub_address *= 10;
			sub_address += *ptr - '0';
			ptr++;
		}

		if (sub_address > 15) return true;
	}

	while (isdigit(*ptr)) ptr++;

	if (*ptr) return true;

	address->name[0] = name[0];
	address->name[1] = name[1];
	address->name[2] = name[2];
	address->name[3] = name[3];

	address->main_address = main_address;
	address->sub_address = sub_address;
	//	std::cout<<"after  decode ,name :"<<address->name<<" address , main = "<< main_address<<" sub ="<<sub_address<<std::endl;

	return false;

}

bool finsTcpCommand::test_communicate()
{
	//   bool readdata[8] = {0};
	//   fins_readbit("cio1.01",readdata,2,3000);
	if (!plc_info)
	{
		return false;
	}
	unsigned char test_cmnd[34] = { 0x46,0x49,0x4E,0x53,0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0x02,
	0x00 ,0x00 ,0x00 ,0x00 ,0x80 ,0x00 ,0x02 ,0x00 ,
	0x14,0x00,0x00,0xCE,0x00,0x00,0x01,0x01,0x30,0x00,0x00,0x00,0x00,0x02 };
	test_cmnd[20] = plc_info->remote_node;
	test_cmnd[23] = plc_info->local_node;

	fins_tcp_write(test_cmnd, 34);

	unsigned char *rec_buf = new  unsigned char[FINS_CMND_BUF];
	memset(rec_buf, 0, FINS_CMND_BUF);
	int rec_len = 0;
	fins_tcp_read(rec_buf, 32, rec_len);

	//std::string message  = (char*)rec_buf;
	//std::cout<<" Client rec len :"<<rec_len<<"  msg:"<<message<<std::endl;
	//std::cout<<" local node :"<<(int)rec_buf[19]<<" remote_node:"<<(int)rec_buf[23]<<std::endl;

	//plc_info->local_node = rec_buf[19];
	//plc_info->remote_node = rec_buf[23];

	bool noerror = true;
	if (rec_len == 32 && rec_buf[15] == 0)
	{
		//std::cout<<"test_communicate()   success!"<<std::endl;
		noerror = true;
	}
	else {
		std::cout << "test_communicate()   fail!" << std::endl;
		noerror = false;
	}

	memset(rec_buf, 0, FINS_CMND_BUF);
	delete[] rec_buf;
	rec_buf = NULL;
	return noerror;
}


const  fins_area_tp * finsTcpCommand::finslib_search_area(fins_plc_st *sys, const  fins_address_tp *address,
	int bits, uint32_t accs, bool force)
{

	// 	if(show_detail)
	// 	{
	// 	      std::cout<<"call fnc ,finslib_search_area()!"<<std::endl;
	// 	      std::cout<<"bits :"<<bits<<" accs:"<<accs<<"  force:"<<force<<std::endl;
	// 	      std::cout<<" sys->plc_mode:"<< sys->plc_mode<<" main add:"<<address->main_address<<std::endl;
	// 	      std::cout<<" address->name:["<<address->name<<"]"<<std::endl;;
	// 	}

	int a = 0;
	while (fins_area[a].plc_mode != FINS_MODE_UNKNOWN) {

		if (fins_area[a].plc_mode != sys->plc_mode) { a++; continue; }
		if (fins_area[a].bits != bits) { a++; continue; }
		if ((fins_area[a].access | accs) == 0x00000000) { a++; continue; }
		if (fins_area[a].force != force) { a++; continue; }
		if (fins_area[a].low_id > address->main_address) { a++; continue; }
		if (fins_area[a].high_id < address->main_address) { a++; continue; }
		if (strcmp(fins_area[a].name, address->name)) { a++; continue; }

		break;
	}

	if (show_detail)
	{
		std::cout << "** Area  , a:" << a << std::endl;
		std::cout << " plc_mode:" << fins_area[a].plc_mode << std::endl;
		std::cout << "name :" << (fins_area[a].name) << std::endl;
		std::cout << "bits:" << fins_area[a].bits << std::endl;
		std::cout << "length:" << fins_area[a].length << std::endl;
		std::cout << "area:" << (int)fins_area[a].area << std::endl;
		std::cout << "low_id:" << fins_area[a].low_id << std::endl;
		std::cout << "high_id:" << fins_area[a].high_id << std::endl;
		std::cout << "low_addr:" << fins_area[a].low_addr << std::endl;
		std::cout << "high_addr:" << fins_area[a].high_addr << std::endl;
		std::cout << "access:" << fins_area[a].access << std::endl;
		std::cout << "force:" << fins_area[a].force << "    ** " << std::endl;
	}


	if (fins_area[a].plc_mode == FINS_MODE_UNKNOWN) return NULL;

	return &fins_area[a];
}

bool finsTcpCommand::check_connection()
{
	int check_cnt = 3;
	for (; check_cnt > 0; check_cnt--)
	{
		switch (m_connection_st)
		{
		case  NO_CONNECTION:
		{
			bool conn = asyc_connect();
			if (conn)
			{
				int error_no = 0;
				bool sk = shakehand(0xD2, error_no);
				if (sk)
					m_connection_st = LONG_CONNECTED;
				else
				{
					disconnect();
					m_connection_st = FAIL_CONNECTION;
				}
			}
			else
			{
				m_connection_st = FAIL_CONNECTION;
			}
			break;
		}
		case  LONG_CONNECTED:
		{
			bool tst = test_communicate();
			if (tst)
			{
				return true;
			}
			else
			{
				m_connection_st = RE_CONNECTION;
			}

			break;
		}
		case  RE_CONNECTION:
		{
			bool conn = asyc_connect();
			if (conn)
			{
				m_connection_st = LONG_CONNECTED;
			}
			else
			{
				m_connection_st = FAIL_CONNECTION;
			}

			break;
		}
		case  FAIL_CONNECTION:
		{
			m_connection_st = NO_CONNECTION;
			return false;
			break;
		}
		}

	}

}

bool finsTcpCommand::connect_and_shakehand()
{
	if (m_connection_st == LONG_CONNECTED)
		return true;


	// 1st  connect 
	bool asyc_conn = asyc_connect();

	if (false == asyc_conn)
		return false;

	int error_no = 0;
	bool sk = shakehand(LOCAL_NODE, error_no);;

	if (sk) {
		m_connection_st = LONG_CONNECTED;
		return true;
	}


	std::cout << "first error no :" << error_no << std::endl;
	//same node retry 
	if (error_no == 0x21 || error_no == 0x20)
	{
		int try_time = 8;
		if (error_no == 0x21) {
			boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(500000));
			try_time = 2;
		}


		for (int i = 0; i < try_time; i++)
		{
			bool conn = asyc_connect();
			boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(500000));
			disconnect();
			boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(1000000));
		}
	}
	// 2.   connect again
	bool conn2 = asyc_connect();
	if (false == conn2)
		return false;

	int error_no_again = 0;
	bool sk2 = shakehand(LOCAL_NODE, error_no_again);;
	std::cout << " CONNN sk2 == " << sk2 << std::endl;
	if (sk2) {
		return true;
	}
	std::cout << " try all time ,fail !!!" << std::endl;
	return  false;
}

bool  finsTcpCommand::verify_transmission()
{
	bool verify_result = false;
	for (int i = 0; i < 5; i++)
	{
		switch (m_transmission_st)
		{
		case Transmission_Status::IDLE:
		{
			// 1st  connect 
			bool asyc_conn = asyc_connect();

			if (true == asyc_conn)
			{
				int error_no = 0;
				bool sk = shakehand(LOCAL_NODE, error_no);;

				if (sk)
				{
					if (plc_info->local_node == 0x0A || plc_info->local_node == 0x0B) // 连接点正确，才认为传输正常
						m_transmission_st = Transmission_Status::LONG_CONNECT;
					else
						m_transmission_st = Transmission_Status::RESET_ETHERNET;
				}
				else
				{
					//if(error_no == 0x21)

				}

			}
			break;
		}
		case Transmission_Status::LONG_CONNECT:
		{
			bool test_res = test_communicate();
			if (test_res)
				return true;
			else
				m_transmission_st = Transmission_Status::IDLE;
			break;
		}
		case Transmission_Status::RESET_ETHERNET:
		{
			std::cout << "Now Begin Reset PLC Ethernet Unit !" << std::endl;
			if (fins_set_stop())
				std::cout << "SET STOP PLC SUCCESS!" << std::endl;
			else {
				m_transmission_st = Transmission_Status::IDLE;
				std::cout << "SET STOP PLC FAIL!" << std::endl;
			}



			if (fins_reset_ethernet()) {
				std::cout << " Reset PLC PLC SUCCESS!" << std::endl;
				m_transmission_st = Transmission_Status::REVERT_PLC;
			}
			else
			{
				std::cout << " Reset PLC PLC FAIL!" << std::endl;
				m_transmission_st = Transmission_Status::IDLE;
			}
			break;
		}

		case Transmission_Status::REVERT_PLC:
		{
			std::cout << "Now Begin REVERT_PLC  !" << std::endl;
			boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(6000000));

			// 1st  connect 
			bool asyc_conn = asyc_connect();

			if (true == asyc_conn)
			{
				int error_no = 0;
				bool sk = shakehand(LOCAL_NODE, error_no);;

				if (sk)
				{
					if (plc_info->local_node == 0x0A || plc_info->local_node == 0x0B) // 连接点正确，才认为传输正常
					{
						if (fins_set_run())
						{
							std::cout << "SET RUN PLC SUCCESS!" << std::endl;
							m_transmission_st = Transmission_Status::LONG_CONNECT;
						}
						else
							std::cout << "SET STRUNOP PLC FAIL!" << std::endl;
					}
					else
						m_transmission_st = Transmission_Status::RESET_ETHERNET;
				}
				else
				{
					//等待1s 
					boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(1000000));
				}
			}
			else //无法连接
			{
				boost::thread::sleep(boost::get_system_time() + boost::posix_time::microsec(1000000));
			}


			break;
		}
		case Transmission_Status::FAIL_CONNECT:
		{
			break;
		}
		}

	}
	return verify_result;
}

