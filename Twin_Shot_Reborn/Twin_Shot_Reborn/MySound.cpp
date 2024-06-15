#include "MySound.h"

#include <Windows.h>

#include "Resources/Library/inc/fmod.hpp"
#pragma comment (lib, "Resources/Library/lib/x64/fmod_vc.lib")

MySound::MySound()
{
	// ������ �ε� ���� ���̺귯�� ��� �� Dll Directory�� �������ش�.
	SetDllDirectoryA("Resources/Library/lib/x64");
	// ���̺귯�� üũ
	HMODULE hModule = LoadLibraryA("fmod.dll");
	if (hModule) {
		FreeLibrary(hModule);
	}
	else {
		MessageBoxA(nullptr, "fmod.dll�� ���� �ڵ� ������ ������ �� �����ϴ�. ���� ���ҽ��� �����ϼ���.", "�ý��� ����", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	// ���� �ý��� ����
	FMOD::System_Create(&ssystem);
	ssystem->init(32, FMOD_INIT_NORMAL, nullptr);

	backgroundChannel = nullptr;
	effectChannel = nullptr;
}

MySound::~MySound()
{
	ssystem->release();
}

MySound& MySound::getInstance()
{
	static MySound instance;
	return instance;
}
