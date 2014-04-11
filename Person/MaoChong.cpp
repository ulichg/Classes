#include "MaoChong.h"
#include "Data/GlobalVar.h"
#include "Scene/FactoryScene.h"
#include "Controller/FallDownController.h"

//// ����״̬��������Ϸ�����еĿ������Լ�����֡
//void statucChangeTo(HeroStatus mStatus);
//
//// ���ý�ɫ״̬
//void setStatus(HeroStatus mStatus);
//
//// ���ݴ���Ĳ������ж���
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
		this->statusChangeTo(HeroStatus::DIE);
		return;
	}

	/*if (mSprite){*/
	if (mArmature){
		this->setPosition(c);
		this->setViewPointByPlayer();
	}
}


bool MaoChong::initWithTileMap(CCTMXTiledMap* map)
{
	this->curRope = NULL;
	this->mArmature = NULL;
	this->mController = NULL;
	this->heroLevel = HERO_LEVEL;
	this->curLine = 0;
	this->mStatus = HeroStatus::LEFT_PA;
	this->map = map;

	// ����maochongnodeλ��
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("objects");
	CCDictionary* heroStartPointDic = objGroup->objectNamed("heroStartPoint");
	float heroX = heroStartPointDic->valueForKey("x")->floatValue();
	float heroY = heroStartPointDic->valueForKey("y")->floatValue();
	this->setPosition(ccp(heroX, heroY));

	// ���heroͼƬ
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero/chong10.plist", "hero/chong10.png");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("hero/chong1.ExportJson");
	CCArmature* armature = CCArmature::create("chong1");
	if (!armature){
		return true;
	}
	setArmature(armature);
	statusChangeTo(HeroStatus::LEFT_PA);
	map->addChild(this, 10);
	return true;
}

void MaoChong::dataLoaded(float percent){
	
}

