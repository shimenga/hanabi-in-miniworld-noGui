#include "AbstractModule.h"

AbstractModule::AbstractModule(std::string modName, Category modCategory) : name(modName), category(modCategory), i_toggle(false) {}

std::string AbstractModule::getName() {
	return this->name;
}

bool AbstractModule::getToggle() {
	return this->i_toggle;
}

void AbstractModule::setToggle(bool _New) {

	if (_New == this->i_toggle) return;
	this->i_toggle = _New;
	this->onToggled();
}

void AbstractModule::enable() {
	this->setToggle(true);
}

void AbstractModule::disable() {
	this->setToggle(false);
}

Category AbstractModule::getCategory() {
	return this->category;
}

void AbstractModule::toggle() {
	this->i_toggle = !this->i_toggle;
	this->onToggled();
}

void AbstractModule::onToggled() {
	if (this->i_toggle) {
		onEnabled();
		NotificationManager::getInstance().makeNotification(this->getName() + std::string(" Enabled."), Type::SUCCESS);
	}
	else {
		onDisabled();
		NotificationManager::getInstance().makeNotification(this->getName() + std::string(" Disabled."), Type::SUCCESS);
	}
}
