#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>

namespace dx3d {
	struct LoggerOwner {
		explicit LoggerOwner(Logger::LogLevel level)
			: loggerOwner(level) {
		}
		Logger loggerOwner;
	};
}