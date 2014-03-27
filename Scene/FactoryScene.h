#pragma once
#include "cocos2d.h"
#include "BaseScene.h"
#include "Rope.h"

class FactoryScene :
	public BaseScene
{
public:
	CREATE_FUNC(FactoryScene);

	virtual bool init();
	static CCScene* scene();

	//设置地图上的信息，绳子 轴
	void setMapThings();

	// 把角色放置在绳子上,先放置，返回是否在绳子上
	bool bindHeroToRope(Rope* rope);
	// 初始化hero
	void initHero();
protected:
	// 绳子集合
	CCArray* ropeArray;
};

