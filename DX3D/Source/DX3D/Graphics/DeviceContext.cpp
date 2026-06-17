#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc): GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDegerredContexr Failed.");
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& colour)
{
	f32 fColour[] = {colour.x, colour.y, colour.z, colour.w};
	auto rtv = swapChain.m_renderTargetView.Get();
	m_context->ClearRenderTargetView(rtv, fColour);
	m_context->OMSetRenderTargets(1, &rtv, nullptr);
}
