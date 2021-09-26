/*
 * Copyright 2020 <copyright holder> <email>
 *
 *
 */

#ifndef FINSTCPCOMMAND_H
#define FINSTCPCOMMAND_H
#ifndef Q_MOC_RUN
#include <boost/asio.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/serialization/singleton.hpp> 
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>  
#include <boost/date_time/posix_time/posix_time_types.hpp> 
#endif
#include "fins_structure.h"

#define LOCAL_NODE  0 // 200

typedef  boost::asio::ip::tcp::socket  boost_socket;

class finsTcpCommand
{
	typedef enum
	{
		NO_CONNECTION = 1,
		LONG_CONNECTED = 2,
		RE_CONNECTION = 3,
		FAIL_CONNECTION = 4,

	}Connection_Status;

	typedef enum
	{
		IDLE = 0,
		LONG_CONNECT = 2,
		RESET_ETHERNET = 3,
		REVERT_PLC = 4,
		FAIL_CONNECT = 5

	}Transmission_Status;

	typedef enum
	{
		FirstPoint = 0x0A,
		SecondPoint = 0x0B,
		ThirdPoint = 0x0C,

	}Connection_Point;

public:
	finsTcpCommand();
	~finsTcpCommand();

	void init_plc(std::string ip, int port, int remote_port);

	bool connect();
	bool shakehand(uint8_t local_node, int&error_no);

	bool fins_readbit(const char* start, bool* resdata, std::size_t num_bits);
	bool fins_writebit(const char* start, const bool* data, std::size_t num_bits);

	bool fins_readword(const char* start, short* resdata, std::size_t num_bits);
	bool fins_writeword(const char* start, const short* data, std::size_t num_bits);

	void disconnect();
	bool asyc_connect();

	bool connect_and_shakehand();

	bool  fins_set_run();
	bool  fins_set_stop();
	bool  fins_reset_ethernet();
	bool  fins_read_ethernet_state();
	bool  fins_read_connect_state(unsigned char conn);
	void  get_plc_info(fins_plc_st* plc_struct);
	bool  verify_transmission();
private:
	void fins_cpu_data_read(fins_plc_st *  plc_info);
	void fins_init_command(fins_command_st * fins_cmd, int arealen, uint8_t mrc, uint8_t src);

	void fins_tcp_write(unsigned char* buf, int send_len);
	void fins_tcp_read(unsigned char* buf, int len, int& rec_len);

	bool finslib_decode_address(const char *str, fins_address_tp *address);
	const  fins_area_tp * finslib_search_area(fins_plc_st *sys, const  fins_address_tp *address,
		int bits, uint32_t accs, bool force);

	bool test_communicate();
	bool check_connection();
private: //socket time out related
	void time_out();
	void  handle_connect(const boost::system::error_code &err);
	void handle_tcp_write(const boost::system::error_code&, std::size_t);
	void handle_tcp_read(const boost::system::error_code&, std::size_t);
private:
	std::string m_ip;
	int       m_port;
	int    m_remote_node;

	int m_connect;
	int m_byte_write;
	int m_byte_read;

	fins_plc_st *  plc_info;

	boost_socket * m_socket;
	boost::asio::io_service _ioService;

	boost::mutex res_mutex;
	bool  communicate_response;

	bool show_detail;

	Connection_Status  m_connection_st;
	Transmission_Status m_transmission_st;
	boost::mutex driver_mu_;
	unsigned int driver_call_id_;
};


class multiPLC
{
public:
	multiPLC()
	{
		PLC_driver_map.clear();
	}
	~multiPLC()
	{
		std::map<std::string, finsTcpCommand* >::iterator it_map = PLC_driver_map.begin();
		for (; it_map != PLC_driver_map.end(); it_map++)
		{
			finsTcpCommand* driver_ = it_map->second;
			driver_->disconnect();
			delete driver_;
			driver_ = NULL;
		}
	}

	finsTcpCommand* init_plc(std::string ip, int port, int remote_port)
	{
		std::map<std::string, finsTcpCommand* >::iterator it_map = PLC_driver_map.find(ip);

		if (it_map == PLC_driver_map.end())
		{
			finsTcpCommand* driver_new = new finsTcpCommand();
			driver_new->init_plc(ip, port, remote_port);
			PLC_driver_map[ip] = driver_new;
			std::cout << "Create  plc driver" << ip << " Done!" << std::endl;
			return driver_new;
		}
		else
		{
			std::cout << " plc driver" << ip << " has exist .!" << std::endl;
			return it_map->second;
		}
	}
private:
	std::map<std::string, finsTcpCommand* >  PLC_driver_map;

};

typedef boost::serialization::singleton<multiPLC> Singleton_MultiPLC;
#define MULTIPLC_MANAGE Singleton_MultiPLC::get_mutable_instance() 

#endif // FINSTCPCOMMAND_H
