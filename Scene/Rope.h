#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Rope : public CCNode
{
public:
	Rope();
	// 绳子最长长度
	static const float MAXLINE;

	// 绳子最短长度
	static const float MINLINE;
	// 初始化
	virtual bool init();
	// 获得绳子的碰撞区域
	CCRect getCollideRect();
	// 绳子卷动效果实现
	void rollAction();
	// 更新绳子效果
	void update(float delta);
protected:
	CCSprite* mSprite;
	// 当前运动方向是否向下
	bool isDown;
	// 当前长度
	float curLength;
};