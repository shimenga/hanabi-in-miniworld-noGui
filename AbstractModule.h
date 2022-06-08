#pragma once
#include <string>
#include "NotificationManager.h"


#define ToggleCheck if (!this->getToggle()) return
#define DefaultConstructor(_Class) _Class() = default
#define DefaultDeconstructor(_Class) ~_Class() = default
#define NoMoveConstructor(_Class) _Class(_Class&&) = delete
#define NoCopyConstructor(_Class) _Class(const _Class&) = delete
#define NoAssignOperator(_Class) _Class& operator=(const _Class&) = delete

enum class Category : unsigned int {
	
	Render = 0,
	Combat,
	World,
	Movement,
	Player
};

class AbstractModule {

public:

	void toggle();
	void onToggled();
	std::string getName();
	bool getToggle();
	void setToggle(bool _New);
	void enable();
	void disable();
	Category getCategory();

	virtual void onEnabled() = 0;
	virtual void onDisabled() = 0;

	AbstractModule(std::string modName, Category modCategory);
	virtual ~AbstractModule() = default;
	AbstractModule(AbstractModule&& mod) = delete;
	AbstractModule(AbstractModule& other) = delete;
	AbstractModule& operator=(const AbstractModule& _New) = delete;

protected:
	std::string name;
	Category category;
	bool i_toggle;

};

