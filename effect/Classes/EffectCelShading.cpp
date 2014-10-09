#include "EffectCelShading.h"

bool EffectCelShading::init()
{
	this->initGLProgramState("Shaders/example_celShading.fsh");
	return true;
}

void EffectCelShading::setTarget(EffectSprite* sprite)
{
	Size size = sprite->getTexture()->getContentSizeInPixels();
	_glprogramstate->setUniformVec2("resolution", size);
}