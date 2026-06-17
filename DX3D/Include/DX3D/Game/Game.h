#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <DX3D/Core/LoggerOwner.h>

namespace dx3d {
	

	class Game : private LoggerOwner, public Base {
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game() override;
		virtual void run() final;
	private:
		void onInternalUpdate();
	private:
		bool m_isRunning = true;
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{};
		std::unique_ptr<Display> m_display{};
	};
}