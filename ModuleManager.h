#pragma once
#include <iostream>
#include <vector>
#include "AbstractModule.h"

#define ToBaseModule(_Mod) reinterpret_cast<AbstractModule*>(_Mod)
#define ToDirectModule(_Impl, _Mod) reinterpret_cast<_Impl*>(_Mod)

typedef void* HMOD;

class ModuleManager {
	
public:

	static ModuleManager& getInstance();

	template<class MODCLASS>
	void addModule(MODCLASS* mod);

	template <class MODCLASS>
	MODCLASS* getModule(std::string modName);

	void getModule(Category c, std::vector<HMOD>* out_modules);
	void getModule(bool enabled, std::vector<HMOD>* out_modules);

	ModuleManager(ModuleManager&&) = delete;
	ModuleManager(const ModuleManager&) = delete;
	ModuleManager& operator=(const ModuleManager&) = delete;

private:

	std::vector<HMOD> modules;

	ModuleManager();
	~ModuleManager() = default;
};

template<class MODCLASS>
void ModuleManager::addModule(MODCLASS* mod) {
	this->modules.push_back(reinterpret_cast<HMOD>(mod));
}

template<class MODCLASS>
MODCLASS* ModuleManager::getModule(std::string modName) {

	for (auto iter = this->modules.cbegin(); iter < this->modules.cend(); iter++) {

		if (::compareStringIgnoreCase(ToBaseModule(*iter)->getName(), modName))
			return ToDirectModule(MODCLASS, *iter);
	}

	return nullptr;
}


