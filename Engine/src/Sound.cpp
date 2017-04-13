#include "Sound.h"
#include "Resources.h"

Sound::Sound(): sound(nullptr), channel(-1)
{
}
Sound::Sound(string file): sound(nullptr), channel(-1)
{
	Open(file);
}
void Sound::Play(int times)
{
	channel= Mix_PlayChannel(-1, sound.get(), times-1);
}
void Sound::Stop(void)
{
	Mix_HaltChannel(channel);
}
void Sound::Open(string file)
{
	sound= Resources::GetSound(file);
}
bool Sound::IsOpen(void)
{
	return sound != nullptr;
}
