#include "MySound.h"

#include <Windows.h>

#include <string>

#include "Resources/Library/inc/fmod.hpp"
#pragma comment (lib, "Resources/Library/lib/x64/fmod_vc.lib")

MySound::MySound()
	: sounds{}
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

	loadSoundFiles();
}

MySound::~MySound()
{
	ssystem->release();
}

void MySound::loadSoundFiles()
{
	std::string filename[]{ "bgm_lobby", "bgm_normal", "bgm_boss", "jump",
		"shoot", "shoot_wall", "shoot_monster", "attacked", "item", "silver_coin", "gold_coin" };
	for (int i = 0; i < 11; ++i) {
		std::string name = "./Resources/Sounds/" + filename[i] + ".mp3";
		if (i < 3)
			ssystem->createSound(name.c_str(), FMOD_LOOP_NORMAL, nullptr, &sounds[i]);
		else
			ssystem->createSound(name.c_str(), FMOD_DEFAULT, nullptr, &sounds[i]);
	}
}

MySound& MySound::getInstance()
{
	static MySound instance;
	return instance;
}

void MySound::playLobbyBGM()
{
	if (backgroundChannel)
		backgroundChannel->stop();
	ssystem->playSound(sounds[0], nullptr, false, &backgroundChannel);
}

void MySound::playNormalBGM()
{
	if (backgroundChannel)
		backgroundChannel->stop();
	ssystem->playSound(sounds[1], nullptr, false, &backgroundChannel);
}

void MySound::playBossBGM()
{
	if (backgroundChannel)
		backgroundChannel->stop();
	ssystem->playSound(sounds[2], nullptr, false, &backgroundChannel);
}

void MySound::playJumpSound()
{
	ssystem->playSound(sounds[3], nullptr, false, nullptr);
}

void MySound::playShootSound()
{
	ssystem->playSound(sounds[4], nullptr, false, nullptr);
}

void MySound::playShootWallSound()
{
	ssystem->playSound(sounds[5], nullptr, false, nullptr);
}

void MySound::playShootMonsterSound()
{
	ssystem->playSound(sounds[6], nullptr, false, nullptr);
}

void MySound::playAttackedSound()
{
	ssystem->playSound(sounds[7], nullptr, false, nullptr);
}

void MySound::playItemSound()
{
	ssystem->playSound(sounds[8], nullptr, false, nullptr);
}

void MySound::playSilverCoinSound()
{
	ssystem->playSound(sounds[9], nullptr, false, nullptr);
}

void MySound::playGoldCoinSound()
{
	ssystem->playSound(sounds[10], nullptr, false, nullptr);
}
