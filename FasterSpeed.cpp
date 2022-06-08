#include "FasterSpeed.h"

FasterSpeed::FasterSpeed() : AbstractModule("FasterSpeed", Category::Movement) {

	EventManager::getInstance().reg(Events::EventUpdate, MakeHandler(this, &FasterSpeed::onUpdate));
}

FasterSpeed* FasterSpeed::getInstance() {
	static FasterSpeed* inst = new FasterSpeed();
	return inst;
}

void FasterSpeed::onEnabled() {

	if (Game::isPlaying()) {
		
		Game::thePlayer->setWalkSpeed(22);
		Game::thePlayer->setRunSpeed(22);
		Game::thePlayer->setSneakSpeed(22);
		Game::thePlayer->setSwimSpeed(22);
	}
		
}

void FasterSpeed::onDisabled() {

	if (Game::isPlaying()) {
		
		Game::thePlayer->setWalkSpeed(-1);
		Game::thePlayer->setRunSpeed(-1);
		Game::thePlayer->setSneakSpeed(-1);
		Game::thePlayer->setSwimSpeed(-1);
	}
		
}

void FasterSpeed::onUpdate() {
	ToggleCheck;
	IngameCheck;
	
	if (Game::thePlayer->getWalkSpeed() != 22)
		Game::thePlayer->setWalkSpeed(22);

	if (Game::thePlayer->getRunSpeed() != 22)
		Game::thePlayer->setRunSpeed(22);

	if (Game::thePlayer->getSneakSpeed() != 22)
		Game::thePlayer->setSneakSpeed(22);

	if (Game::thePlayer->getSwimSpeed() != 22)
		Game::thePlayer->setSwimSpeed(22);

}
