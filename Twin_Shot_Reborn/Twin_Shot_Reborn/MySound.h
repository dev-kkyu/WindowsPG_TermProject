#pragma once

#include <array>

namespace FMOD
{
	class System;
	class Channel;
	class Sound;
}

class MySound
{
private:
	FMOD::System* ssystem;

	FMOD::Channel* backgroundChannel;
	FMOD::Channel* effectChannel;

	std::array<FMOD::Sound*, 11> sounds;

private:
	// ΩÃ±€≈Ê
	MySound();
	~MySound();

	MySound(const MySound&) = delete;
	MySound& operator=(const MySound&) = delete;

private:
	void loadSoundFiles();

public:
	static MySound& getInstance();

public:
	void playLobbyBGM();
	void playNormalBGM();
	void playBossBGM();
	void playJumpSound();
	void playShootSound();
	void playShootWallSound();
	void playShootMonsterSound();
	void playAttackedSound();
	void playItemSound();
	void playSilverCoinSound();
	void playGoldCoinSound();

};

