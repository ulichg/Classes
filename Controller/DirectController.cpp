#include "DirectController.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"

bool DirectController::init(){
	this->isStartTouch = false;
	this->startP = CCPointZero;
	this->iYSpeed = SPEED;

	/* ���������� */
	this->setTouchEnabled(true);
	/* �������м��ٴ����� */
	this->setAccelerometerEnabled(true);

	this->scheduleUpdate();
	return true;
}

void DirectController::update(float dt)
{
	if (mControllerListener == NULL) {
		return;
	}

	
	MaoChong* hero = dynamic_cast<MaoChong*>(mControllerListener);
	if (!hero){
		CCLog("wrong 1");
		return;
	}
	setYSpeedAccordingToRope(hero->getCurRope());
	CCPoint curPos = hero->getCurPosition();
	FactoryScene* fs = dynamic_cast<FactoryScene*>(hero->getParent()->getParent());
	curPos.y += iYSpeed;
	hero->setSimplePosition(curPos);
}

void DirectController::setYSpeedAccordingToRope(Rope* r){
	if (!r){
		return;
	}
	if (r->is_Down()){
		iYSpeed = SPEED;
	}
	else {
		iYSpeed = SPEED * 3;
	}
}

void DirectController::setiXSpeed(float iSpeed)
{
	this->iXSpeed = iSpeed;
}

void DirectController::setiYSpeed(float iSpeed)
{
	this->iYSpeed = iSpeed;
}
bool DirectController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return false;
	}
	if (isStartTouch){
		return false;
	}
	isStartTouch = true;
	/* ��ȡ��������� */
	CCPoint touchLocation = pTouch->getLocationInView();
	this->startP = CCDirector::sharedDirector()->convertToGL(touchLocation);
	return true;
}

void DirectController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

void DirectController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!mControllerListener){
		return;
	}
	if (!isStartTouch){
		return;
	}
	isStartTouch = false;
	CCPoint touchLocation = pTouch->getLocationInView();
	CCPoint endP = CCDirector::sharedDirector()->convertToGL(touchLocation);

	MaoChong* hero = dynamic_cast<MaoChong*>(mControllerListener);
	if (!hero){
		return;
	}
	if (startP.x - endP.x < -20){
		hero->statusChangeTo(HeroStatus::RIGHT_FLY);
	}
	else if(startP.x - endP.x > 20){
		hero->statusChangeTo(HeroStatus::LEFT_FLY);
	}
	//float maxLength = MAX(abs(startP.x - endP.x), abs(startP.y - endP.y));

	// �����л�ë�����ڱ�
	if (fabs(startP.x - endP.x) <= 20){
		if (hero->getStatus() == HeroStatus::LEFT_PA){
			hero->statusChangeTo(HeroStatus::RIGHT_PA);
			hero->setCurLine(hero->getCurLine() + 1);
		}
		else if (hero->getStatus() == HeroStatus::RIGHT_PA){
			hero->statusChangeTo(HeroStatus::LEFT_PA);
			hero->setCurLine(hero->getCurLine() - 1);
		}
	}
}

void DirectController::registerWithTouchDispatcher()
{
	/* ע�ᴥ���¼� */
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void DirectController::didAccelerate(CCAcceleration* mAccelerationValue){
	if (mControllerListener == NULL){
		return;
	}

	MaoChong* maoChong = dynamic_cast<MaoChong*>(mControllerListener);
	if (maoChong == NULL){
		return;
	}
	CCDirector* pDtr = CCDirector::sharedDirector();

	if (mAccelerationValue->x > 0.05)
	{
		// ����ƫ
		if (maoChong->getCurLine() % 2 == 0){
			// �����
			maoChong->statusChangeTo(HeroStatus::RIGHT_PA);
			maoChong->setCurLine(maoChong->getCurLine() + 1);
		}
	}
	else if (mAccelerationValue->x < -0.05){
		// ����ƫ
		if (maoChong->getCurLine() % 2 == 1){
			// ���Ҳ�
			maoChong->statusChangeTo(HeroStatus::LEFT_PA);
			maoChong->setCurLine(maoChong->getCurLine() - 1);
		}
	}
}