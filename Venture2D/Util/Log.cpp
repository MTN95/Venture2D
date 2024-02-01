#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace venture {

	SharedLogger Log::s_Logger;

	void Log::Init()
	{
		spdlog::set_pattern("[%T] [%l] %n:%$ %v");
		s_Logger = spdlog::stdout_color_mt("Venture");
		s_Logger->set_level(spdlog::level::trace);
	}

}