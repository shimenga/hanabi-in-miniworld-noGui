#pragma once
#include <Windows.h>
#include "Utility.h"
#include "Renderer.h"
#include "ImGuiHeader.h"
#include "EventManager.h"
#include "ModuleManager.h"
#include "NotificationManager.h"


// Modules
#include "ClickGui.h"
#include "IDProtection.h"
#include "HighJump.h"
#include "FasterSpeed.h"
#include "ESP.h"
#include "HUD.h"
#include "AirJump.h"
#include "Fly.h"
#include "Aimbot.h"
#include "FakePosition.h"
#include "Disabler.h"
#include "Phase.h"
#include "Reach.h"
#include "BoxESP.h"
#include "AutoClicker.h"
#include "Team.h"
#include "Radar.h"
#include "FillBright.h"

#define MakeThread(_Executor, _Param) CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(_Executor), _Param, 0, nullptr)
#define MakeDisposableThread(_Executor, _Param) CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(_Executor), _Param, 0, nullptr))

using Address = unsigned long;
using Pointer = unsigned long;
using Byte = unsigned char;

namespace Client {

	extern HWND wndGame;
	extern HMODULE clientModule;
	extern std::string clientAuthor;
	extern std::string clientMajorVersion;
	extern std::string clientMinorVersion;
	extern std::string clientDllPath;
	extern std::string clientAssetsPath;
	extern ImGuiIO* rendererIO;
	extern ImFont* defaultFont;
	extern ImFont* hanabiFont;
	extern Address hWorld;

	namespace Texture {

		extern struct Picture hanabiLogo;				// LOGO����
		extern struct Picture background;				// MainPanel����
		extern struct Picture notificationInfo;
		extern struct Picture notificationErr;
		extern struct Picture notificationWarn;
		extern struct Picture notificationSuccess;

	}

	void initClient();
	void initModules();
	void initEvents();
	void startClient(HMODULE thisModule);
	void handleKeyEvent();
	void loadTextures(IDirect3DDevice9* device);
	void loadConfig();

}

