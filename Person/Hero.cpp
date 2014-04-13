#include "Hero.h"
#include "scene/BaseScene.h"
#include "data/GlobalVar.h"

float Max(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

float Min(float a, float b)
{
	if (a > b){
		return b;
	}
	else
	{
		return a;
	}
}

void Hero::setSprite(CCSprite* mSprite){
	if (this->mSprite){
		this->removeChild(this->mSprite);
	}
	mSprite->setAnchorPoint(ccp(0.5, 1));
	mSprite->setPosition(CCPointZero);
	this->mSprite = mSprite;
	this->addChild(mSprite);
}

void Hero::setArmature(CCArmature* mArmature){
	if (mArmature == NULL){
		this->removeChild(this->mArmature);
		return;
	}
	if (this->mArmature){
		this->removeChild(this->mArmature);
	}
	mArmature->setPosition(CCPointZero);
	this->mArmature = mArmature;
	this->addChild(mArmature);
}

void Hero::setSimplePosition(CCPoint c){

}

void Hero::setStatus(int status){
	this->mStatus = status;
}


void Hero::setViewPointByPlayer()
{
	/*if (mSprite == NULL) {*/
	if (mArmature == NULL){
		return;
	}
	CCLayer* parent = (CCLayer*)this->getParent();

	/* ��Ļ��С */
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/* ��������� */
	CCPoint spritePos = this->getPosition();

	/* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ��������� */
	float x = Max(spritePos.x, visibleSize.width / 2);
	float y = Max(spritePos.y, visibleSize.height / 3);

	///* ���x��y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ������Ļ��ɳ��ֺڱߵļ������꣩ */
	x = Min(x, WIDTH - visibleSize.width / 2);
	//y = Min(y, mapSize.height - visibleSize.height / 3 * 2);

	CCPoint destPos = CCPoint(x, y);
	CCPoint fixPos = CCPoint(visibleSize.width / 2, visibleSize.height / 3);

	/* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */
	CCPoint viewPos = ccpSub(fixPos, destPos);

	BaseScene* bs = dynamic_cast<BaseScene*>(parent->getParent());
	if (!bs){
		return;
	}
	bs->setViewPoint(viewPos);
}

CCPoint Hero::tileCoordForPosition(CCPoint pos){
	CCSize mapTiledNum = map->getMapSize();
	CCSize tiledSize = map->getTileSize();

	float x = pos.x / tiledSize.width;
	float y = pos.y / tiledSize.height;

	/* Cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ��������� */
	y = mapTiledNum.height - y;

	/*CCLog("x: %f, y: %f", x, y);
	CCLog("pos.x: %f, pos.y: %f", pos.x, pos.y);*/
	return ccp(x, y);
}

void Hero::setController(Controller* controller){
	CCLayer* layer = dynamic_cast<CCLayer*>(this->getParent());
	if (!layer){
		CCLog("wrong Hero::setController");
		return;
	}
	if (this->mController && this->mController != controller){
		layer->removeChild(this->mController);
		this->mController->unscheduleAllSelectors();
		this->mController = NULL;
	}
	if (!controller){
		return;
	}
	this->mController = controller;
	this->mController->setControllerListener(this);
	layer->addChild(this->mController, 11, CONTROLLER_TAG);
}

CCPoint Hero::getCurPosition(){
	/*if (mSprite){*/
	if (mArmature){
		return this->getPosition();
	}

	return CCPoint(0, 0);
}

int Hero::getHeroLevel(){
	return heroLevel;
}

int Hero::getStatus(){
	return mStatus;
}