#include "SoundEvent.h"



SoundEvent::SoundEvent()
{
}


SoundEvent::~SoundEvent()
{

}

void SoundEvent::SetLoopForever()
{
	audioBuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
}
