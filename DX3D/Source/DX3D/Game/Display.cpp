#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/GraphicsDevice.h>

using namespace dx3d;
dx3d::Display::Display(const DisplayDesc& desc): Window(desc.window)
{
	m_swapChain = desc.graphicsDevice.createSwapChain({ m_handle, m_size });
}

SwapChain& dx3d::Display::getSwapChain() noexcept
{
	return *m_swapChain;
}
