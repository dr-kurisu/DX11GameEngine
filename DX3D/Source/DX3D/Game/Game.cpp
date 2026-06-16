#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc):
	LoggerOwner(desc.logLevel),
	Base({ LoggerOwner::loggerOwner })
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsDesc{m_logger});
	m_display = std::make_unique<Display>(DisplayDesc{ {m_logger, desc.windowSize}, m_graphicsEngine->getRenderSystem() });
	DX3DlogInfo("Game Initialised.");
}

dx3d::Game::~Game()
{
	DX3DlogInfo("Game Deallocation Started.");
}