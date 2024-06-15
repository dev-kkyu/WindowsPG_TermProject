#include "MySound.h"

#include <Windows.h>

#include "Resources/Library/inc/fmod.hpp"
#pragma comment (lib, "Resources/Library/lib/x64/fmod_vc.lib")

MySound::MySound()
{
	// 지연된 로드 이후 라이브러리 사용 전 Dll Directory를 변경해준다.
	SetDllDirectoryA("Resources/Library/lib/x64");
	// 라이브러리 체크
	HMODULE hModule = LoadLibraryA("fmod.dll");
	if (hModule) {
		FreeLibrary(hModule);
	}
	else {
		MessageBoxA(nullptr, "fmod.dll이 없어 코드 실행을 진행할 수 없습니다. 원본 리소스를 복구하세요.", "시스템 오류", MB_OK | MB_ICONERROR);
		exit(-1);
	}

	// 사운드 시스템 생성
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
