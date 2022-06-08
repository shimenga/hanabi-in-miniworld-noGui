#include "Utility.h"

namespace Utility {

    static HWND wndGame = FindWindowA("RenderWindow_ClassName", nullptr);
	
    void openConsole() {

        AllocConsole();
        SetConsoleTitleW(L"Hanabi client inject success.(Author: °¢ÒðAyin)");
        freopen("CONOUT$", "w", stdout);
    }

    inline float PI() { return 3.1415926535f; }

    bool compareString(const char* _String1, const char* _String2) {
        return strcmp(_String1, _String2) == 0;
    }

    bool compareStringIgnoreCase(const char* _String1, const char* _String2) {
        return _stricmp(_String1, _String2) == 0;
    }

    bool compareString(std::string _String1, std::string _String2) {
        return Utility::compareString(_String1.c_str(), _String2.c_str());
    }

    bool compareStringIgnoreCase(std::string _String1, std::string _String2) {
        return Utility::compareStringIgnoreCase(_String1.c_str(), _String2.c_str());
    }

    void notice(const char* msg, Level lv) {
        
        if (lv == Level::INFO) {
            MessageBoxA(nullptr, msg, "Infomation from Hanabi:", MB_OK | MB_ICONINFORMATION);
            return;
        }

        if (lv == Level::ERR) {
            MessageBoxA(nullptr, msg, "Error from Hanabi:", MB_OK | MB_ICONERROR);
            return;
        }

        if (lv == Level::WARN) {
            MessageBoxA(nullptr, msg, "Warnning from Hanabi:", MB_OK | MB_ICONWARNING);
            return;
        }
    }

    float width() {
        RECT rect;
        RtlZeroMemory(&rect, sizeof(RECT));
        GetClientRect(wndGame, &rect);
        return static_cast<float>(rect.right - rect.left);
    }

    float height() {
        RECT rect;
        RtlZeroMemory(&rect, sizeof(RECT));
        GetClientRect(wndGame, &rect);
        return static_cast<float>(rect.bottom - rect.top);
    }

    bool isReadablePtr(void* pointer) {
        return (IsBadReadPtr(pointer, sizeof(pointer)) == 0);
    }

    bool isWriteablePtr(void* pointer) {
        return (IsBadWritePtr(pointer, sizeof(pointer)) == 0);
    }

    float getDistance2D(struct Vec2 from, struct Vec2 to) {

        Vec2 diff;
        diff.x = to.x - from.x;
        diff.y = to.y - from.y;

        return sqrt(diff.x * diff.x + diff.y * diff.y);

    }

    float getDistance3D(struct Vec3 from, struct Vec3 to) {

        Vec3 diff;
        diff.x = to.x - from.x;
        diff.y = to.y - from.y;
        diff.z = to.z - from.z;

        return sqrt(diff.x * diff.x + diff.y + diff.y + diff.z * diff.z);

    }

    bool worldToScreen(const float pvm[4][4], struct Vec3* target, struct Vec2* view, struct Vec2* screenPos) {

        float cameraZ = pvm[0][3] * target->x + pvm[1][3] * target->y + pvm[2][3] * target->z + pvm[3][3];
        if (cameraZ < 0.01f) return false;

        float scale = 1 / cameraZ;
        (*screenPos).x = view->x + (pvm[0][0] * target->x + pvm[1][0] * target->y + pvm[2][0] * target->z + pvm[3][0]) * scale * view->x;
        (*screenPos).y = view->y - (pvm[0][1] * target->x + pvm[1][1] * target->y + pvm[2][1] * target->z + pvm[3][1]) * scale * view->y;

        return true;
    }

    Vec2 calcAimAngle(struct Vec3* player, struct Vec3* target) {

        Vec2 result;
        Vec3 diff;
        diff.x =  target->x - player->x;
        diff.y =  target->z - player->z;
        diff.z =  target->y - player->y;

        if (diff.x >= 0 && diff.y >= 0)
            result.x = atanf(diff.x / diff.y) / PI() * 180;
        if (diff.x <= 0 && diff.y >= 0)
            result.x = 270 + atanf(diff.y / abs(diff.x)) / PI() * 180;
        if (diff.x <= 0 && diff.y <= 0)
            result.x = 180 + atanf(abs(diff.x) / abs(diff.y)) / PI() * 180;
        if (diff.x >= 0 && diff.y <= 0)
            result.x = 90 + atanf(abs(diff.y) / diff.x) / PI() * 180;

        result.y = -atanf(diff.z / sqrt(diff.x * diff.x + diff.y * diff.y)) / PI() * 180;

        return result;
    }

    float getStringLength(const char* _String, float fontScale) {
        
        return strlen(_String) * fontScale + 30;
    }

    float map(float in, float inMin, float inMax, float outMin, float outMax) {
        return (in - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
    }

}
