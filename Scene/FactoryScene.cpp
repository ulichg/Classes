#include "FactoryScene.h"
#include "Person/MaoChong.h"
#include "Data/GlobalVar.h"

bool FactoryScene::init(){
	this->targetRope = NULL;
	this->ropeArray = CCArray::create();
	ropeArray->retain();
	this->roundArray = CCArray::create();
	roundArray->retain();
	this->coindArray = CCArray::create();
	coindArray->retain();

	CCTMXTiledMap* map = CCTMXTiledMap::create("map/testMap.tmx");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map/mapThing.plist", "map/mapThing.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map/coin0.plist", "map/coin0.png");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("map/coin.ExportJson");
	setMap(map);
	initHero();
	setMapThings();
	return true;
}

void FactoryScene::initHero(){
	MaoChong* maoChong = MaoChong::createWithTiledMap(map);
	hero = maoChong;
}

CCScene* FactoryScene::scene(){
	CCScene* mScene = CCScene::create();
	FactoryScene* mLayer = FactoryScene::create();
	mScene->addChild(mLayer);

	return mScene;
}

void FactoryScene::setMapThings(){
	if (!this->map){
		return;
	}

	// 设置转动的轴以及绳子
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("roundObjects");
	int length = objGroup->getObjects()->count();
	char str[100];
	for (int i = 0; i < length; i++)
	{
		sprintf(str, "round_%i", i);
		CCDictionary* roundDic = objGroup->objectNamed(str);
		float x = roundDic->valueForKey("x")->floatValue();
		float y = roundDic->valueForKey("y")->floatValue();
		
		/*CCSprite* roundSprite = CCSprite::createWithSpriteFrameName("round.png");*/
		CCSprite* roundSprite = CCSprite::create("map/round.png");
		roundArray->addObject(roundSprite);
		CCSize size = roundSprite->getContentSize();
		//roundSprite->setPosition(ccp(x + size.width / 2, y + size.height / 2));
		roundSprite->setPosition(ccp(x, y));

		CCActionInterval* rotate = CCRotateBy::create(2, 360.0f);

		// 第一个轴不转
		if (i != 0){
			roundSprite->runAction(CCRepeatForever::create(rotate));
		}
		map->addChild(roundSprite, 1);

		Rope* rope = new Rope();
		ropeArray->addObject(rope);
		rope->setPosition(ccp(x, y));
		// 第一个绳子不动
		if (i != 0)
		{
			rope->rollAction();
		}
		else 
		{
			bindHeroToRope(rope);
		}
		
		map->addChild(rope, 0);
	}

	// 设置灯光
	CCTMXObjectGroup* objGroup1 = map->objectGroupNamed("lightObjects");
	int length1 = objGroup1->getObjects()->count();
	char str1[100];
	for (int i = 0; i < length1; i++)
	{
		sprintf(str1, "light_%i", i);
		CCDictionary* lightDic = objGroup1->objectNamed(str1);
		float x = lightDic->valueForKey("x")->floatValue();
		float y = lightDic->valueForKey("y")->floatValue();

		CCSprite* light = CCSprite::create("map/light.png");
		CCSprite* led = CCSprite::create("map/LED.png");
		
		// 调整灯方向
		const CCString* prop = CCString::create("");
		prop = lightDic->valueForKey("loc");
		led->setAnchorPoint(ccp(1, 0.5));
		light->setAnchorPoint(ccp(1, 0.5));
		if (prop->m_sString.compare("left") == 0){
			led->setScaleX(-1);
		}
		else {
			led->setScaleX(1);
		}
		led->setPosition(ccp(x, y));
		light->setPosition(ccp(0, led->getContentSize().height / 2));
		led->addChild(light, 1);

		map->addChild(led, 20);

		/*CCActionInterval* blink = CCBlink::create(rand() % 3 + 1, 1);
		light->runAction(CCRepeatForever::create(blink));*/

		CCActionInterval* ac1 = CCFadeOut::create(rand() % 10 / float(10) + 1);
		CCSequence* se = CCSequence::create(ac1, ac1->reverse(), NULL);
		light->runAction(CCRepeatForever::create(se));
	}

	//CCArmature* armature = CCArmature::create("coin0");

	refreshSiNumLabel();
}

void FactoryScene::update(float dt){
	MaoChong* maoChong = (MaoChong*)hero;
	if (!hero)
	{
		return;
	}
	for (unsigned int i = 0; i < roundArray->count(); i++){
		CCSprite* r = (CCSprite*)roundArray->objectAtIndex(i);
		if (r->getTextureRect().intersectsRect(maoChong->getCollideRect())){
			if (maoChong->getCurLine() % 2 == 0){
				maoChong->statusChangeTo(HeroStatus::LEFT_FALL_DOWN);
			}
			else {
				maoChong->statusChangeTo(HeroStatus::RIGHT_FALL_DOWN);
			}
			
		}
	}
}

