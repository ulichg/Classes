#pragma once
#include "Controller.h"
#include "Person/MaoChong.h"
#include "Scene/Rope.h"
#include "cocos2d.h"
using namespace cocos2d;

class DirectController :
	public Controller
{
public:
	CREATE_FUNC(DirectController);
	virtual bool init();
	virtual void update(float dt);

	/* 触屏事件 */
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	/* 设置X方向的移动速度 */
	void setiXSpeed(float iSpeed);

	/* 设置Y方向的移动速度*/
	void setiYSpeed(float iSpeed);
	/* 根据毛虫所在绳子状态判定毛虫速度 */
	void setYSpeedAccordingToRope(Rope* r);
private:
	float iXSpeed;
	float iYSpeed;
	// 触摸开始点
	CCPoint startP;
	bool isStartTouch;
};

