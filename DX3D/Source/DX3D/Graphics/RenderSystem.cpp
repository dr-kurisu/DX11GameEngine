#include <DX3D/Graphics/RenderSystem.h>

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

	if (FAILED(hr)) {
		logger().log(Logger::LogLevel::Error, "Failed to create D3D11 device and context.");
		throw std::runtime_error("Failed to create D3D11 device and context");
	}
}


dx3d::RenderSystem::~RenderSystem()
{
}
