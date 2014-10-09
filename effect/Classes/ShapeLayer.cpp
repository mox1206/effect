#include "ShapeLayer.h"


ShapeLayer::ShapeLayer()
:m_nOneIndex(-1),
m_nTwoIndex(-1)
{
}


ShapeLayer::~ShapeLayer()
{
}

ShapeLayer* ShapeLayer::create(const std::string &filename)
{
	auto shapeLayer = new (std::nothrow) ShapeLayer;
	if (shapeLayer && shapeLayer->initWithFile(filename))
	{
		shapeLayer->autorelease();
		return shapeLayer;
	}
	CC_SAFE_RELEASE(shapeLayer);
	return nullptr;
}

bool ShapeLayer::initWithFile(const std::string &filename)
{
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
	if (!spriteFrame)
	{
		this->m_pOneSprite = Sprite::create(filename);
		this->m_pTwoSprite = Sprite::create(filename);
	}
	else
	{
		this->m_pOneSprite = Sprite::createWithSpriteFrameName(filename);
		this->m_pTwoSprite = Sprite::createWithSpriteFrameName(filename);
	}

	this->initListener();
	this->initStencil();

	return true;
}

bool ShapeLayer::initStencil()
{
	Size winSize = Director::getInstance()->getWinSize();

	Size contentSize = this->m_pOneSprite->getContentSize();
	Vec2 boxbounding[4] = {
		Vec2(-contentSize.width / 2, -contentSize.height / 2),
		Vec2(contentSize.width / 2, -contentSize.height / 2),
		Vec2(contentSize.width / 2, contentSize.height / 2),
		Vec2(-contentSize.width / 2, contentSize.height / 2)
	};
	this->m_pOneStencil = DrawNode::create();
	this->m_pOneStencil->retain();
	static Color4F green(0, 1, 0, 1);
	m_pOneStencil->drawPolygon(boxbounding, 4, green, 0, green);

	this->m_pClippOneNode = ClippingNode::create();
	m_pClippOneNode->setAnchorPoint(Vec2(0.5, 0.5));
	m_pClippOneNode->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	m_pClippOneNode->addChild(m_pOneSprite);
	m_pClippOneNode->setStencil(m_pOneStencil);
	this->addChild(m_pClippOneNode);

	this->m_pTwoStencil = DrawNode::create();
	this->m_pTwoStencil->retain();
	m_pTwoStencil->drawPolygon(boxbounding, 4, green, 0, green);
	this->m_pClippTwoNode = ClippingNode::create();
	m_pClippTwoNode->setAnchorPoint(Vec2(0.5, 0.5));
	m_pClippTwoNode->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	m_pClippTwoNode->addChild(m_pTwoSprite);
	m_pClippTwoNode->setStencil(m_pTwoStencil);
	this->addChild(m_pClippTwoNode);
	return true;
}

bool ShapeLayer::initListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ShapeLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ShapeLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ShapeLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool ShapeLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

void ShapeLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	this->generateAllVertex(pTouch->getStartLocation(), pTouch->getLocation());
}
void ShapeLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
}

Vec2 ShapeLayer::getContactVec(Point p1, Point p2, Point p3, Point p4)
{
	Vec2 point1 = ccpIntersectPoint(p1, p2, p3, p4);
	if (point1.x > std::min(p1.x, p2.x) && point1.x < std::max(p1.x, p2.x) ||
		point1.y > std::min(p1.y, p2.y) && point1.y < std::max(p1.y, p2.y))
	{
		return point1;
	}
	return Vec2();
}

void ShapeLayer::generateAllVertex(const Vec2 &beginPoint, const Vec2 &endPoint)
{
	Point spritePos = this->m_pClippOneNode->getParent()->convertToWorldSpace(this->m_pClippOneNode->getPosition());

	Rect rect = m_pOneSprite->getBoundingBox();
	Vec2 lb = m_pOneSprite->getParent()->convertToWorldSpace(rect.origin);
	Vec2 lt = m_pOneSprite->getParent()->convertToWorldSpace(Vec2(rect.getMinX(), rect.getMaxY()));
	Vec2 rb = m_pOneSprite->getParent()->convertToWorldSpace(Vec2(rect.getMaxX(), rect.getMinY()));
	Vec2 rt = m_pOneSprite->getParent()->convertToWorldSpace(Vec2(rect.getMaxX(), rect.getMaxY()));

	int index = 0;
	m_pVertexArray[index] = Vec2(rect.origin);
	index++;
	Vec2 point1 = this->getContactVec(lb, rb, beginPoint, endPoint);
	if (point1.x != 0 && point1.y != 0)
	{
		if (m_nOneIndex == -1) m_nOneIndex = index; else m_nTwoIndex = index;
		m_pVertexArray[index] = point1 - spritePos;
		index++;
	}
	m_pVertexArray[index] = Vec2(Vec2(rect.getMaxX(), rect.getMinY()));
	index++;
	point1 = this->getContactVec(rb, rt, beginPoint, endPoint);
	if (point1.x != 0 && point1.y != 0)
	{
		if (m_nOneIndex == -1) m_nOneIndex = index; else m_nTwoIndex = index;
		m_pVertexArray[index] = point1 - spritePos;
		index++;
	}
	m_pVertexArray[index] = Vec2(Vec2(rect.getMaxX(), rect.getMaxY()));
	index++;
	point1 = this->getContactVec(rt, lt, beginPoint, endPoint);
	if (point1.x != 0 && point1.y != 0)
	{
		if (m_nOneIndex == -1) m_nOneIndex = index; else m_nTwoIndex = index;
		m_pVertexArray[index] = point1 - spritePos;
		index++;
	}
	m_pVertexArray[index] = Vec2(Vec2(rect.getMinX(), rect.getMaxY()));
	index++;
	point1 = this->getContactVec(lt, lb, beginPoint, endPoint);
	if (point1.x != 0 && point1.y != 0)
	{
		if (m_nOneIndex == -1) m_nOneIndex = index; else m_nTwoIndex = index;
		m_pVertexArray[index] = point1 - spritePos;
		index++;
	}
	if (index == 6){
		this->setClippStencil();
	}
}

void ShapeLayer::setClippStencil()
{
	if (this->m_nOneIndex != -1 && this->m_nTwoIndex != -1)
	{
		int num = m_nOneIndex + 1 + 6 - m_nTwoIndex;
		Vec2 *vertexOnes = new Vec2[num];
		memcpy(vertexOnes, this->m_pVertexArray, (m_nOneIndex + 1) * sizeof(Vec2));
		memcpy(vertexOnes + m_nOneIndex + 1, m_pVertexArray + m_nTwoIndex, (6 - m_nTwoIndex) * sizeof(Vec2));

		auto stenci3 = DrawNode::create();
		static Color4F green(0, 1, 0, 1);
		stenci3->drawPolygon(vertexOnes, num, green, 0, green);
		m_pClippOneNode->setStencil(stenci3);
		m_pClippOneNode->runAction(RepeatForever::create(RotateBy::create(0.1f, 5.0f)));
		delete[] vertexOnes;

		num = m_nTwoIndex - m_nOneIndex + 1;
		Vec2 *vertexTwos = new Vec2[num];
		memcpy(vertexTwos, m_pVertexArray + m_nOneIndex, num * sizeof(Vec2));

		auto stencil4 = DrawNode::create();
		stencil4->drawPolygon(vertexTwos, num, green, 0, green);
		m_pClippTwoNode->setStencil(stencil4);
		delete[] vertexTwos;
	}
}
