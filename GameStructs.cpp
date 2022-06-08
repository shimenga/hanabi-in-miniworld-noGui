#include "GameStructs.h"

namespace SDK {

	static Address hWorld = reinterpret_cast<Address>(GetModuleHandleA("libiworld_micro.dll"));

	World* getWorld() {

		Address* pWorld = reinterpret_cast<Address*>(hWorld + Offsets::World);
		World* world = reinterpret_cast<World*>(*pWorld);
		if (IsBadReadPtr(world, sizeof(world)) == 0 && reinterpret_cast<Address>(world) != 0)
			return world;
		return nullptr;
	}

	UIRenderer* getUIRenderer() {
		
		DWORD* pUIRenderer = reinterpret_cast<DWORD*>(hWorld + Offsets::UIRenderer);
		UIRenderer* renderer = reinterpret_cast<UIRenderer*>(*pUIRenderer);
		if (IsBadReadPtr(renderer, sizeof(renderer)) == 0 && reinterpret_cast<Address>(renderer) != 0)
			return renderer;
		return nullptr;
	}

}
