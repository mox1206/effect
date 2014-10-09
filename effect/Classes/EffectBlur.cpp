#include "EffectBlur.h""

bool EffectBlur::init(float blurRadius, float sampleNum)
{
	this->initGLProgramState("Shaders/example_Blur.fsh");
	this->_blurRadius = blurRadius;
	this->_sampleNum = sampleNum;
	return true;
}

void EffectBlur::setTarget(EffectSprite* sprite)
{
	Size size = sprite->getTexture()->getContentSizeInPixels();
	_glprogramstate->setUniformVec2("resolution", size);
	_glprogramstate->setUniformFloat("blurRadius", _blurRadius);
	_glprogramstate->setUniformFloat("sampleNum", _sampleNum);
}

void EffectBlur::setBlurRadius(float blurRadius)
{
	this->_blurRadius = blurRadius;
}

void EffectBlur::setBlurSampleNum(float sampleNum)
{
	this->_sampleNum = sampleNum;
}