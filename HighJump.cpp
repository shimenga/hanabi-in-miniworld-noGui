#include "HighJump.h"

HighJump::HighJump() : AbstractModule("HighJump", Category::Movement) {
	
	EventManager::getInstance().reg(Events::EventUpdate, MakeHandler(this, &HighJump::onUpdate));
}

HighJump* HighJump::getInstance() {
	static HighJump* inst = new HighJump();
	return inst;
}

void HighJump::onEnabled() {

	if (Game::isPlaying())
		Game::thePlayer->setJumpHeight(75);
}

void HighJump::onDisabled() {

	if (Game::isPlaying())
		Game::thePlayer->setJumpHeight(-1);
}

void HighJump::onUpdate() {
	ToggleCheck;
	IngameCheck;

	if (Game::thePlayer->getJumpHeight() != 75)
		Game::thePlayer->setJumpHeight(75);

}
