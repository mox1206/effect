#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"
USING_NS_CC;

class EffectSprite;

class Effect: public Ref
{
public:
	GLProgramState* getGLProgramState() const { return _glprogramstate; }
	virtual void setTarget(EffectSprite* sprite){}
protected:
	bool initGLProgramState(const std::string &fragmentFilename);
	bool initGLProgramState(const std::string &vertexFilename, const std::string &fragmentFilename);
	Effect();
	virtual ~Effect();

protected:
	GLProgramState* _glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string _fragSource;
	EventListenerCustom* _backgroundListener;
#endif
};

class EffectSprite : public Sprite
{
public:
	static EffectSprite* create(const std::string &filename);

	void setEffect(Effect* effect);

	void addEffect(Effect* effect, ssize_t order);

	virtual void draw(Renderer *render, const Mat4& transform, uint32_t flags);

protected:
	EffectSprite() :_defaultEffect(nullptr)
	{
		_effects.reserve(2);
	}
	~EffectSprite()
	{
		for (auto &tuple : _effects)
		{
			std::get<1>(tuple)->release();
		}
		CC_SAFE_RELEASE(_defaultEffect);
	}

	std::vector<std::tuple<ssize_t, Effect*, QuadCommand>> _effects;
	Effect*	 _defaultEffect;
};

#endif