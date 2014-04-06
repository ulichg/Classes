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
	void refreshSiNumLabel(); // 刷新丝数
	CCArray* getRopeArray();
protected:
	CCTMXTiledMap* map;
	Hero* hero;
	Controller* controller;
	// 绳子集合
	CCArray* ropeArray;
	int siNum;
};
