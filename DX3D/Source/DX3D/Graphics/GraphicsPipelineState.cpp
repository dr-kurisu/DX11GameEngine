#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc)
{
	if (desc.vs.getType() != ShaderType::Vertex)
		DX3DLogThrowInvalidArg("The vs member is not a valid vertex shader");
	if (desc.ps.getType() != ShaderType::Pixel)
		DX3DLogThrowInvalidArg("The ps member is not a valid pixel shader");


	auto vs = desc.vs.getData();
	auto ps = desc.ps.getData();
	DX3DGraphicsLogThrowOnFail(m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader Failed.");
	DX3DGraphicsLogThrowOnFail(m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader Failed.");

}
