#pragma once
#include "Controller.h"
#include "Person/MaoChong.h"
#include "cocos2d.h"
using namespace cocos2d;

/************************************************************************/
/* �ȴ�������
����ë��ָ������Ӻ󲻶�*/
/************************************************************************/
class WaitController :
	public Controller
{
public:
	CREATE_FUNC(WaitController);
	virtual bool init();

	/* �����¼� */
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

