#pragma once
#include "cocos2d.h"
#include "Person/MaoChong.h"
using namespace cocos2d;

class BaseScene :
	public CCLayer
{
public:
	CREATE_FUNC(BaseScene);

	virtual bool init();
	virtual void setMap(CCTMXTiledMap* map);
	static CCScene* scene();
	virtual void bindControllerToHero(Controller* controller);

protected:
	CCTMXTiledMap* map;
	Hero* hero;
	Controller* controller;
};

