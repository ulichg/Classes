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

	void findRope();

	/* 做爬丝处理*/
	void doSiPa();
	/* 获得毛虫吐丝后，可返回的绳子，返回NULL，辨明无法找到合适的。*/
	Rope* getSiTouchRope();
	/* 回调函数 */
	void backToRope(float dt);

	void setPa();
	~FactoryScene();

private:
	Rope* targetRope;
};

