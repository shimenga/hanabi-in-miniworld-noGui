#pragma once
#include "AbstractModule.h"
#include "Game.h"
#include "EventManager.h"


class HighJump : public AbstractModule {

public:

	static HighJump* getInstance();

	void onEnabled();
	void onDisabled();

	void onUpdate();

private:

	HighJump();
	DefaultDeconstructor(HighJump);
	NoMoveConstructor(HighJump);
	NoCopyConstructor(HighJump);
	NoAssignOperator(HighJump);

};

