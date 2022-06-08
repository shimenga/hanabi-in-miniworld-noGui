#pragma once
#include <Windows.h>

namespace Memory {
	
	class ProtectDestroyer {

	public:
		void init(void* address, size_t size);
		bool destroy();
		void restore();

	private:
		void* address;
		size_t size;
		unsigned long originalProtect;

	};

}


