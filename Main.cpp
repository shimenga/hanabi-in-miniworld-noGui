#include <Windows.h>
#include "Client.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	
	if (dwReason == DLL_PROCESS_ATTACH) {
		MakeDisposableThread(Client::startClient, hModule);
	}

	return TRUE;
}
