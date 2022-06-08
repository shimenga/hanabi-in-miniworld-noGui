#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"


class Aimbot : public AbstractModule {

public:

	float aimRange = 190;
	float headOffset = 130;

	static Aimbot* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	Aimbot();
	DefaultDeconstructor(Aimbot);
	NoMoveConstructor(Aimbot);
	NoCopyConstructor(Aimbot);
	NoAssignOperator(Aimbot);

};

class AimbotDisSorter {

public:
	bool operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2);
};

class AimbotScreenDisSorter {

public:
	bool operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2);
};
