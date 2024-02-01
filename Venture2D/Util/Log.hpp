/**
 * The Log class provides an easy-to-use interface for logging messages using the SPDlog library.
 * It encapsulates a single static logger instance shared across the application.
 * Log messages also include the source file name and line number.
 *
 * Example Usage:
 *
 * NOTE: initializing the logger before using it is required.
 *
 * venture::Log::Init(); // initialize the logger
 *
 * // Use the LOG macro
 * LOG_TRACE("This is a trace message.");
 * LOG_DEBUG("This is a debug message.");
 * LOG_INFO("This is an info message.");
 * LOG_WARN("This is a warning message.");
 * LOG_ERROR("This is an error message.");
 * LOG_FATAL("This is a fatal message.");
 *
 * for formatting spdlog uses fmt - https://github.com/fmtlib/fmt
 */
#pragma once

#include <spdlog/spdlog.h>
#include <memory>

// Extract the file name from the __FILE__ macro
constexpr const char* shortFileName(const char* filePath)
{
	const char* file = filePath;
	for (const char* p = filePath; *p; ++p) {
		if (*p == '/' || *p == '\\') {
			file = p + 1;
		}
	}
	return file;
}

namespace venture
{
	using SharedLogger = std::shared_ptr<spdlog::logger>;
	/**
	 * @brief A Simple spdlog wrapper Log class with a single static Logger instance.
	 */
	class Log
	{
	public:
		/**
		 * @brief Initialize the logger.
		 */
		static void Init();

		/**
		* @brief Get the shared logger instance.
		* @return A reference to the shared logger.
		*/
		inline static SharedLogger& GetLogger() { return s_Logger; }
	private:
		static SharedLogger s_Logger;
	};


}

#define LOG_TRACE(...)	::venture::Log::GetLogger()->trace("[{}:{}]: {}", shortFileName(__FILE__), __LINE__, fmt::format(__VA_ARGS__))
#define LOG_DEBUG(...)	::venture::Log::GetLogger()->debug("[{}:{}]: {}", shortFileName(__FILE__), __LINE__, fmt::format(__VA_ARGS__))
#define LOG_INFO(...)   ::venture::Log::GetLogger()->info("[{}:{}]: {}", shortFileName(__FILE__), __LINE__, fmt::format(__VA_ARGS__))
#define LOG_WARN(...)	::venture::Log::GetLogger()->warn("[{}:{}]: {}", shortFileName(__FILE__), __LINE__, fmt::format(__VA_ARGS__))
#define LOG_ERROR(...)  ::venture::Log::GetLogger()->error("[{}:{}]: {}", shortFileName(__FILE__), __LINE__, fmt::format(__VA_ARGS__))
#define LOG_FATAL(...)  ::venture::Log::GetLogger()->fatal("[{}:{}]: {}", shortFileName(__FILE__), __LINE__, fmt::format(__VA_ARGS__))
