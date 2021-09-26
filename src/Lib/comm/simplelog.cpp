// boostlog.cpp : 定义 DLL 应用程序的导出函数。
//
#include <stdarg.h>
#include <stdio.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/signals2/signal.hpp>
#include "comm/simplelog.h"
#include <windows.h>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

using namespace logging::trivial;
static src::severity_logger<severity_level> lg;

const int  Buff_SIZE = 1024000;
static char buff_[Buff_SIZE] = { 0 };
static boost::mutex g_mutex;
static boost::signals2::signal<void(std::string, int)> print_sink_signal_;
static bool log_initialized_ = false;

int init_log(const char* logfilename, size_t maxfilesize)
{
	// The first thing we have to do to get using the library is
	// to set up the logging sinks - i.e. where the logs will be written to.
	logging::add_console_log(std::clog, keywords::format = "[%TimeStamp%]: %Message%");

	// One can also use lambda expressions to setup filters and formatters
	logging::add_file_log
	(
		keywords::file_name = logfilename,                                        /*< file name pattern >*/
		keywords::rotation_size = maxfilesize * 1024 * 1024 * 10,                                   /*< rotate files every 10 MiB... >*/
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(boost::date_time::weekdays(boost::date_time::weekdays::Monday)), /*< ...or at midnight >*/
		keywords::format = "[%TimeStamp%]: %Message%",                                 /*< log record format >*/
		keywords::auto_flush = true
	);

#ifdef _DEBUG
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
#else
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
#endif

	logging::add_common_attributes();
	log_initialized_ = true;

	return 0;
}

void log_bind_sink(std::function<void(std::string, int)> sink)
{
	print_sink_signal_.connect(sink);
}

void log_trace(const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, trace) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}

	print_sink_signal_(buff_, log_color::black);
}

void log_debug(const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, debug) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, log_color::black);
}

void log_info(const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, info) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, log_color::black);
}

void log_warning(const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, warning) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, log_color::black);
}

void log_error(const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, error) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, log_color::red);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_fatal(const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, fatal) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, log_color::red);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_trace_color(log_color color, const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (color)
	{
	case red:
		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case green:
		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case blue:
		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case white:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case yellow:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case purple:
		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		wAttributes = wOldColorAttrs;
		break;
	}
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, trace) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, color);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_debug_color(log_color color, const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (color)
	{
	case red:
		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case green:
		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case blue:
		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case white:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case yellow:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case purple:
		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		wAttributes = wOldColorAttrs;
		break;
	}
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, debug) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, color);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_info_color(log_color color, const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (color)
	{
	case red:
		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case green:
		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case blue:
		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case white:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case yellow:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case purple:
		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		wAttributes = wOldColorAttrs;
		break;
	}
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, info) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, color);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_warning_color(log_color color, const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (color)
	{
	case red:
		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case green:
		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case blue:
		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case white:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case yellow:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case purple:
		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		wAttributes = wOldColorAttrs;
		break;
	}
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, warning) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, color);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_error_color(log_color color, const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (color)
	{
	case red:
		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case green:
		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case blue:
		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case white:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case yellow:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case purple:
		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		wAttributes = wOldColorAttrs;
		break;
	}
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, error) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, color);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

void log_fatal_color(log_color color, const char* fmt, ...)
{
	boost::mutex::scoped_lock lock(g_mutex);
	HANDLE handle;
	WORD wOldColorAttrs, wAttributes;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	switch (color)
	{
	case red:
		wAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		break;
	case green:
		wAttributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case blue:
		wAttributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case white:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	case yellow:
		wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		break;
	case purple:
		wAttributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		break;
	default:
		wAttributes = wOldColorAttrs;
		break;
	}
	SetConsoleTextAttribute(handle, wAttributes);

	memset(buff_, 0, Buff_SIZE);
	va_list args;
	va_start(args, fmt);
	_vsnprintf_s(buff_, Buff_SIZE, Buff_SIZE, fmt, args);
	va_end(args);
	if (log_initialized_)
	{
		BOOST_LOG_SEV(lg, fatal) << buff_;
	}
	else
	{
		std::cout << buff_ << std::endl;
	}
	print_sink_signal_(buff_, color);

	SetConsoleTextAttribute(handle, wOldColorAttrs);
}

