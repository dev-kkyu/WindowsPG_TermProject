#pragma once

namespace FMOD
{
	class System;
	class Channel;
}

class MySound
{
private:
	FMOD::System* ssystem;

	FMOD::Channel* backgroundChannel;
	FMOD::Channel* effectChannel;

private:
	// ΩÃ±€≈Ê
	MySound();
	~MySound();

	MySound(const MySound&) = delete;
	MySound& operator=(const MySound&) = delete;

public:
	static MySound& getInstance();

public:

};

