#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gDesc): 
	GraphicsResource(gDesc), m_vertexSize(desc.vertexSize), m_vertexListSize(desc.vertexListSize) {
	if (!desc.vertexList) DX3DLogThrowInvalidArg("No Vertex List provided.");
	if (!desc.vertexListSize) DX3DLogThrowInvalidArg("Vertex List Size must be non-zero.");
	if (!desc.vertexSize) DX3DLogThrowInvalidArg("Vertex Size must be non-zero."); 
	
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = desc.vertexListSize * desc.vertexSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.vertexList;

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateBuffer(&bufferDesc, &initData, &m_buffer),
		"CreateBuffer Failed.");
}

dx3d::ui32 dx3d::VertexBuffer::getVertexSize() const noexcept
{
	return m_vertexListSize;
}
