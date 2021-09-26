#pragma once
#include <functional>

enum log_color
{
	black = 0,
	red,
	green,
	blue,
	yellow,
	white,
	purple
};

int init_log(const char* logfilename, size_t maxfilesize);
void log_bind_sink(std::function<void(std::string, int)> sink);
void log_trace(const char* fmt, ...);
void log_debug(const char* fmt, ...);
void log_info(const char* fmt, ...);
void log_warning(const char* fmt, ...);
void log_error(const char* fmt, ...);
void log_fatal(const char* fmt, ...);

void log_trace_color(log_color color,const char* fmt, ...);
void log_debug_color(log_color color, const char* fmt, ...);
void log_info_color(log_color color, const char* fmt, ...);
void log_warning_color(log_color color, const char* fmt, ...);
void log_error_color(log_color color, const char* fmt, ...);
void log_fatal_color(log_color color, const char* fmt, ...);