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

#define DX3DlogInfo(message)\
	{\
	logger().log(Logger::LogLevel::Warning, message);\
	}

#define DX3DLogWarning(message)\
	{\
	logger().log(Logger::LogLevel::Warning, message);\
	}

#define DX3DLogError(message)\
	logger().log(Logger::LogLevel::Error, message);

#define DX3DLogErrorAndTHROW(message) \
	{ \
		logger().log(Logger::LogLevel::Error, message); \
		throw std::runtime_error(message); \
	}
}