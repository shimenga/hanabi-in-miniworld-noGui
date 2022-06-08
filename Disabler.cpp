#include "Disabler.h"

Disabler::Disabler() : AbstractModule("Disabler", Category::World) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Disabler::onRenderOverlay));
}

Disabler* Disabler::getInstance() {
	static Disabler* inst = new Disabler();
	return inst;
}

void Disabler::onEnabled() {

}

void Disabler::onDisabled() {

}

void bypass(int* wndACAddr) {
	
	Disabler* disabler = Disabler::getInstance();
	DWORD EnumWindowsaddr = (DWORD)GetProcAddress(GetModuleHandleA("user32.dll"), "EnumWindows");
	unsigned char data[5] = { 0x33 ,0xC0,0xC2,0x08,0x00 };
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(EnumWindowsaddr), data, 5, nullptr);
	DWORD EnumProcessesaddr = (DWORD)GetProcAddress(GetModuleHandleA("user32.dll"), "EnumProcesses");
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(EnumProcessesaddr), data, 5, nullptr);
	//BYTE data1[6] = { 0x90, 0x90, 0x90, 0x90 ,0x90 ,0x90 };
	//WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::CloudServerBypass), data1, 6, nullptr);
	NotificationManager::getInstance().makeNotification("Anti-Cheat Bypassed!", Type::SUCCESS);
	//Sleep(1000);
	//if (disabler->startBypass()) {
		
	//	Sleep(10000);
	//	disabler->endBypass();

	//	Sleep(9000);
	//	*wndACAddr = 16777216;
		
	//}
	//else {
	//	disabler->bypassError();
	//}

}

void Disabler::onRenderOverlay() {
	
}

void Disabler::bypassError() {
	Utility::notice("Disabler没能成功绕过反作弊，但是这并不影响Hanabi Client正常工作，您可以继续使用Hanabi Client(如果您愿意承担相应的风险)，但是还是建议您暂时不要再继续使用Hanabi Client，应等候开发者修复该错误!", Level::ERR);
	NotificationManager::getInstance().makeNotification("Disabler Error!", Type::EXCEPTION);
	this->disable();
}

bool Disabler::startBypass() {

	DWORD oldProtect = 0;
	VirtualProtect(ToPointer(Client::hWorld + Offsets::AntiCrash, void), 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	bool res = Memory::write<unsigned char>(Client::hWorld + Offsets::AntiCrash, 0x74);
	VirtualProtect(ToPointer(Client::hWorld + Offsets::AntiCrash, void), 1, oldProtect, nullptr);

	return res;
}

void Disabler::endBypass() {

	DWORD oldProtect = 0;
	VirtualProtect(ToPointer(Client::hWorld + Offsets::AntiCrash, void), 1, PAGE_EXECUTE_READWRITE, &oldProtect);
	Memory::write<unsigned char>(Client::hWorld + Offsets::AntiCrash, 0x75);
	VirtualProtect(ToPointer(Client::hWorld + Offsets::AntiCrash, void), 1, oldProtect, nullptr);
}
