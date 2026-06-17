#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsDesc& desc) : Base(desc.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});
	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept {
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, Vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);

	swapChain.present();
}
