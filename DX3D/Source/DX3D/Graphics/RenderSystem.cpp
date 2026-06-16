#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc): Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel = {};
	UINT createDeviceFlags = 0;

#ifdef DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// HRESULT (Failed and Success => <0 and >0)
	auto hr = D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,  // pick primary GPU
		NULL,
		createDeviceFlags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&m_d3dDevice,
		&featureLevel,
		&m_d3dContext
	);

	DX3DGrpahicsLogErrorAndThrow(hr, "Direct3D11 initialisation failed.");
	DX3DGrpahicsLogErrorAndThrow(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)), "QueryInterface failed to retrieve IDXGDevice.");
	DX3DGrpahicsLogErrorAndThrow(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdaptor)), "GetParent failed to retrieve IDXGAdaptor.");
	DX3DGrpahicsLogErrorAndThrow(m_dxgiAdaptor->GetParent(IID_PPV_ARGS(&m_dxgiFactory)), "GetParent failed to retrieve IDXGFactory.");
}


dx3d::RenderSystem::~RenderSystem()
{
}

SwapChainPtr dx3d::RenderSystem::createSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

GraphicsResourceDesc dx3d::RenderSystem::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get()};
}
