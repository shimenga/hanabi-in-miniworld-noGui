#pragma once

#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"
#include "NotificationManager.h"

class Disabler : public AbstractModule {

public:

	static Disabler* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();
	void bypassError();

	bool startBypass();
	void endBypass();

private:

	Disabler();
	DefaultDeconstructor(Disabler);
	NoMoveConstructor(Disabler);
	NoCopyConstructor(Disabler);
	NoAssignOperator(Disabler);

};

