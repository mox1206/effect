#ifndef __EFFECTBLOOM_H__
#define __EFFECTBLOOM_H__

#include "Effect.h"

class EffectBloom: public Effect
{
public:
	CREATE_FUNC(EffectBloom);

	virtual void setTarget(EffectSprite *sprite);

protected:

	bool init();
};

#endif