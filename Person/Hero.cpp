#include "Hero.h"


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
	this->mSprite = mSprite;
}

void Hero::setSimplePosition(CCPoint c){

}

void Hero::setStatus(HeroStatus status){
	this->mStatus = status;
}


void Hero::setViewPointByPlayer()
{
	if (mSprite == NULL) {
		return;
	}
	CCLayer* parent = (CCLayer*)mSprite->getParent();

	/* 地图方块数量 */
	CCSize mapTiledNum = map->getMapSize();

	/* 地图单个格子大小 */
	CCSize tiledSize = map->getTileSize();

	/* 地图大小 */
	CCSize mapSize = CCSize(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* 屏幕大小 */
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/* 精灵的坐标 */
	CCPoint spritePos = mSprite->getPosition();

	/* 如果精灵坐标小于屏幕的一半，则取屏幕中点坐标，否则取精灵的坐标 */
	float x = Max(spritePos.x, visibleSize.width / 2);
	float y = Max(spritePos.y, visibleSize.height / 4);

	/* 如果x、y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标） */
	x = Min(x, mapSize.width - visibleSize.width / 2);
	y = Min(y, mapSize.height - visibleSize.height / 4 * 3);

	CCPoint destPos = CCPoint(x, y);
	CCPoint fixPos = CCPoint(visibleSize.width / 2, visibleSize.height / 4);

	/* 计算屏幕中点和所要移动的目的点之间的距离 */
	CCPoint viewPos = ccpSub(fixPos, destPos);

	parent->setPosition(viewPos);
}

CCPoint Hero::tileCoordForPosition(CCPoint pos){
	CCSize mapTiledNum = map->getMapSize();
	CCSize tiledSize = map->getTileSize();

	float x = pos.x / tiledSize.width;
	float y = pos.y / tiledSize.height;

	/* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
	y = mapTiledNum.height - y;

	/*CCLog("x: %f, y: %f", x, y);
	CCLog("pos.x: %f, pos.y: %f", pos.x, pos.y);*/
	return ccp(x, y);
}

void Hero::setController(Controller* controller){
	this->mController = controller;
	mController->setControllerListener(this);
}

CCPoint Hero::getCurPosition(){
	if (mSprite){
		return this->getPosition();
	}

	return CCPoint(0, 0);
}