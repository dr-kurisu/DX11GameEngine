#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc)
{
	if (desc.ps.getType() != ShaderType::Pixel)
		DX3DLogThrowInvalidArg("The ps member is not a valid pixel shader");


	auto vs = desc.vs.getShaderBinary();
	auto ps = desc.ps.getData();
	auto vsInputElements = desc.vs.getInputBinaryData();

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateInputLayout(
			static_cast<const D3D11_INPUT_ELEMENT_DESC*>(vsInputElements.data), 
			static_cast<ui32>(vsInputElements.dataSize),
			vs.data, 
			vs.dataSize, 
			&m_layout),
		"CreateInputLayout Failed.");

	DX3DGraphicsLogThrowOnFail(m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader Failed.");
	DX3DGraphicsLogThrowOnFail(m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader Failed.");

}
