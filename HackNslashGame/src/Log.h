#pragma once

#include <memory>
#include "includes.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetSDLLogger() { return s_SDLLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
	static std::shared_ptr<spdlog::logger> s_SDLLogger;
};

// Game log macros
#define GAME_TRACE(...) Log::GetClientLogger()->trace(__VA_ARGS__)
#define GAME_INFO(...)  Log::GetClientLogger()->info(__VA_ARGS__)
#define GAME_WARN(...)  Log::GetClientLogger()->warn(__VA_ARGS__)
#define GAME_ERROR(...) Log::GetClientLogger()->error(__VA_ARGS__)
#define GAME_FATAL(...) Log::GetClientLogger()->critical(__VA_ARGS__)

// SDL log macros
#define SDL_TRACE(...) Log::GetSDLLogger()->trace(__VA_ARGS__)
#define SDL_INFO(...)  Log::GetSDLLogger()->info(__VA_ARGS__)
#define SDL_WARN(...)  Log::GetSDLLogger()->warn(__VA_ARGS__)
#define SDL_ERROR(...) Log::GetSDLLogger()->error(__VA_ARGS__)
#define SDL_FATAL(...) Log::GetSDLLogger()->critical(__VA_ARGS__)