#ifndef FINS_STRUCTURE_H
#define FINS_STRUCTURE_H

#define WIN32_LEAN_AND_MEAN
#include <vector>
#include <stdint.h>


/********************************************************/
/*							*/
#define FINS_ICF				0			/* Information Control Field				*/
#define FINS_RSV				1			/* Reserved						*/
#define FINS_GCT				2			/* Gateway Counter. Init op 0x07 naar CPU v2.0 of 0x02	*/
#define FINS_DNA				3			/* Destination Network Address (0..127) 0 = lokaal	*/
#define FINS_DA1				4			/* Destination Node Address (0..254) 0 = lokaal		*/
#define FINS_DA2				5			/* Destination Unit Address (0..31) 0 = CPU unit	*/
#define FINS_SNA				6			/* Source Network Address (0..127) 0 = lokaal		*/
#define FINS_SA1				7			/* Source Node Address (0..254) 0 = intern in PLC	*/
#define FINS_SA2				8			/* Source Unit Address (0..31) 0 = CPU unit		*/
#define FINS_SID				9			/* Service ID, uniek nummer 0..FF per commando		*/
#define FINS_MRC				10			/* Main Request Code					*/
#define FINS_SRC				11			/* Sub Request Code					*/
/*							*/
/********************************************************/
#define FINS_MRES				0
#define FINS_SRES				1
/********************************************************/

#define FINS_PORT_MIN				0
#define FINS_PORT_RESERVED			1024
#define FINS_PORT_MAX				65535

#define FINS_TIMEOUT				60

#define FINS_DEFAULT_PORT			9600			/* Default port for FINS TCP and UDP communications	*/

/********************************************************/
/*							*/
#define FINS_MODE_UNKNOWN			0			/* PLC communication mode unknown			*/
#define FINS_MODE_CV				1			/* PLC communicates like a CV PLC			*/
#define FINS_MODE_CS				2			/* PLC communicates like a CS/CJ/CP PLC		*/	

#define FI_RD					0x01
#define FI_WR					0x02
#define FI_FILL					0x04
#define FI_MRD					0x08
#define FI_TRS					0x10
#define FI_TRD					0x20
#define FI_FRC					0x40


/*							*/
#define FINS_HEADER_LEN				8			/* Length of a FINS header				*/
#define FINS_FRAME_LEN				2020			/* Maximum length of a FINS body			*/
#define FINS_MAX_TCP_HEADER			32			/* Maximum length of a FINS/TCP header			*/
/*							*/

#define FINS_CMND_BUF  2048

/********************************************************/
typedef struct _Sfins_command_st
{
    unsigned char Header[FINS_HEADER_LEN];
    unsigned char command[4];
    unsigned char error_code[4];
    unsigned char Frame[FINS_FRAME_LEN];
}fins_command_st;

typedef struct _Sfins_plc_st
{
    char address[128];
    uint16_t port;
    uint8_t local_net;
    uint8_t local_node;
    uint8_t local_unit;
    uint8_t remote_net;
    uint8_t remote_node;
    uint8_t remote_unit;
    uint8_t sid;
    uint8_t comm_type;
//  char model[21];
//  char version[21];
    int plc_mode;
}fins_plc_st;	


typedef struct _Sfins_address_tp
{
	char name[4];
	uint32_t main_address;
	uint32_t sub_address;
}fins_address_tp;

typedef struct _Sfins_chunk_info
{
	char name[4];   //eg. CIO  DM ...
	uint8_t area;  
	uint32_t main_address;
	uint32_t sub_address;
	uint16_t length;
}fins_chunk_info; // PLC区块信息

typedef struct _Sfins_area_tp
{
	/*							*/
	int plc_mode; /* CS/CJ or CV mode communication			*/
	const char* name; /* Text string with the area short code			*/
	int bits; /* Number of bits in the data				*/
	int length; /* Number of bytes per element				*/
	uint8_t area; /* Area code						*/
	uint32_t low_id; /* Lowest identificator					*/
	uint32_t high_id; /* Highest identificator				*/
	uint32_t low_addr; /* Lowest memory address				*/
	uint32_t high_addr; /* Highest memory address				*/
	int32_t access; /* Read or Read/Write access				*/
	bool force; /* Force status used 					*/
}fins_area_tp; /*							*/

