#pragma once
#include <Windows.h>
#include "ImGuiHeader.h"
#include "InlineHook.h"
#include "Client.h"
#include "EventManager.h"

struct Picture {

	IDirect3DTexture9* texture;
	int						width;
	int						height;

};

struct Block {

	float x;
	float y;
	float width;
	float height;
};

namespace Renderer {

	// ȫ�ֱ���
	extern WNDPROC originalWndProc;      // ��Ϸ����Ĵ��ڴ�����

	// Hooks
	extern InlineHook* resetHook;
	extern InlineHook* presentHook;

	void initImGui(HWND hwnd, IDirect3DDevice9* device);

	bool hookDx9(HWND hwnd);
	
	bool startRenderer(HWND hwnd);

	bool loadTextureFromFile(IDirect3DDevice9* device, const char* filename, Picture* pic);

	bool isBlockHovered(Block* block);

	void drawBlockBoundingBox(Block* block);

	bool isBlockClicked(Block* block);

	bool isBlockInAnotherBlock(Block* subBlock, Block* superBlock);

	void addBlockBoundingBox(Block* subBlock, int xInc, int yInc, int wInc, int hInc);

	// �Լ��Ĵ��ڴ�����
	LRESULT CALLBACK SelfWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Hooked functions
	HRESULT WINAPI Hook_Reset(IDirect3DDevice9* direct3DDevice9, D3DPRESENT_PARAMETERS* pPresentationParameters);
	HRESULT WINAPI Hook_Present(IDirect3DDevice9* direct3DDevice9, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion);

}

