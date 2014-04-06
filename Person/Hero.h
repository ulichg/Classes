#pragma once
#include "Controller/Controller.h"
#include "cocos2d.h"
#include "HeroStatus.h"
#include "cocos-ext.h" 

using namespace cocos2d;
using namespace cocos2d::extension;

class Hero :
	public CCNode, public ControllerListener
{
public:
	virtual void setSprite(CCSprite* mSprite);
	virtual void setArmature(CCArmature* mArmature);
	virtual void setController(Controller* controller);
	virtual void setSimplePosition(CCPoint c);
	virtual CCPoint getCurPosition();
	virtual void setViewPointByPlayer();
	virtual void setStatus(int mStatus);
	virtual int getStatus();
	virtual void statusChangeTo(int mStatus) = 0;
	virtual int getHeroLevel();
	virtual int getSiNum();
	virtual void setSiNum(int i);

protected:
	CCSprite* mSprite;
	CCArmature* mArmature;
	CCTMXTiledMap* map;
	CCTMXLayer* meta;

	Controller* mController;
	int mStatus;
	CCPoint tileCoordForPosition(CCPoint pos);
	// 英雄等级
	int heroLevel;
	// 现有的可吐丝次数
	int siNum;
};
