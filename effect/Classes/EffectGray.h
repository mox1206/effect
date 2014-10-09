#ifndef __EFFECTGRAY_H__
#define __EFFECTGRAY_H__

#include "Effect.h"

class EffectGray: public Effect
{
public:
	CREATE_FUNC(EffectGray);

	virtual void setTarget(EffectSprite *sprite);

protected:
	bool init();
};

#endif