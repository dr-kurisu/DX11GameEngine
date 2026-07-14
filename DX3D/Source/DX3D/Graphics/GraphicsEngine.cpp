#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <fstream>
 
using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsDesc& desc) : Base(desc.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});
	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("Failed to open shader file.");
	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),
		std::istreambuf_iterator<char>()
	};


	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	auto vs = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "VSMain", ShaderType::Vertex });
	auto ps = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "PSMain", ShaderType::Pixel });
	auto vsSig = device.createVertexShaderSignature({ vs });

	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	const Vertex vertexList[] =
	{
		{{-0.5f,-0.5f,-0.5f}, {1,0,0,1}},
		{{-0.5f,0.5f,-0.5f}, {0,1,0,1} },
		{{0.5f,0.5f,-0.5f},  {0,0,1,1}},
		{{0.5f,-0.5f,-0.5f}, {1,0,1,1}},

		{{0.5f,-0.5f,0.5f}, {1,0,1,1}},
		{{0.5f,0.5f,0.5f}, {0,0,1,1}},
		{{-0.5f,0.5f,0.5f}, {0,1,0,1}},
		{{-0.5f,-0.5f,0.5f}, {1,0,0,1}}
	};

	const ui32 indexList[] =
	{
		//winding order: clockwise
		// 
		//front face indices
		0,1,2,  //first triangle
		2,3,0,  //second triangle
		//back face indices
		4,5,6,
		6,7,4,
		//top face indices
		1,6,5,
		5,2,1,
		//bottom face indices
		7,0,3,
		3,4,7,
		//right face indices
		3,2,5,
		5,4,3,
		//left face indices
		7,6,1,
		1,0,7
	};

	m_vb = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vertex)});
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData)});
	m_ib = device.createIndexBuffer({indexList, std::size(indexList)});
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept {
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain, f32 deltaTime)
{
	auto& context = *m_deviceContext;
	auto& cb = *m_cb;

	m_pos += deltaTime * 0.0f;
	m_rot += deltaTime * 0.707f;
	m_scale = std::abs(std::sin(m_rot));

	DX3DLogInfo("Pos: X:{} Y:{}", m_pos, m_pos);
	DX3DLogInfo("Rot: Z:{}", m_rot);
	DX3DLogInfo("Scale: {}", m_scale);

	auto worldMat =
		Mat4::scale({ m_scale,m_scale,m_scale }) *
		Mat4::rotateX(m_rot) *
		Mat4::rotateY(m_rot) *
		Mat4::rotateZ(m_rot) *
		Mat4::translate({ m_pos,m_pos,0 });

	//orthographic camera setup
	auto size = swapChain.getSize();
	auto aspect = static_cast<f32>(size.width) / size.height;
	auto unitsPerScreenHeight = 2.0f;
	auto viewHeight = unitsPerScreenHeight;
	auto viewWidth = unitsPerScreenHeight * aspect;
	auto projMat = Mat4::orthoLH(viewWidth, viewHeight, -10.0f, 10.0f);

	ConstantData data{ worldMat, projMat };
	context.updateConstantBuffer(cb, &data);

	context.clearAndSetBackBuffer(swapChain, Vec4{ 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(swapChain.getSize());

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.setConstantBuffer(cb);
	context.drawTriangleList(vb.getVertexSize(), 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);

	swapChain.present();
}
