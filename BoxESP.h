#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

class BoxESP : public AbstractModule {

public:

	static BoxESP* getInstance();

	void onEnabled();
	void onDisabled();

	void onRenderOverlay();

private:

	float radius = 65;
	float headOffset = 190;
	float sightLength = 300;
	float sightXOffset = 125;

	Vec3 rotatePointYaw(Vec3 opc, float radius, float angle);
	Vec3 rotatePointPitch(Vec3 opc, float radius, float angle);

	BoxESP();
	DefaultDeconstructor(BoxESP);
	NoMoveConstructor(BoxESP);
	NoCopyConstructor(BoxESP);
	NoAssignOperator(BoxESP);

};
