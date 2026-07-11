#include <DX3D/Core/Logger.h>
#include <iostream>

dx3d::Logger::Logger(LogLevel logLevel) : m_logLevel(logLevel)
{
	// Initialiser list (using logLevel init private attribute m_logLevel)
	std::clog << "[DX3D Logger]: Log level set to " << static_cast<int>(logLevel) << "\n";
	std::clog << "---------------------------------------------------" << "\n";
}

dx3d::Logger::~Logger()
{

}

void dx3d::Logger::_log(LogLevel level, const char* msg)
{
	auto logLevelToString = [](LogLevel level) {
		switch (level) {
		case LogLevel::Info: return "Info";
		case LogLevel::Warning: return "Warning";
		case LogLevel::Error: return "Error";
		default: return "Unknown";
		}
	};
	if (level > m_logLevel) return;
	std::clog << "[DX3D " << logLevelToString(level) << "]: " << msg << "\n";

}
