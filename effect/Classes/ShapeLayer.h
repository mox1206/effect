#ifndef __SHAPELAYER_H__
#define __SHAPELAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class ShapeLayer: public Node
{
public:
	ShapeLayer();
	~ShapeLayer();

	static ShapeLayer* create(const std::string &filename);

	bool initWithFile(const std::string &filename);
	bool initListener();
	bool initStencil();

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);

	Vec2 getContactVec(Point p1, Point p2, Point p3, Point p4);
	void generateAllVertex(const Vec2& beginPoint, const Vec2 &endPoint);
	void setClippStencil();

private:
	Point		m_pStartPos;
	Node*		m_pOneSprite;
	Node*		m_pTwoSprite;
	ClippingNode* m_pClippOneNode;
	ClippingNode* m_pClippTwoNode;
	Vec2		m_pVertexArray[6];
	int			m_nOneIndex;
	int			m_nTwoIndex;
	DrawNode	*m_pOneStencil;
	DrawNode	*m_pTwoStencil;
};

#endif