#pragma once
#include <string>
#include "ImGuiHeader.h"
#include "Colors.h"
#include "TimerUtil.h"
#include "Utility.h"
#include "Animation.h"

enum class Type : unsigned int {
	SUCCESS = 0,
	EXCEPTION,
	WARNNING,
	INFO
};

class Notification {

public:

	Notification(std::string text, Type type);

	void render(IDirect3DTexture9*  icon, int index, float x, float y);
	clock_t getTime();
	bool isRendering();
	Type getType();
	std::string getText();

private:

	std::string text;
	Type type;
	clock_t start;
	clock_t end;

};

