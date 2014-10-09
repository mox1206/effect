#ifndef __EFFECTCELSHADING_H__
#define __EFFECTCELSHADING_H__

#include "Effect.h"

class EffectCelShading: public Effect
{
public:
	CREATE_FUNC(EffectCelShading);

	virtual void setTarget(EffectSprite *sprite);

protected:

	bool init();
};

#endif