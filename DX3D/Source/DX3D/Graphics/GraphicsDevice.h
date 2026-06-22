#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <d3d11.h>
#include <wrl.h>
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d {
	class GraphicsDevice final : public Base, public std::enable_shared_from_this<GraphicsDevice>
	{
	public:
		GraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~GraphicsDevice() override;

		SwapChainPtr createSwapChain(const SwapChainDesc& desc) const;
		DeviceContextPtr createDeviceContext() const;
		ShaderBinaryPtr compileShader(const ShaderCompileDesc& desc);

		void executeCommandList(const DeviceContext& context);
	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdaptor{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};
	};
}