#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>

namespace dx3d
{
	struct BaseDesc {
		Logger& logger;
	};

	struct WindowDesc {
		BaseDesc base;
		Rect size;
	};

	struct GraphicsDesc {
		BaseDesc base;
	};

	struct GraphicsDeviceDesc {
		BaseDesc base;
	};

	struct SwapChainDesc {
		void* winHandle{};
		Rect winSize{};
	};

	struct DisplayDesc {
		WindowDesc window;
		GraphicsDevice& graphicsDevice;
	};

	enum class ShaderType {
		Vertex = 0,
		Pixel,
	};

	struct ShaderCompileDesc {
		const char* shaderSourceName{};
		const void* shaderSourceCode{};
		size_t shaderSourceCodeSize{};
		const char* shaderEntryPoint{};
		const ShaderType shaderType;
	};

	struct ShaderBinaryData {
		const void* data{};
		size_t dataSize{};
	};

	struct VertexBufferDesc {
		const void* vertexList{};
		ui32 vertexListSize{};
		ui32 vertexSize{};
	};

	struct GraphicsPipelineStateDesc {
		const VertexShaderSignature& vs;
		const ShaderBinary& ps;
	};

	struct VertexShaderSignatureDesc {
		const ShaderBinaryPtr& vsBinary;
	};

	struct GameDesc {
		Rect windowSize{ 1280, 720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};
}