#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class MaoChong;
class Controller;
class Hero;

class BaseScene :
	public CCLayer
{
public:
	CREATE_FUNC(BaseScene);

	virtual bool init();
	virtual void setMap(CCTMXTiledMap* map);
	static CCScene* scene();

protected:
	CCTMXTiledMap* map;
	Hero* hero;
	Controller* controller;
	// Éþ×Ó¼¯ºÏ
	CCArray* ropeArray;
};

