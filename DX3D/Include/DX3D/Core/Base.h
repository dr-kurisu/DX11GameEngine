#pragma once
#include <DX3D/Core/Common.h>

namespace dx3d
{
	class Base {
		dx3d_disable_copy_and_move(Base)
	public:
		explicit Base(const BaseDesc& desc);
		virtual ~Base();
		virtual Logger& logger() noexcept final;
	protected:
		Logger& m_logger;
	};	
}

//#define DX3DlogInfo(message)\
//	DX3DLog(logger(), Logger::LogLevel::Info, message)
//
//#define DX3DLogWarning(message)\
//	DX3DLog(logger(), Logger::LogLevel::Warning, message)
//
//#define DX3DLogError(message)\
//	DX3DLog(logger(), Logger::LogLevel::Error, message)
//
//#define DX3DLogThrowError(message) \
//	DX3DLogThrow(logger(), std::runtime_error, Logger::LogLevel::Info, message)
//
//#define DX3DLogThrowInvalidArg(message) \
//	DX3DLogThrow(logger(), std::invalid_argument, Logger::LogLevel::Info, message)
