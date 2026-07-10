#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc)
{
	m_logger = std::make_unique<Logger>(desc.logLevel);
	DX3DLogInfo("C++ 3D Game Tutorial Series");
	DX3DLogInfo("--------------------------------------");

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsDesc{*m_logger});
	m_display = std::make_unique<Display>(DisplayDesc{ {*m_logger, desc.windowSize}, m_graphicsEngine->getGraphicsDevice() });

	DX3DLogInfo("Game Initialised.");
}

void dx3d::Game::onInternalUpdate()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<f32> delta = currentTime - m_previousTime;
	m_previousTime = currentTime;
	auto deltaTime = delta.count();
	m_graphicsEngine->render(m_display->getSwapChain());
}


dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down...");
}

dx3d::Logger& dx3d::Game::getLogger() noexcept
{
	return *m_logger;
}
