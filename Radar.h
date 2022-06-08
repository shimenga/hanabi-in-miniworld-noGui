#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

class Radar : public AbstractModule {

public:

	static Radar* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	Vec2 scPos;
	bool center = true;
	float scale = 0.3f;

	Vec2 transformPos(Vec3 self, Vec3 target, float angle, float scale);

	Radar();
	DefaultDeconstructor(Radar);
	NoMoveConstructor(Radar);
	NoCopyConstructor(Radar);
	NoAssignOperator(Radar);

};

