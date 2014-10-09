#include "EffectBloom.h"

bool EffectBloom::init()
{
	this->initGLProgramState("Shaders/example_bloom.fsh");
	return true;
}

void EffectBloom::setTarget(EffectSprite* sprite)
{
	
}
