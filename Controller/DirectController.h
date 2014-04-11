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

	/* �����¼� */
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	/* ����X������ƶ��ٶ� */
	void setiXSpeed(float iSpeed);

	/* ����Y������ƶ��ٶ�*/
	void setiYSpeed(float iSpeed);
	/* ����ë����������״̬�ж�ë���ٶ� */
	void setYSpeedAccordingToRope(Rope* r);
private:
	float iXSpeed;
	float iYSpeed;
	// ������ʼ��
	CCPoint startP;
	bool isStartTouch;
};

