#pragma once
#include "AbstractModule.h"
#include "EventManager.h"
#include "Utility.h"
#include "ImGuiHeader.h"
#include "Game.h"

#define TeamCheck Team::getInstance()->getToggle()

class Team : public AbstractModule {

public:

	static Team* getInstance();

	void onEnabled();
	void onDisabled();

private:

	Team();
	DefaultDeconstructor(Team);
	NoMoveConstructor(Team);
	NoCopyConstructor(Team);
	NoAssignOperator(Team);

};

