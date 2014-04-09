#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Rope : public CCNode
{
public:
	Rope();
	// 初始化
	virtual bool init();
	// 获得绳子的碰撞区域
	CCRect getCollideRect();
	// 绳子卷动效果实现
	void rollAction();
	// 更新绳子效果
	void update(float delta);
	// 设置显示
	void setShowLength();
	// 获得绳子长度
	float getCurLength();
	// 是否下落
	bool is_Down();
protected:
	CCSprite* mSprite;
	// 当前运动方向是否向下
	bool isDown;
	// 当前长度
	float curLength;
};