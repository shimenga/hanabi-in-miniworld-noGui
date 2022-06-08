#pragma once
#include <iostream>
#include <Windows.h>
#include "Structs.h"


enum class Level : unsigned int {

	INFO = 0,
	ERR,
	WARN
};

namespace Utility {

	void openConsole();

	bool compareString(const char* _String1, const char* _String2);

	bool compareStringIgnoreCase(const char* _String1, const char* _String2);

	bool compareString(std::string _String1, std::string _String2);

	bool compareStringIgnoreCase(std::string _String1, std::string _String2);

	void notice(const char* msg, Level lv = Level::INFO);

	float width();

	float height();

	bool isReadablePtr(void* pointer);

	bool isWriteablePtr(void* pointer);

	float getDistance2D(Vec2 from, Vec2 to);

	float getDistance3D(Vec3 from, Vec3 to);

	bool worldToScreen(const float pvm[4][4], Vec3* target, Vec2* view, Vec2* screenPos);

	Vec2 calcAimAngle(Vec3* player, Vec3* target);

	float getStringLength(const char* _String, float fontScale);

	float map(float in, float inMin, float inMax, float outMin, float outMax);

}