void MaoChong::statusChangeTo(int mStatus)
{
	FactoryScene* scene = (FactoryScene*) this->map->getParent();
	switch (mStatus)
	{
	case HeroStatus::LEFT_PA:
		this->setController(DirectController::create());
		break;
	case HeroStatus::RIGHT_PA:
		this->setController(DirectController::create());
		break;
	case HeroStatus::LEFT_FLY:
		if (this->getCurLine() != 2 && this->getCurLine() != 4)
		{
			return;
		}
		this->setController(NULL); // ɾ��controller
		break;
	case HeroStatus::RIGHT_FLY:
		if (this->getCurLine() != 1 && this->getCurLine() != 3)
		{
			return;
		}
		this->setController(NULL); // ɾ��controller
		break;
	case HeroStatus::RIGHT_FALL_DOWN:
		if (HeroStatus::RIGHT_FALL_DOWN == this->mStatus || HeroStatus::LEFT_FALL_DOWN == this->mStatus)
		{
			this->statusChangeTo(HeroStatus::DIE);
			return;
		}
		this->setController(FallDownController::create()); // ɾ��controller
		break;
	case HeroStatus::LEFT_FALL_DOWN:
		if (HeroStatus::RIGHT_FALL_DOWN == this->mStatus || HeroStatus::LEFT_FALL_DOWN == this->mStatus)
		{
			this->statusChangeTo(HeroStatus::DIE);
			return;
		}
		this->setController(FallDownController::create()); // ɾ��controller
		break;
	case HeroStatus::DISAPPEAR:
		this->setController(NULL);
		break;
	case HeroStatus::APPEAR:
		this->setController(NULL);
		break;
	case HeroStatus::BUTTERFLY:
		this->setController(NULL); // ɾ��controller
		break;
	case HeroStatus::DIE:
		this->setController(NULL); // ɾ��controller
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

//// δʹ��studio�汾
//void MaoChong::runStatusAnimation(){
//	mSprite->stopAllActions();
//	CCArray* animFrames = NULL;
//	char str[100] = { 0 };
//	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
//	switch (mStatus)
//	{
//	case HeroStatus::PA:
//	{
//				animFrames = CCArray::createWithCapacity(2);
//				for (int i = 0; i < 2; i++)
//				{
//					sprintf(str, "chongPaFrame_%i.png", i);
//					CCSpriteFrame* frame = cache->spriteFrameByName(str);
//					animFrames->addObject(frame);
//				}
//				if (!animFrames){
//					return;
//				}
//				CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.5f);
//				animation->setLoops(INT32_MAX);
//				mSprite->runAction(CCAnimate::create(animation));
//
//				return;
//	}
//		
//	case HeroStatus::LEFT_FLY:
//	{
//					 CCSprite* heroSprite = CCSprite::create("hero/chongLeftFly_0.png");
//					 setSprite(heroSprite);
//					 CCActionInterval* moveBy = NULL;
//					 if (curLine == 1){
//						 moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[0] - THREELINES[1], 0));
//					 }
//					 else if (curLine == 2){
//						 moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[1] - THREELINES[2], 0));
//					 }
//					 curLine -= 1;
//
//					 if (moveBy){
//						 this->runAction(
//							 CCSequence::create(
//								moveBy, 
//								CCCallFunc::create(this, callfunc_selector(MaoChong::moveFinishedCallFunc)),
//								NULL));
//					 }
//					 return;
//	}
//	case HeroStatus::RIGHT_FLY:
//	{
//					  CCSprite* heroSprite = CCSprite::create("hero/chongRightFly_0.png");
//					  setSprite(heroSprite);
//					  CCActionInterval* moveBy = NULL;
//					  if (curLine == 0){
//						  moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[1] - THREELINES[0], 0));
//					  }
//					  else if (curLine == 1){
//						  moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[2] - THREELINES[1], 0));
//					  }
//					  curLine += 1;
//
//					  if (moveBy){
//						  this->runAction(
//							  CCSequence::create(
//							  moveBy,
//							  CCCallFunc::create(this, callfunc_selector(MaoChong::moveFinishedCallFunc)),
//							  NULL));
//					  }
//					  return;
//	}
//	case HeroStatus::FALL_DOWN:
//	{
//					CCSprite* heroSprite = CCSprite::create("hero/chongFallDown_0.png");
//					setSprite(heroSprite);
//					return;
//	}
//	case HeroStatus::BUTTERFLY:
//		return;
//	case HeroStatus::SI_PA:
//	{
//					/*CCSprite* heroSprite = CCSprite::create("hero/chongFallDown_0.png");
//					setSprite(heroSprite);
//					return;*/
//	}
//	default:
//		return;
//	}
//}

// ʹ��studio�汾
void MaoChong::runStatusAnimation(){
	//mSprite->stopAllActions();

	switch (mStatus)
	{
	case HeroStatus::LEFT_PA:
		this->mArmature->getAnimation()->play("chongLeftPa");
		break;
	case HeroStatus::RIGHT_PA:
		this->mArmature->getAnimation()->play("chongRightPa");
		break;
	case HeroStatus::LEFT_FLY:
	{
								 this->mArmature->getAnimation()->play("chongLeftFly");
								 CCActionInterval* moveBy = NULL;
								 if (curLine == 2){
									 moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[0] - THREELINES[1], 0));
								 }
								 else if (curLine == 4){
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
								this->mArmature->getAnimation()->play("chongRightFly");
								CCActionInterval* moveBy = NULL;
								if (curLine == 1){
									moveBy = CCMoveBy::create(TIME_HOR, ccp(THREELINES[1] - THREELINES[0], 0));
								}
								else if (curLine == 3){
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
	case HeroStatus::RIGHT_FALL_DOWN:
	{
								this->mArmature->getAnimation()->play("chongRightFallDown");
								return;
	}
	case HeroStatus::LEFT_FALL_DOWN:
	{
								this->mArmature->getAnimation()->play("chongLeftFallDown");
								return;
	}
	case HeroStatus::DISAPPEAR:
	{
							  this->mArmature->getAnimation()->play("chongDisappear");
							  return;
	}
	case HeroStatus::APPEAR:
	{
							  this->mArmature->getAnimation()->play("chongAppear");
							  return;
	}
	case HeroStatus::BUTTERFLY:
		return;
	case HeroStatus::DIE:
		return;
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

void MaoChong::setCurRope(Rope* r){
	this->curRope = r;
}

Rope* MaoChong::getCurRope(){
	return this->curRope;
}

CCRect MaoChong::getCollideRect()
{
	if (!this->mArmature){
		return CCRectZero;
	}
#define ADJUST_SIZE 30
	// mArmtature�Ĵ�С
	CCRect area = this->mArmature->boundingBox();
	

	CCRect c = CCRectMake(this->getPositionX() + area.getMinX(), this->getPositionY() + area.getMinY(),
		area.size.width, area.size.height - ADJUST_SIZE);
	return c;
}