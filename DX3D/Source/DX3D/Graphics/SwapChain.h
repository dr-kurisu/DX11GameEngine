#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class SwapChain : public GraphicsResource {
	public:
		SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc);

		void present(bool vsync = false);
	private:
		void reloadBuffers();
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView{};

		friend class DeviceContext;
	};
}
