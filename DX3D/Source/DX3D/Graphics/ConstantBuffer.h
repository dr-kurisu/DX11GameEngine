#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class ConstantBuffer : public GraphicsResource {
	public:
		ConstantBuffer(const ConstantBufferDesc& desc, const GraphicsResourceDesc& gDesc);
	private:
		ui32 m_size{};

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
		friend class DeviceContext;
	};
}