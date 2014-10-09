#ifndef __EFFECTBLUR_H__
#define __EFFECTBLUR_H__

#include "cocos2d.h"
#include "Effect.h"
USING_NS_CC;

class EffectBlur: public Effect
{
public:
	CREATE_FUNC(EffectBlur);
	virtual void setTarget(EffectSprite *sprite);
	void setBlurRadius(float radius);
	void setBlurSampleNum(float num);

protected:
	bool init(float blurRadius = 10.0f, float sampleNum = 5.0f);

protected:
	float _blurRadius;
	float _sampleNum;
};

#endif