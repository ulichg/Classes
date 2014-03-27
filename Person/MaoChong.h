#pragma once
#include "Hero.h"
class MaoChong :
	public Hero
{
public:
	CREATE_FUNC(MaoChong);
	// 有限状态机控制游戏过程中的控制器以及动画帧
	virtual void statusChangeTo(HeroStatus mStatus);

	// 设置角色状态
	void setStatus(HeroStatus mStatus);
	bool initWithTileMap(CCTMXTiledMap* map);

	virtual void setSimplePosition();
	static MaoChong* createWithTiledMap(CCTMXTiledMap* map);
private:
	// 设置对应状态的animation
	void runStatusAnimation();
};

