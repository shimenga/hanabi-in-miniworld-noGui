#pragma once
#include <Windows.h>

constexpr int CODE_LENGTH = 5;

class InlineHook {

private:

	// ԭʼָ���С
	BYTE s_originalBytes[CODE_LENGTH];

	// �Լ�����Ļ��ָ��
	BYTE s_newBytes[CODE_LENGTH];

	// ԭʼ������ַ
	DWORD s_originalAddress;

	// �Լ��ĺ�����ַ
	DWORD s_newAddress;

	DWORD ModifyMemoryAttributes(DWORD address, DWORD attributes = PAGE_EXECUTE_READWRITE);

public:

	InlineHook(DWORD originalFuncAddr, DWORD newFuncAddr);

	VOID MotifyASM();

	VOID ResetASM();
};
