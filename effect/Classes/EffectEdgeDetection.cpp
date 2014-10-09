#include "EffectEdgeDetection.h"

bool EffectEdgeDetection::init()
{
	this->initGLProgramState("Shaders/example_edgeDetection.fsh");
	return true;
}

void EffectEdgeDetection::setTarget(EffectSprite* sprite)
{
	Size size = sprite->getTexture()->getContentSizeInPixels();
	_glprogramstate->setUniformVec2("resolution", size);
}
