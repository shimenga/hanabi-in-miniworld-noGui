#include "Client.h"

namespace Client {

	// Globals
	HWND wndGame = nullptr;						// 游戏窗口句柄
	HMODULE clientModule = nullptr;				// DLL句柄
	std::string clientName("Hanabi");			// 端名
	std::string clientAuthor("阿茵Ayin");		// 作者名(现原作者)
	std::string clientMajorVersion("1");		// 主版本号
	std::string clientMinorVersion("0");		// 副版本号
	std::string clientDllPath("");				// 客户端DLL路径
	std::string clientAssetsPath("");			// 客户端资源路径
	ImGuiIO* rendererIO = nullptr;				// ImGuiIO
	ImFont* defaultFont = nullptr;				// 默认字体
	ImFont* hanabiFont = nullptr;				// Hanabi的字体
	Address hWorld = 0;							// libiworld_micro.dll基址

	namespace Texture {

		struct Picture hanabiLogo;				// LOGO纹理
		struct Picture background;				// MainPanel纹理
		struct Picture notificationInfo;
		struct Picture notificationErr;
		struct Picture notificationWarn;
		struct Picture notificationSuccess;

	}
	
	void initClient() {

		// 获取游戏窗口句柄
		Client::wndGame = FindWindowA("RenderWindow_ClassName", nullptr);
			
		// 获取主模块基址
		Client::hWorld = reinterpret_cast<Address>(GetModuleHandleA("libiworld_micro.dll"));
		
		// 获取DLL路径和资源路径
		char path[1024];
		RtlZeroMemory(path, 1024);
		GetModuleFileNameA(Client::clientModule, path, 1024);
		Client::clientDllPath = std::string(path);
		(strrchr(path, '\\'))[1] = 0;
		Client::clientAssetsPath = std::string(strcat(path, "assets\\"));

	}

	void initModules() {
		
		ModuleManager::getInstance().addModule<ClickGui>(ClickGui::getInstance());
		ModuleManager::getInstance().addModule<Disabler>(Disabler::getInstance());
		ModuleManager::getInstance().addModule<IDProtection>(IDProtection::getInstance());
		ModuleManager::getInstance().addModule<HighJump>(HighJump::getInstance());
		ModuleManager::getInstance().addModule<FasterSpeed>(FasterSpeed::getInstance());
		ModuleManager::getInstance().addModule<ESP>(ESP::getInstance());
		ModuleManager::getInstance().addModule<HUD>(HUD::getInstance());
		ModuleManager::getInstance().addModule<AirJump>(AirJump::getInstance());
		ModuleManager::getInstance().addModule<Fly>(Fly::getInstance());
		ModuleManager::getInstance().addModule<Aimbot>(Aimbot::getInstance());
		ModuleManager::getInstance().addModule<FakePosition>(FakePosition::getInstance());
		ModuleManager::getInstance().addModule<Phase>(Phase::getInstance());
		ModuleManager::getInstance().addModule<Reach>(Reach::getInstance());
		ModuleManager::getInstance().addModule<BoxESP>(BoxESP::getInstance());
		ModuleManager::getInstance().addModule<AutoClicker>(AutoClicker::getInstance());
		ModuleManager::getInstance().addModule<Team>(Team::getInstance());
		ModuleManager::getInstance().addModule<Radar>(Radar::getInstance());
		ModuleManager::getInstance().addModule<FillBright>(FillBright::getInstance());
	}

	void initEvents() {
		
		EventManager::getInstance().reg(Events::EventKeyDown, handleKeyEvent);
		EventManager::getInstance().reg(Events::EventUpdateData, Game::updateData);
	}

	void startClient(HMODULE thisModule) {

		Client::clientModule = thisModule;

#ifdef _DEBUG
		Utility::openConsole();
#endif
		
		Client::initClient();
		Client::initModules();
		Client::loadConfig();
		Client::initEvents();

		Renderer::startRenderer(Client::wndGame);

	}

	void handleKeyEvent() {

		if (ImGui::IsKeyDown(ImGuiKey_RightShift)) {
			EventManager::getInstance().call(Events::EventOpenClickGui);
		}


		if (ImGui::IsKeyDown(ImGuiKey_Escape)) {
			EventManager::getInstance().call(Events::EventCloseClickGui);
		}

		if (ImGui::IsKeyDown(ImGuiKey_W) || ImGui::IsKeyDown(ImGuiKey_A) || ImGui::IsKeyDown(ImGuiKey_S) || ImGui::IsKeyDown(ImGuiKey_D)) {
			EventManager::getInstance().call(Events::EventMotion);
		}
	}

	void loadTextures(IDirect3DDevice9* device) {

		char buffer[1024];
		RtlZeroMemory(buffer, 1024);
		strcpy(buffer, Client::clientAssetsPath.c_str());
		strcat(buffer, "image\\Hanabi.jpg");
		Renderer::loadTextureFromFile(device, buffer, &Client::Texture::hanabiLogo);

		RtlZeroMemory(buffer, 1024);
		strcpy(buffer, Client::clientAssetsPath.c_str());
		strcat(buffer, "image\\Window.png");
		Renderer::loadTextureFromFile(device, buffer, &Client::Texture::background);

		RtlZeroMemory(buffer, 1024);
		strcpy(buffer, Client::clientAssetsPath.c_str());
		strcat(buffer, "image\\INFO.png");
		Renderer::loadTextureFromFile(device, buffer, &Client::Texture::notificationInfo);

		RtlZeroMemory(buffer, 1024);
		strcpy(buffer, Client::clientAssetsPath.c_str());
		strcat(buffer, "image\\ERROR.png");
		Renderer::loadTextureFromFile(device, buffer, &Client::Texture::notificationErr);

		RtlZeroMemory(buffer, 1024);
		strcpy(buffer, Client::clientAssetsPath.c_str());
		strcat(buffer, "image\\WARNING.png");
		Renderer::loadTextureFromFile(device, buffer, &Client::Texture::notificationWarn);

		RtlZeroMemory(buffer, 1024);
		strcpy(buffer, Client::clientAssetsPath.c_str());
		strcat(buffer, "image\\SUCCESS.png");
		Renderer::loadTextureFromFile(device, buffer, &Client::Texture::notificationSuccess);

		NotificationManager::getInstance().setIcon(Client::Texture::notificationInfo.texture, Client::Texture::notificationErr.texture, Client::Texture::notificationSuccess.texture, Client::Texture::notificationWarn.texture);
	}

	void loadConfig() {
		
		Disabler::getInstance()->enable();
		HUD::getInstance()->enable();
		IDProtection::getInstance()->enable();
		Team::getInstance()->enable();
	}

}