bool FactoryScene::bindHeroToRope(Rope* rope){
	if (!rope || !this->hero)
	{
		return false;
	}
	CCPoint ropeP = rope->getPosition();
	CCPoint heroP = this->hero->getPosition();

	CCLog("Hero loc: %f %f", ropeP.x, heroP.y);
	this->hero->setPosition(ropeP.x, heroP.y);

	return true;
}

void FactoryScene::findRope(){
	MaoChong* maoChong = (MaoChong*)hero;
	CCLog("find rope");
	Rope* targetRope = NULL;
	// 检测碰到哪根绳子
	for (unsigned int i = 0; i < ropeArray->count(); i++){
		Rope* r = (Rope*)ropeArray->objectAtIndex(i);
		if (r->getCollideRect().intersectsRect(maoChong->getCollideRect()) && r->getPositionY() > maoChong->getPositionY()){
			if (targetRope){
				// 已存在，取近的
				if (r->getPositionY() < targetRope->getPositionY()){
					targetRope = r;
				}
			}
			else {
				targetRope = r;
			}
		}
	}

	if (targetRope){
		// 找到绳子，绑定，并设置设置毛虫爬方向
		bindHeroToRope(targetRope);
		if (maoChong->getCurLine() % 2 == 1)
		{
			maoChong->statusChangeTo(HeroStatus::RIGHT_PA);
		}
		else
		{
			maoChong->statusChangeTo(HeroStatus::LEFT_PA);
		}
	}
	else {
		// 没碰到绳子，设置掉落方向
		if (maoChong->getCurLine() % 2 == 1)
		{
			maoChong->statusChangeTo(HeroStatus::RIGHT_FALL_DOWN);
		}
		else
		{
			maoChong->statusChangeTo(HeroStatus::LEFT_FALL_DOWN);
		}
	}
}

Rope* FactoryScene::getSiTouchRope(){
	Rope* targetRope = NULL;

	if (!hero){
		return NULL;
	}

	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (!maoChong)
	{
		return NULL;
	}
	// 检测碰到哪根绳子
	for (unsigned int i = 0; i < ropeArray->count(); i++){
		Rope* r = (Rope*)ropeArray->objectAtIndex(i);
		if (r->getPositionX() == THREELINES[maoChong->getCurLine() / 2]){
			if (targetRope){
				// 已存在，取近的
				if (r->getPositionY() < targetRope->getPositionY() && r->getPositionY() > hero->getPositionY()){
					targetRope = r;
				}
			}
			else {
				targetRope = r;
			}
		}
	}
	return targetRope;
}

void FactoryScene::doSiPa()
{
	int siNum = hero->getSiNum();
	if (siNum > 0)
	{
		this->targetRope = getSiTouchRope();
		if (!targetRope)
		{
			hero->statusChangeTo(HeroStatus::DIE);
			return;
		}
		else
		{
			hero->setSiNum(siNum - 1);
			this->refreshSiNumLabel();
			hero->statusChangeTo(HeroStatus::DISAPPEAR);
			scheduleOnce(schedule_selector(FactoryScene::backToRope), BACK_TIME);
		}
	}
}

void FactoryScene::backToRope(float dt){
	CCLog("back to rope");
	if (!this->targetRope){
		return;
	}
	
	float x = targetRope->getPositionX();
	float y = targetRope->getPositionY() - targetRope->getCurLength() / 2;
	this->hero->setPosition(ccp(x, y));
	this->hero->statusChangeTo(HeroStatus::APPEAR);

	scheduleOnce(schedule_selector(FactoryScene::setPa), BACK_TIME);
}

void FactoryScene::setPa(float dt){
	MaoChong* maoChong = dynamic_cast<MaoChong*>(hero);
	if (maoChong->getCurLine() % 2 == 0)
	{
		hero->statusChangeTo(HeroStatus::LEFT_PA);
	}
	else
	{
		hero->statusChangeTo(HeroStatus::RIGHT_PA);
	}
}

Rope* FactoryScene::getTargetRope(){
	return targetRope;
}

FactoryScene::~FactoryScene(){
	CCObject* o = NULL;
	CCARRAY_FOREACH(ropeArray, o){
		Rope* r = dynamic_cast<Rope*>(o);
		r->release();
	}
	CC_SAFE_DELETE(ropeArray);

	CCARRAY_FOREACH(roundArray, o){
		CCSprite* r = dynamic_cast<CCSprite*>(o);
		r->release();
	}
	CC_SAFE_DELETE(roundArray);
}