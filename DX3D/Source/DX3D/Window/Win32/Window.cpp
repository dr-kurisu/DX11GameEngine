#include <DX3D/Window/Window.h>
#include <Windows.h>
#include <stdexcept>

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


dx3d::Window::Window(const WindowDesc& desc): Base(desc.base), m_size(desc.size) {
	auto registerWindowClassFunction = []()
	{
		WNDCLASSEX wc{};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = L"DX3DWindowClass";
		wc.lpfnWndProc = &WindowProc;
		return RegisterClassEx(&wc);
	};

	static const auto windowClassId = registerWindowClassFunction();


	// fail to create window
	if (!windowClassId) {
		DX3DLogThrowError("RegisterClassEx Failed.");
	}

	RECT rc = { 0, 0, m_size.width, m_size.height };
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

	m_handle = CreateWindowEx(NULL, MAKEINTATOM(windowClassId), L"Tutorial | C++ Game Engine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, NULL, NULL
	);
	if (!m_handle) {
		DX3DLogThrowError("CreateWindowEx failed");
	}
	ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);
}


dx3d::Window::~Window() {
	DestroyWindow(static_cast<HWND>(m_handle));
}