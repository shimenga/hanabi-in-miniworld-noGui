#include "Reach.h"

Reach::Reach() : AbstractModule("Reach", Category::Combat) {
	this->reachChecker.init(ToPointer(Client::hWorld + Offsets::Reach, unsigned char), 1);
}

Reach* Reach::getInstance() {
	static Reach* inst = new Reach();
	return inst;
}

void Reach::onEnabled() {
	IngameCheck;

	if (Fly::getInstance()->bypassAC()) {
		this->preGameMode = Game::theWorld->worldManager->mode;
		Game::theWorld->worldManager->mode = SDK::MODE_EDIT;
		this->startReach();
	}
	else {
		Utility::notice("�ƹ����з�����ʧ�ܣ����ǿ���ʹ�ô˹��ܣ��벻Ҫ˫���ո���з���", Level::ERR);
	}

}

void Reach::onDisabled() {
	IngameCheck;

	this->endReach();
	Game::theWorld->worldManager->mode = this->preGameMode;
	this->preGameMode = -1;
	Fly::getInstance()->resetAC();
}

bool Reach::startReach() {

	bool res = this->reachChecker.destroy();
	if (res)
		res = Memory::write<unsigned char>(Client::hWorld + Offsets::Reach, 0x74);

	return res;
}

void Reach::endReach() {

	this->reachChecker.restore();
	Memory::write<unsigned char>(Client::hWorld + Offsets::Reach, 0x75);
}
