#pragma once
#include <DX3D/Window/Window.h>

namespace dx3d {
	class Display final: public Window
	{
	public:
		Display(const DisplayDesc& desc);
	private:
		SwapChainPtr m_swapChain{};
	};
}


