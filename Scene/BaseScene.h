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
	virtual void addMap(CCTMXTiledMap* map);
	virtual void removeMap(CCTMXTiledMap* map);
	/* ������Ұ�� */
	virtual void setViewPoint(CCPoint c);
	static CCScene* scene();
	void refreshSiNumLabel(); // ˢ��˿��
	void refreshCoinNumLabel(); //ˢ�½����
	CCArray* getRopeArray();
	/*����ں����һ�ŵ�ͼ*/
	virtual void addRandomMap();
	/*���¾�����ֵ*/
	void updateDistance(float dt);
protected:
	CCTMXTiledMap* map;
	CCLayer* thingLayer;
	CCArray* mapArray;
	unsigned int curMap;
	Hero* hero;
	Controller* controller;
	// ���Ӽ���
	CCArray* ropeArray;
	// ���Ἧ��
	CCArray* roundArray;
	CCArray* coinArray;
	int siNum;
	int coinNum;
	int distance;
};
