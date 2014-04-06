#pragma once
#include "Hero.h"
#include "Controller/DirectController.h"
#include "Scene/Rope.h"

class FactoryScene;

using namespace cocos2d;
using namespace cocos2d::extension;

class MaoChong :
	public Hero
{
public:
	// 有限状态机控制游戏过程中的控制器以及动画帧
	virtual void statusChangeTo(int mStatus);

	// 设置角色状态
	void setStatus(int mStatus);
	bool initWithTileMap(CCTMXTiledMap* map);

	virtual void setSimplePosition(CCPoint c);
	static MaoChong* createWithTiledMap(CCTMXTiledMap* map);
	int getCurLine();
	void setCurLine(int c);
	void moveFinishedCallFunc();
	void dataLoaded(float percent);

	/* 获得毛虫碰撞区域 */
	CCRect getCollideRect();
private:
	// 设置对应状态的animation
	void runStatusAnimation();
	// 当前所在线 ：从左到右依次为：0 - 5
	int curLine;
};

