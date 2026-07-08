#pragma once
#include <DX3D/Core/Common.h>
#include <d3d11.h>
#include <bit>

namespace dx3d {
	namespace GraphicsUtils {
		inline const char* GetShaderModelTarget(ShaderType type) {
			switch (type) {
			case ShaderType::Vertex: return "vs_5_0";
			case ShaderType::Pixel: return "ps_5_0";
			default: return "";
			}
		}

		inline DXGI_FORMAT GetDXGIFomartFromMask(D3D_REGISTER_COMPONENT_TYPE type, UINT mask) {
			auto componentCount = std::popcount(mask); // count num 1s
			if (componentCount < 1) return DXGI_FORMAT_UNKNOWN;
			constexpr DXGI_FORMAT formatTable[1][4] = {
				{
					DXGI_FORMAT_R32_FLOAT,
					DXGI_FORMAT_R32G32_FLOAT,
					DXGI_FORMAT_R32G32B32_FLOAT,
					DXGI_FORMAT_R32G32B32A32_FLOAT,
				}
			};

			auto typeIndex = 0u;
			switch (type) {
			case D3D_REGISTER_COMPONENT_FLOAT32: typeIndex = 0u; break;
			default: return DXGI_FORMAT_UNKNOWN;
			}
			return formatTable[typeIndex][componentCount - 1];
		}
	}
}