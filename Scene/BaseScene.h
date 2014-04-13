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
	virtual bool init();
	virtual void setMap(CCTMXTiledMap* map);
	virtual void addMap(CCTMXTiledMap* map);
	virtual void removeMap(CCTMXTiledMap* map);
	/* 设置视野点 */
	virtual void setViewPoint(CCPoint c);
	static CCScene* scene();
	void refreshSiNumLabel(); // 刷新丝数
	void refreshCoinNumLabel(); //刷新金币数
	CCArray* getRopeArray();
	/*随机在后方添加一张地图*/
	virtual void addRandomMap();
protected:
	CCTMXTiledMap* map;
	CCLayer* thingLayer;
	CCArray* mapArray;
	unsigned int curMap;
	Hero* hero;
	Controller* controller;
	// 绳子集合
	CCArray* ropeArray;
	// 轮轴集合
	CCArray* roundArray;
	CCArray* coinArray;
	int siNum;
	int coinNum;
};
