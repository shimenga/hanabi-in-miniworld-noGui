#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "MouseSimulator.h"


class AutoClicker : public AbstractModule {

public:

	static AutoClicker* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	TimerUtil cpsTimer;
	int cps = 8;
	bool start = false;

	AutoClicker();
	DefaultDeconstructor(AutoClicker);
	NoMoveConstructor(AutoClicker);
	NoCopyConstructor(AutoClicker);
	NoAssignOperator(AutoClicker);

};

