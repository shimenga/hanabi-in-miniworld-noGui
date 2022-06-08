#pragma once
#include <vector>
#include <algorithm>
#include "AbstractModule.h"
#include "EventManager.h"
#include "ImGuiHeader.h"
#include "Game.h"

class HUD : public AbstractModule {

public:

	static HUD* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	std::vector<HMOD> enabledMods;

	HUD();
	DefaultDeconstructor(HUD);
	NoMoveConstructor(HUD);
	NoCopyConstructor(HUD);
	NoAssignOperator(HUD);

};

class EnabledListSorter {

public:
	bool operator()(HMOD m1, HMOD m2);
};

