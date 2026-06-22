#pragma once

namespace dx3d {
	class Logger final
	{
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info
		};

		explicit Logger(LogLevel logLevel = LogLevel::Error);
		~Logger();
		void log(LogLevel level, const char* msg);

	protected:
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;
		Logger(Logger&&) = delete;

	private:
		LogLevel m_logLevel = LogLevel::Error;
	};
}

#define DX3DLog(logger, type, msg)\
logger.log((type), msg)

#define DX3DLogThrow(logger, exception, type, msg)\
{\
DX3DLog(logger, type, msg);\
throw exception{msg};\
}