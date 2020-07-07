#include "Log.h"


std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
std::shared_ptr<spdlog::logger> Log::s_SDLLogger;


void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_ClientLogger = spdlog::stdout_color_mt("GAME");
	s_ClientLogger->set_level(spdlog::level::trace);

	s_SDLLogger = spdlog::stdout_color_mt("SDL");
	s_SDLLogger->set_level(spdlog::level::trace);

}
