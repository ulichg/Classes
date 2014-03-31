#include "MaoChong.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"
#include "Controller/FallDownController.h"

//// 有限状态机控制游戏过程中的控制器以及动画帧
//void statucChangeTo(HeroStatus mStatus);
//
//// 设置角色状态
//void setStatus(HeroStatus mStatus);
//
//// 根据传入的参数运行动作
//void doAnimation();

MaoChong* MaoChong::createWithTiledMap(CCTMXTiledMap* map){
	MaoChong* maoChong = new MaoChong();
	
	if (maoChong && maoChong->initWithTileMap(map)){
	}
	else{
		CC_SAFE_DELETE(maoChong);
	}
	return maoChong;
}


void MaoChong::setSimplePosition(CCPoint c){
	if (c.x < 0 || c.y < 50)
	{
		return;
	}
	if (mSprite){
		CCPoint tiledPos = tileCoordForPosition(c);
		int tiledGid = meta->tileGIDAt(tiledPos);

		if (tiledGid != 0){
			CCDictionary* propertiesDict = map->propertiesForGID(tiledGid);

			if (propertiesDict != NULL){
				const CCString* prop = CCString::create("");
				prop = propertiesDict->valueForKey("Collidable");

				if (prop->m_sString.compare("true") == 0){
					CCLog("collidable");
					statusChangeTo(HeroStatus::FALL_DOWN);
					return;
				}
			}
			
		}
		this->setPosition(c);
		this->setViewPointByPlayer();
	}
}


bool MaoChong::initWithTileMap(CCTMXTiledMap* map)
{
	this->heroLevel = HERO_LEVEL;
	this->siNum = SI_START_NUM;
	this->curLine = 0;
	this->mStatus = HeroStatus::PA;
	this->map = map;
	this->meta = map->layerNamed("meta");
	//this->meta->setVisible(false);

	// 设置maochongnode位置
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("objects");
	CCDictionary* heroStartPointDic = objGroup->objectNamed("heroStartPoint");
	float heroX = heroStartPointDic->valueForKey("x")->floatValue();
	float heroY = heroStartPointDic->valueForKey("y")->floatValue();
	this->setAnchorPoint(ccp(0.5, 1));	
	this->setPosition(ccp(heroX, heroY));

	// 添加hero图片
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero/hero.plist", "hero/hero.png");
	CCSprite* heroSprite = CCSprite::createWithSpriteFrameName("chongPaFrame_0.png");
	setSprite(heroSprite);
	map->addChild(this, 10);

	return true;
}

void MaoChong::statusChangeTo(int mStatus)
{
	FactoryScene* scene = (FactoryScene*) this->map->getParent();
	switch (mStatus)
	{
	case HeroStatus::PA:
		this->setController(DirectController::create());
		break;
	case HeroStatus::LEFT_FLY:
		if (this->getPositionX() <= THREELINES[0])
		{
			return;
		}
		this->setController(NULL); // 删除controller
		break;
	case HeroStatus::RIGHT_FLY:
		if (this->getPositionX() >= THREELINES[2])
		{
			return;
		}
		this->setController(NULL); // 删除controller
		break;
	case HeroStatus::FALL_DOWN:
		this->setController(FallDownController::create()); // 删除controller
		break;
	case HeroStatus::BUTTERFLY:
		break;
	default:
		break;
	}
	CCLog("Change status: %i", mStatus);
	setStatus(mStatus);
	runStatusAnimation();
}

void MaoChong::setStatus(int mStatus){
	this->mStatus = mStatus;
}

void MaoChong::runStatusAnimation(){
	mSprite->stopAllActions();
	CCArray* animFrames = NULL;
	char str[100] = { 0 };
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	switch (mStatus)
	{
	case HeroStatus::PA:
	{
				animFrames = CCArray::createWithCapacity(2);
				for (int i = 0; i < 2; i++)
				{
					sprintf(str, "chongPaFrame_%i.png", i);
					CCSpriteFrame* frame = cache->spriteFrameByName(str);
					animFrames->addObject(frame);
				}
				if (!animFrames){
					return;
				}
				CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.5f);
				animation->setLoops(INT32_MAX);
				mSprite->runAction(CCAnimate::create(animation));

				return;
	}
		
	case HeroStatus::LEFT_FLY:
	{
					 CCSprite* heroSprite = CCSprite::create("hero/chongLeftFly_0.png");
					 setSprite(heroSprite);
					 CCActionInterval* moveBy = NULL;
					 if (curLine == 1){
						 moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[0] - THREELINES[1], 0));
					 }
					 else if (curLine == 2){
						 moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[1] - THREELINES[2], 0));
					 }
					 curLine -= 1;

					 if (moveBy){
						 this->runAction(
							 CCSequence::create(
								moveBy, 
								CCCallFunc::create(this, callfunc_selector(MaoChong::moveFinishedCallFunc)),
								NULL));
					 }
					 return;
	}
	case HeroStatus::RIGHT_FLY:
	{
					  CCSprite* heroSprite = CCSprite::create("hero/chongRightFly_0.png");
					  setSprite(heroSprite);
					  CCActionInterval* moveBy = NULL;
					  if (curLine == 0){
						  moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[1] - THREELINES[0], 0));
					  }
					  else if (curLine == 1){
						  moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[2] - THREELINES[1], 0));
					  }
					  curLine += 1;

					  if (moveBy){
						  this->runAction(
							  CCSequence::create(
							  moveBy,
							  CCCallFunc::create(this, callfunc_selector(MaoChong::moveFinishedCallFunc)),
							  NULL));
					  }
					  return;
	}
	case HeroStatus::FALL_DOWN:
	{
					CCSprite* heroSprite = CCSprite::create("hero/chongFallDown_0.png");
					setSprite(heroSprite);
					return;
	}
	case HeroStatus::BUTTERFLY:
		return;
	case HeroStatus::SI_PA:
	{
					/*CCSprite* heroSprite = CCSprite::create("hero/chongFallDown_0.png");
					setSprite(heroSprite);
					return;*/
	}
	default:
		return;
	}
}


int MaoChong::getCurLine(){
	return curLine;
}

void MaoChong::setCurLine(int c){
	this->curLine = c;
}

void MaoChong::moveFinishedCallFunc()
{
	FactoryScene* scene = (FactoryScene*) this->map->getParent();
	if (!scene){
		return;
	}
	scene->findRope();
}