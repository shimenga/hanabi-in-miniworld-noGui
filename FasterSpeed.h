#pragma once

#include "AbstractModule.h"
#include "Game.h"
#include "EventManager.h"


class FasterSpeed : public AbstractModule {

public:

	static FasterSpeed* getInstance();

	void onEnabled();
	void onDisabled();

	void onUpdate();

private:

	FasterSpeed();
	DefaultDeconstructor(FasterSpeed);
	NoMoveConstructor(FasterSpeed);
	NoCopyConstructor(FasterSpeed);
	NoAssignOperator(FasterSpeed);

};

