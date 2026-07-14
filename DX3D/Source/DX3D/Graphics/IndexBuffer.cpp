#include <DX3D/Graphics/IndexBuffer.h>


dx3d::IndexBuffer::IndexBuffer(const IndexBufferDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_listSize(desc.indexListSize)
{
	// Param Check
	if (!desc.indexList) DX3DLogThrowInvalidArg("No IndexList Provided.");
	if (!desc.indexListSize) DX3DLogThrowInvalidArg("Invalid indexListSize");

	D3D11_BUFFER_DESC indexBufferDesc{};
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = desc.indexListSize * sizeof(ui32);

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.indexList;

	auto hr = m_device.CreateBuffer(&indexBufferDesc, &initData, &m_buffer);
	DX3DGraphicsLogThrowOnFail(hr, "Create IndexBuffer Failed");
}
