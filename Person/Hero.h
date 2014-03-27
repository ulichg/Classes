#pragma once
#include "Controller/Controller.h"
#include "cocos2d.h"

using namespace cocos2d;


enum HeroStatus
{
	PA, LEFT_FLY, RIGHT_FLY, FALL_DOWN, BUTTERFLY
};


class Hero :
	public CCNode, public ControllerListener
{
public:
	virtual void setSprite(CCSprite* mSprite);
	virtual void setController(Controller* controller);
	virtual void setSimplePosition(int x, int y);
	virtual CCPoint getCurPosition();
	virtual void setViewPointByPlayer();

protected:
	CCSprite* mSprite;
	CCTMXTiledMap* map;
	CCTMXLayer* meta;

	Controller* mController;
	HeroStatus mStatus;
	CCPoint tileCoordForPosition(CCPoint pos);
};
