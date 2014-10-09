#ifndef __EFFECTEDGEDETECTION_H__
#define __EFFECTEDGEDETECTION_H__

#include "Effect.h"

class EffectEdgeDetection: public Effect
{
public:
	CREATE_FUNC(EffectEdgeDetection);

	virtual void setTarget(EffectSprite *sprite);
	
protected:
	bool init();
};

#endif