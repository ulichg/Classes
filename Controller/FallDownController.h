#pragma once
#include "Controller.h"
#include "Person/MaoChong.h"
#include "cocos2d.h"
using namespace cocos2d;

class FallDownController :
	public Controller
{
public:
	CREATE_FUNC(FallDownController);
	virtual bool init();
	virtual void update(float dt);

	/* �����¼� */
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	/* ����Y������ƶ��ٶ�*/
	void setiYSpeed(int iSpeed);
private:
	float iYSpeed;
};

