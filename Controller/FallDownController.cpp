#include "FallDownController.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"

bool FallDownController::init(){
	this->iYSpeed = FALL_DOWN_SPEED;
	this->startP = -1;
	/* ���������� */
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}

void FallDownController::update(float dt)
{
	if (mControllerListener == NULL) {
		return;
	}

	MaoChong* hero = dynamic_cast<MaoChong*>(mControllerListener);
	if (!hero){
		CCLog("wrong 1");
		return;
	}
	float nowP = hero->getPositionY();
	if (startP == -1){
		startP = nowP;
	}
	else if (nowP - startP > HEIGHT / 2){
		hero->statusChangeTo(HeroStatus::DIE);
		return;
	}
	iYSpeed += 0.098f;
	CCPoint curPos = hero->getCurPosition();
	curPos.y -= iYSpeed;
	hero->setSimplePosition(curPos);
}

void FallDownController::setiYSpeed(int iSpeed)
{
	this->iYSpeed = iSpeed;
}


bool FallDownController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return true;
	}

	FactoryScene* fs = dynamic_cast<FactoryScene*>(this->getParent()->getParent());
	if (!fs){
		return true;
	}
	fs->doSiPa();
	
	return true;
}

void FallDownController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	///* ��ȡ��������� */
	//CCPoint touchLocation = pTouch->getLocationInView();
	//touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

	///* �����ƶ�������� */
	//CCPoint pos = mControllerListener->getCurPosition();

	///* �ж��������ƶ����������ƶ� */
	//int iSpeed = 0;
	//if (touchLocation.x > pos.x) {
	//	iSpeed = 1;
	//}
	//else {
	//	iSpeed = -1;
	//}

	//setiXSpeed(iSpeed);
}

void FallDownController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void FallDownController::registerWithTouchDispatcher()
{
	/* ע�ᴥ���¼� */
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}