#include "EffectGray.h"

bool EffectGray::init()
{
	this->initGLProgramState("Shaders/example_greyScale.fsh");
	return true;
}

void EffectGray::setTarget(EffectSprite* sprite)
{
}