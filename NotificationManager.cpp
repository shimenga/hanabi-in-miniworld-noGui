#include "NotificationManager.h"

NotificationManager::NotificationManager() : startX(0), startY(500), cleanInterval(6000) {
	
	this->notifications.clear();
	this->cleanTimer.reset();
	EventManager::getInstance().reg(Events::EventRenderOverlay, MakeHandler(this, &NotificationManager::render));
}

NotificationManager& NotificationManager::getInstance() {
	static NotificationManager inst;
	return inst;
}

void NotificationManager::makeNotification(std::string text, Type type) {
	Notification n(text, type);
	this->addNotification(n);
}

void NotificationManager::addNotification(Notification n) {
	this->notifications.push_back(n);
	this->cleanTimer.reset();
}

void NotificationManager::render() {

	if (this->notifications.empty()) return;
	
	int i = 0;
	IDirect3DTexture9* icon = nullptr;
	for (Notification& n : this->notifications) {

		switch (n.getType()) {
			
		case Type::INFO:
			icon = this->iconInfo;
			break;

		case Type::EXCEPTION:
			icon = this->iconErr;
			break;

		case Type::SUCCESS:
			icon = this->iconSucc;
			break;

		case Type::WARNNING:
			icon = this->iconWarn;
			break;
		}

		if (n.isRendering()) {
			n.render(icon, i, this->startX, this->startY);
			++i;
		}
	}

	if (this->cleanTimer.elapsed(this->cleanInterval)) {
		this->clearNotifications();
		this->cleanTimer.reset();
	}
	
}

void NotificationManager::clearNotifications() {
	this->notifications.clear();
}

void NotificationManager::setIcon(IDirect3DTexture9* info, IDirect3DTexture9* err, IDirect3DTexture9* succ, IDirect3DTexture9* warn) {
	this->iconInfo = info;
	this->iconErr = err;
	this->iconSucc = succ;
	this->iconWarn = warn;
}
