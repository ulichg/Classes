#pragma once
#include "Controller.h"
#include "Person/MaoChong.h"
#include "cocos2d.h"
using namespace cocos2d;

/************************************************************************/
/* 等待控制器
用于毛虫恢复到绳子后不动*/
/************************************************************************/
class WaitController :
	public Controller
{
public:
	CREATE_FUNC(WaitController);
	virtual bool init();

	/* 触屏事件 */
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

