#include <DX3D/Graphics/ConstantBuffer.h>

dx3d::ConstantBuffer::ConstantBuffer(const ConstantBufferDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_size(desc.bufferSize)
{
	if (!desc.bufferSize) DX3DLogThrowInvalidArg("Buffer size must be non-zero.");
	D3D11_BUFFER_DESC buffDesc{};
	buffDesc.Usage = D3D11_USAGE_DYNAMIC;
	buffDesc.ByteWidth = desc.bufferSize;
	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.buffer;

	auto hr = m_device.CreateBuffer(&buffDesc, &initData, &m_buffer);
	DX3DGraphicsLogThrowOnFail(hr, "CreateBuffer Failed.");

}
