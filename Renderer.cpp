#include "Renderer.h"

// ImGui���ڴ�����
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Renderer {

    // ȫ�ֱ���
    WNDPROC originalWndProc = nullptr;      // ��Ϸ����Ĵ��ڴ�����

    // Hooks
    InlineHook* resetHook = nullptr;
    InlineHook* presentHook = nullptr;

    void initImGui(HWND hwnd, IDirect3DDevice9* device) {
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // �����������ļ�
        io.IniFilename = nullptr;
        io.LogFilename = nullptr;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        ImGui::StyleColorsLight();

        // ����(��һ����ӵ���Ĭ������)
        char buffer[1024];
        RtlZeroMemory(buffer, 1024);
        strcpy(buffer, Client::clientAssetsPath.c_str());
        strcat(buffer, "font\\SYFont.ttf");
        Client::defaultFont = io.Fonts->AddFontFromFileTTF(buffer, 13, nullptr, io.Fonts->GetGlyphRangesChineseFull());

        RtlZeroMemory(buffer, 1024);
        strcpy(buffer, Client::clientAssetsPath.c_str());
        strcat(buffer, "font\\HanabiFont.ttf");
        Client::hanabiFont = io.Fonts->AddFontFromFileTTF(buffer, 17.5f, nullptr);

        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX9_Init(device);
    }

	bool hookDx9(HWND hwnd) {
		
        // ����D3D
        IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (direct3D9 == nullptr) {
            MessageBoxA(nullptr, "Direct3DCreate9 failed.", "Error:", MB_OK | MB_ICONERROR);
            return false;
        }

        D3DPRESENT_PARAMETERS info;
        memset(&info, 0, sizeof(info));
        info.Windowed = true;
        info.SwapEffect = D3DSWAPEFFECT_COPY;

        // �����豸��Ϊ���ú�����ַ��Hook
        IDirect3DDevice9* direct3DDevice9 = nullptr;
        direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &info, &direct3DDevice9);
        if (direct3DDevice9 == nullptr) {
            MessageBoxA(nullptr, "CreateDevice failed.", "Error:", MB_OK | MB_ICONERROR);
            return false;
        }

        // Hook Direct3D
        DWORD* direct3DDeviceTable = (DWORD*)*(DWORD*)direct3DDevice9;
        resetHook = new InlineHook(direct3DDeviceTable[16], reinterpret_cast<DWORD> (Hook_Reset));
        presentHook = new InlineHook(direct3DDeviceTable[17], reinterpret_cast<DWORD> (Hook_Present));
        resetHook->MotifyASM();
        presentHook->MotifyASM();

        // �����豸����Ϊ�õ���ַ��
        direct3D9->Release();
        direct3DDevice9->Release();

        return true;

	}

	bool startRenderer(HWND hwnd) {

        bool res = true;

		res = hookDx9(hwnd);

        return res;
	}

    // Simple helper function to load an image into a DX9 texture with common settings
    bool loadTextureFromFile(IDirect3DDevice9* device, const char* filename, Picture* pic) {

        // Load texture from disk
        PDIRECT3DTEXTURE9 texture;
        HRESULT hr = D3DXCreateTextureFromFileA(device, filename, &texture);
        if (hr != S_OK)
            return false;

        // Retrieve description of the texture surface so we can access its size
        D3DSURFACE_DESC my_image_desc;
        texture->GetLevelDesc(0, &my_image_desc);
        pic->texture = texture;
        pic->width = (int)my_image_desc.Width;
        pic->height = (int)my_image_desc.Height;

        return true;
    }

    bool isBlockHovered(Block* block) {
        
        return Client::rendererIO->MousePos.x > block->x &&
        Client::rendererIO->MousePos.y > block->y &&
        Client::rendererIO->MousePos.x < (block->x + block->width) &&
        Client::rendererIO->MousePos.y < (block->y + block->height);
    }

    void drawBlockBoundingBox(Block* block) {
        ImGui::GetForegroundDrawList()->AddRect(ImVec2(block->x, block->y), ImVec2(block->x + block->width, block->y + block->height), IM_COL32(255, 0, 0, 230));
    }

    bool isBlockClicked(Block* block) {
        if (isBlockHovered(block)) {
            return ImGui::IsMouseClicked(0);
        }
        return false;
    }

    bool isBlockInAnotherBlock(Block* subBlock, Block* superBlock) {

        int x1 = subBlock->x + subBlock->width;
        int y1 = subBlock->y + subBlock->height;
        
        return subBlock->x > superBlock->x &&
            subBlock->y > superBlock->y &&
            subBlock->x < (superBlock->x + superBlock->width) &&
            subBlock->y < (superBlock->y + superBlock->height) &&
            x1 > superBlock->x &&
            y1 > superBlock->y &&
            x1 < (superBlock->x + superBlock->width) &&
            y1 < (superBlock->y + superBlock->height);
        

    }

    void addBlockBoundingBox(Block* subBlock, int xInc, int yInc, int wInc, int hInc) {
        
        subBlock->x -= xInc;
        subBlock->y -= yInc;
        subBlock->width += xInc + wInc;
        subBlock->height += yInc + hInc;
    }

    // Hooked function implements
    HRESULT WINAPI Hook_Reset(IDirect3DDevice9* direct3DDevice9, D3DPRESENT_PARAMETERS* pPresentationParameters) {

        resetHook->ResetASM();

        // �ϳ��豸����
        ImGui_ImplDX9_InvalidateDeviceObjects();

        HRESULT res = direct3DDevice9->Reset(pPresentationParameters);

        // ���´����豸����
        ImGui_ImplDX9_CreateDeviceObjects();

        resetHook->MotifyASM();

        return res;
    }

    HRESULT WINAPI Hook_Present(IDirect3DDevice9* direct3DDevice9, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion) {

        presentHook->ResetASM();

        static bool called = false;
        if (!called) {

            called = true;

            // ��ʼ��ImGui
            initImGui(Client::wndGame, direct3DDevice9);

            // �ӹܴ�����Ϣ
            Renderer::originalWndProc = reinterpret_cast<WNDPROC> (SetWindowLongA(Client::wndGame, GWL_WNDPROC, reinterpret_cast<long> (SelfWndProc)));
        
            // ��ʼ��RendererIO
            Client::rendererIO = &(ImGui::GetIO());

            // ��ʼ��Textures
            Client::loadTextures(direct3DDevice9);
        }

        // ����
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        EventManager::getInstance().call(Events::EventKeyDown);
        EventManager::getInstance().call(Events::EventUpdateData);
        EventManager::getInstance().call(Events::EventUpdate);
        EventManager::getInstance().call(Events::EventRenderOverlay);
        
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

        HRESULT res = direct3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

        presentHook->MotifyASM();

        // ����ԭ����
        return res;
    }

    LRESULT CALLBACK SelfWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        // ImGui�ӹܴ��ڴ���
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;

        // ����ԭ�ȵĴ��ڴ���
        return CallWindowProcA(Renderer::originalWndProc, hWnd, uMsg, wParam, lParam);
    }

}
