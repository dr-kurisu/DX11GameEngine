#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>


dx3d::Game::Game(const GameDesc& desc):
	LoggerOwner(desc.logLevel),
	Base({ LoggerOwner::logger })
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsDesc{m_logger});
	m_display = std::make_unique<Window>(WindowDesc{m_logger});

	m_logger.log(Logger::LogLevel::Info, "Game initialised.");
}

dx3d::Game::~Game()
{
	m_logger.log(Logger::LogLevel::Info, "Game deallocation started.");
}