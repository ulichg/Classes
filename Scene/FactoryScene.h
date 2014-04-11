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
	void setMapThings(CCTMXTiledMap* map);

	// 把角色放置在绳子上,先放置，返回是否在绳子上
	bool bindHeroToRope(Rope* rope);
	// 初始化hero
	void initHero(CCTMXTiledMap* map);

	void findRope();

	/* 做爬丝处理*/
	void doSiPa();
	/* 获得毛虫吐丝后，可返回的绳子，返回NULL，辨明无法找到合适的。*/
	Rope* getSiTouchRope();
	/* 回调函数 */
	void backToRope(float dt);
	Rope* getTargetRope();
	void setPa(float dt);

	/* 碰撞检测之类 */
	void update(float dt);
	/* 设置轴和绳子 */
	void setRoundAndRope(CCTMXTiledMap* map);
	/* 设置灯光 */
	void setLight(CCTMXTiledMap* map);
	/* 设置金币 */
	void setCoin(CCTMXTiledMap* map);
	/* 显示毛虫挂了后效果*/
	void showDie();
	void initMap();
	void addMap(CCTMXTiledMap* map);
	~FactoryScene();

private:
	Rope* targetRope;
};

