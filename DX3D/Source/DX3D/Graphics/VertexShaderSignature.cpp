#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <ranges>

dx3d::VertexShaderSignature::VertexShaderSignature(const VertexShaderSignatureDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_vsBinary(desc.vsBinary)
{
	if (!desc.vsBinary) DX3DLogThrowInvalidArg("No vsBinary provided.");
	if (desc.vsBinary->getType() != ShaderType::Vertex)
		DX3DLogThrowInvalidArg("Invalid vsBinary member.");

	auto vsData = desc.vsBinary->getData();

	auto hr = D3DReflect(
		vsData.data,
		vsData.dataSize,
		IID_PPV_ARGS(&m_shaderReflection)
	);
	DX3DGraphicsLogThrowOnFail(hr, "D3DReflect Failed.");
	D3D11_SHADER_DESC shaderDesc{};
	DX3DGraphicsLogThrowOnFail(m_shaderReflection->GetDesc(&shaderDesc), 
		"ID3D11ShaderReflection:GetDesc Failed.");
	
	m_numElements = shaderDesc.InputParameters;
	D3D11_SIGNATURE_PARAMETER_DESC params[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{};

	for (auto i : std::views::iota(0u, m_numElements)) {
		DX3DGraphicsLogThrowOnFail(m_shaderReflection->GetInputParameterDesc(i, &params[i]), 
			"ID3D11ShaderReflection::GetInputParameterDesc Failed.");
	}

	//constexpr D3D11_INPUT_ELEMENT_DESC elements[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{"COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	//};
	for (auto i : std::views::iota(0u, m_numElements)) {
		auto param = params[i];
		m_elements[i] = {
			param.SemanticName,
			param.SemanticIndex,
			GraphicsUtils::GetDXGIFomartFromMask(param.ComponentType, param.Mask),
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};
	}
}

dx3d::ShaderBinaryData dx3d::VertexShaderSignature::getShaderBinary() const noexcept
{
	return m_vsBinary->getData();
}

dx3d::ShaderBinaryData dx3d::VertexShaderSignature::getInputBinaryData() const noexcept
{
	return
	{
		m_elements,
		m_numElements
	};
}
