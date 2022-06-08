#include "FillBright.h"

FillBright::FillBright() :AbstractModule("FillBright", Category::Render) {
    EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &FillBright::onRenderOverlay));
}

FillBright* FillBright::getInstance()
{
    static FillBright* inst = new FillBright();
    return inst;
}

void FillBright::onEnabled()
{
    unsigned char data1[13] = { 0xC7 ,0x47 ,0x38 ,0x1F ,0x85 ,0x2B ,0x70 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 };
    unsigned char data2[13] = { 0xC7 ,0x47 ,0x3C ,0x1F ,0x85 ,0x2B ,0x70 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 };
    unsigned char data3[12] = { 0xC7 ,0x47 ,0x40 ,0x1F ,0x85 ,0x2B ,0x70 ,0x90 ,0x90 ,0x90 ,0x90 ,0x90 };
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::FillBright1), data1, 13, nullptr);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::FillBright2), data2, 13, nullptr);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::FillBright3), data3, 12, nullptr);
}

void FillBright::onDisabled()
{
    unsigned char data1[13] = { 0xF3 ,0x0F ,0x11 ,0x47 ,0x38 ,0xF3 ,0x0F ,0x10 ,0x86 ,0x04 ,0x01 ,0x00 ,0x00 };
    unsigned char data2[13] = { 0xF3 ,0x0F ,0x11 ,0x47 ,0x3C ,0xF3 ,0x0F ,0x10 ,0x86 ,0x08 ,0x01 ,0x00 ,0x00 };
    unsigned char data3[12] = { 0xF3 ,0x0F ,0x11 ,0x47 ,0x40 ,0x80 ,0xBE ,0xC0 ,0x00 ,0x00 ,0x00 ,0x00 };
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::FillBright1), data1, 13, nullptr);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::FillBright2), data2, 13, nullptr);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(Client::hWorld + Offsets::FillBright3), data3, 12, nullptr);
}

void FillBright::onRenderOverlay()
{
}
