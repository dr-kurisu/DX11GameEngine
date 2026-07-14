#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class IndexBuffer : public GraphicsResource {
	public:
		IndexBuffer(const IndexBufferDesc& desc, const GraphicsResourceDesc& gDesc);
		ui32 getListSize() const noexcept;
	private:
		ui32 m_listSize;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
		friend class DeviceContext;
	};
}