//PLC区域地址
static const  fins_area_tp fins_area[] = 
{
	/* plc_mode     name,  bits, length, area, low_id, high_id, low_addr, high_addr, access,                                                      force */
	{ FINS_MODE_CS, "CIO", 1,    1,      0x30,      0,    6143, 0x000000, 0x17FF0F,  FI_RD | FI_WR | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CS, "CIO", 1,    1,      0x70,      0,    6143, 0x000000, 0x17FF0F,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "CIO", 16,   2,      0xB0,      0,    6143, 0x000000, 0x17FF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "CIO", 16,   4,      0xF0,      0,    6143, 0x000000, 0x17FF00,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "W",   1,    1,      0x31,      0,     511, 0x000000, 0x01FF0F,  FI_RD | FI_WR | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CS, "W",   1,    1,      0x71,      0,     511, 0x000000, 0x01FF0F,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "W",   16,   2,      0xB1,      0,     511, 0x000000, 0x01FF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "W",   16,   4,      0xF1,      0,     511, 0x000000, 0x01FF00,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "H",   1,    1,      0x32,      0,     511, 0x000000, 0x01FF0F,  FI_RD | FI_WR | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CS, "H",   1,    1,      0x72,      0,     511, 0x000000, 0x01FF0F,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "H",   16,   2,      0xB2,      0,     511, 0x000000, 0x01FF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "H",   16,   4,      0xF2,      0,     511, 0x000000, 0x01FF00,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "A",   1,    1,      0x33,      0,     959, 0x000000, 0x03BF0F,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "A",   1,    1,      0x33,    448,     959, 0x01C000, 0x03BF0F,          FI_WR,                                               false },
	{ FINS_MODE_CS, "A",   16,   2,      0xB3,      0,     959, 0x000000, 0x03BF00,  FI_RD | FI_MRD | FI_TRS,                   false },
	{ FINS_MODE_CS, "A",   16,   2,      0xB3,    448,     959, 0x01C000, 0x03BF00,          FI_WR | FI_FILL | FI_TRD,          false },
	{ FINS_MODE_CS, "TIM", 1,    1,      0x09,      0,    4095, 0x000000, 0x0FFF00,  FI_RD | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CS, "TIM", 1,    1,      0x49,      0,    4095, 0x000000, 0x0FFF00,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "TIM", 16,   2,      0x89,      0,    4095, 0x000000, 0x0FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "CNT", 1,    1,      0x09,      0,    4095, 0x800000, 0x8FFF00,  FI_RD | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CS, "CNT", 1,    1,      0x49,      0,    4095, 0x800000, 0x8FFF00,                            FI_MRD,                            true },
	{ FINS_MODE_CS, "CNT", 16,   2,      0x89,      0,    4095, 0x800000, 0x8FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "DM",  1,    1,      0x02,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "DM",  16,   2,      0x82,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E0_", 1,    1,      0x20,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E1_", 1,    1,      0x21,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E2_", 1,    1,      0x22,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E3_", 1,    1,      0x23,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E4_", 1,    1,      0x24,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E5_", 1,    1,      0x25,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E6_", 1,    1,      0x26,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E7_", 1,    1,      0x27,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E8_", 1,    1,      0x28,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E9_", 1,    1,      0x29,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "EA_", 1,    1,      0x2A,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "EB_", 1,    1,      0x2B,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "EC_", 1,    1,      0x2C,      0,   32767, 0x000000, 0x7FFF0F,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "E0_", 16,   2,      0xA0,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E1_", 16,   2,      0xA1,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E2_", 16,   2,      0xA2,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E3_", 16,   2,      0xA3,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E4_", 16,   2,      0xA4,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E5_", 16,   2,      0xA5,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E6_", 16,   2,      0xA6,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E7_", 16,   2,      0xA7,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E8_", 16,   2,      0xA8,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E9_", 16,   2,      0xA9,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "EA_", 16,   2,      0xAA,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "EB_", 16,   2,      0xAB,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "EC_", 16,   2,      0xAC,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "E",   16,   2,      0x98,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CS, "EM",  16,   2,      0xBC,      0,       0, 0x0F0000, 0x0F0000,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "TK",  1,    1,      0x06,      0,      31, 0x000000, 0x001F00,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "TKS", 1,    1,      0x46,      0,      31, 0x000000, 0x001F00,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "IR",  16,   4,      0xDC,      0,      15, 0x010000, 0x010F00,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "DR",  16,   2,      0xBC,      0,      15, 0x020000, 0x020F00,  FI_RD | FI_WR | FI_MRD,                            false },
	{ FINS_MODE_CS, "C1M", 1,    1,      0x07,      0,       0, 0x000000, 0x000000,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "C1S", 1,    1,      0x07,      0,       0, 0x000100, 0x000100,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "C02", 1,    1,      0x07,      0,       0, 0x000200, 0x000200,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "C01", 1,    1,      0x07,      0,       0, 0x000300, 0x000300,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "C22", 1,    1,      0x07,      0,       0, 0x000400, 0x000400,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CER", 1,    1,      0x07,      0,       0, 0x100000, 0x100000,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CCY", 1,    1,      0x07,      0,       0, 0x100100, 0x100100,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CGT", 1,    1,      0x07,      0,       0, 0x100200, 0x100200,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CEQ", 1,    1,      0x07,      0,       0, 0x100300, 0x100300,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CLT", 1,    1,      0x07,      0,       0, 0x100400, 0x100400,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "NEG", 1,    1,      0x07,      0,       0, 0x100500, 0x100500,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "COF", 1,    1,      0x07,      0,       0, 0x100600, 0x100600,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CUF", 1,    1,      0x07,      0,       0, 0x100700, 0x100700,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CGE", 1,    1,      0x07,      0,       0, 0x100800, 0x100800,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CNE", 1,    1,      0x07,      0,       0, 0x100900, 0x100900,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "CLE", 1,    1,      0x07,      0,       0, 0x100A00, 0x100A00,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "OFF", 1,    1,      0x07,      0,       0, 0x100E00, 0x100E00,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CS, "ON",  1,    1,      0x07,      0,       0, 0x100F00, 0x100F00,  FI_RD | FI_MRD,                            false },

	{ FINS_MODE_CV, "CIO", 1,    1,      0x00,      0,    2555, 0x000000, 0x09FB0F,  FI_RD | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CV, "CIO", 1,    1,      0x40,      0,    2555, 0x000000, 0x09FB0F,                            FI_MRD,                            true },
	{ FINS_MODE_CV, "CIO", 16,   2,      0x80,      0,    2555, 0x000000, 0x09FB00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "CIO", 16,   2,      0xC0,      0,    2555, 0x000000, 0x09FB00,                            FI_MRD,                            true },
	{ FINS_MODE_CV, "A",   1,    1,      0x00,      0,     959, 0x0B0000, 0x0EBF0F,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CV, "A",   1,    1,      0x00,    448,     959, 0x0CC000, 0x0EBF0F,  0,                                                           false },
	{ FINS_MODE_CV, "A",   16,   2,      0x80,      0,     959, 0x0B0000, 0x0EBF00,  FI_RD | FI_MRD | FI_TRS,                   false },
	{ FINS_MODE_CV, "A",   16,   2,      0x80,    448,     959, 0x0CC000, 0x0EBF00,          FI_WR | FI_FILL | FI_TRD,          false },
	{ FINS_MODE_CV, "TIM", 1,    1,      0x01,      0,    2047, 0x000000, 0x07FF00,  FI_RD | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CV, "TIM", 1,    1,      0x41,      0,    2047, 0x000000, 0x07FF00,                            FI_MRD,                            true },
	{ FINS_MODE_CV, "TIM", 16,   2,      0x81,      0,    2047, 0x000000, 0x07FF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "CNT", 1,    1,      0x01,      0,    2047, 0x080000, 0x0FFF00,  FI_RD | FI_MRD | FI_FRC, false },
	{ FINS_MODE_CV, "CNT", 1,    1,      0x41,      0,    2047, 0x080000, 0x0FFF00,                            FI_MRD,                            true },
	{ FINS_MODE_CV, "CNT", 16,   2,      0x81,      0,    2047, 0x080000, 0x0FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "DM",  16,   2,      0x82,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E0_", 16,   2,      0x90,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E1_", 16,   2,      0x91,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E2_", 16,   2,      0x92,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E3_", 16,   2,      0x93,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E4_", 16,   2,      0x94,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E5_", 16,   2,      0x95,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E6_", 16,   2,      0x96,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E7_", 16,   2,      0x97,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "E",   16,   2,      0x98,      0,   32767, 0x000000, 0x7FFF00,  FI_RD | FI_WR | FI_FILL | FI_MRD | FI_TRS | FI_TRD,          false },
	{ FINS_MODE_CV, "EM",  16,   2,      0x9C,      0,       0, 0x000600, 0x000600,  FI_RD | FI_MRD,                            false },
	{ FINS_MODE_CV, "DR",  16,   2,      0x9C,      0,       2, 0x000300, 0x000500,  FI_RD | FI_WR | FI_MRD,                            false },

	{ FINS_MODE_UNKNOWN, NULL, 0, 0,     0x00,      0,       0, 0x000000, 0x000000,  0,                                                           false }
};

#endif // FINS_STRUCTURE_H