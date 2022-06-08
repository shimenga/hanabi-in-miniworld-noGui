#pragma once
#include "AbstractModule.h"
#include <vector>
#include <algorithm>
#include "EventManager.h"
#include "ImGuiHeader.h"
#include "Game.h"

class FillBright : public AbstractModule {
public:
	static FillBright* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();
private:

	FillBright();
	DefaultDeconstructor(FillBright);
	NoMoveConstructor(FillBright);
	NoCopyConstructor(FillBright);
	NoAssignOperator(FillBright);
};