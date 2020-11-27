#pragma once

#include <spdlog/spdlog.h>

#define LOG_DEBUG(Format, ...)		MyLogger::Debug(Format, __VA_ARGS__)
#define LOG_INFO(Format, ...)		MyLogger::Info(Format, __VA_ARGS__)
#define LOG_WARNING(Format, ...)	MyLogger::Warning(Format, __VA_ARGS__)
#define LOG_ERROR(Format, ...)		MyLogger::Error(Format, __VA_ARGS__)
#define LOG_CRITICAL(Format, ...)	MyLogger::Critical(Format, __VA_ARGS__)

class MyLogger
{
public:
	static void Initialize(std::string filename)
	{
		auto console_logger = spdlog::stdout_color_mt("console");
		console_logger->info("console logger initialized");

		std::string filepath("logs/");
		filepath += filename;
		auto daily_logger = spdlog::daily_logger_mt("daily", filepath, 0, 0);
		console_logger->info("daily logger initialized");
	}

	static void Close()
	{
		spdlog::drop_all();
	}

	template <typename... Args>
	static void Log(spdlog::level::level_enum lvl, const char* fmt, const Args&... args)
	{
		auto console_logger = spdlog::get("console");
		if (console_logger != nullptr)
			console_logger->log(lvl, fmt, args...);

		auto daily_logger = spdlog::get("daily");
		if (daily_logger != nullptr)
		{
			daily_logger->log(lvl, fmt, args...);
			daily_logger->flush();
		}
	}

	template <typename... Args>
	static void Debug(const char* fmt, const Args&... args)
	{
		Log(spdlog::level::level_enum::debug, fmt, args...);
	}

	template <typename... Args>
	static void Info(const char* fmt, const Args&... args)
	{
		Log(spdlog::level::level_enum::info, fmt, args...);
	}

	template <typename... Args>
	static void Warning(const char* fmt, const Args&... args)
	{
		Log(spdlog::level::level_enum::warn, fmt, args...);
	}

	template <typename... Args>
	static void Error(const char* fmt, const Args&... args)
	{
		Log(spdlog::level::level_enum::err, fmt, args...);
	}

	template <typename... Args>
	static void Critical(const char* fmt, const Args&... args)
	{
		Log(spdlog::level::level_enum::critical, fmt, args...);
	}

	template<typename T>
	static void Log(spdlog::level::level_enum lvl, const T& msg)
	{
		auto console_logger = spdlog::get("console");
		if (console_logger != nullptr)
			console_logger->log(lvl, msg);

		auto daily_logger = spdlog::get("daily");
		if (daily_logger != nullptr)
		{
			daily_logger->log(lvl, msg);
			daily_logger->flush();
		}
	}

	template<typename T>
	static void Debug(const T& msg)
	{
		Log(spdlog::level::level_enum::debug, msg);
	}

	template<typename T>
	static void Info(const T& msg)
	{
		Log(spdlog::level::level_enum::info, msg);
	}

	template<typename T>
	static void Warning(const T& msg)
	{
		Log(spdlog::level::level_enum::warn, msg);
	}

	template<typename T>
	static void Error(const T& msg)
	{
		Log(spdlog::level::level_enum::err, msg);
	}

	template<typename T>
	static void Critical(const T& msg)
	{
		Log(spdlog::level::level_enum::critical, msg);
	}
};
