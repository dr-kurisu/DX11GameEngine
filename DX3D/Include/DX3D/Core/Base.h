#pragma once
#include <DX3D/Core/Common.h>

namespace dx3d
{
	class Base {
	public:
		explicit Base(const BaseDesc& desc);
		virtual ~Base();
		virtual Logger& logger() noexcept final;
	protected:
		Base(const Base&) = delete;
		Base& operator=(const Base&) = delete;
		Base& operator=(Base&&) = delete;
		Base(Base&&) = delete;
	protected:
		Logger& m_logger;
	};
}
