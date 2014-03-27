#include "FactoryScene.h"

bool FactoryScene::init(){
	CCTMXTiledMap* map = CCTMXTiledMap::create("map/testMap.tmx");
	setMap(map);
	
	setMapThings();
	MaoChong* maoChong = MaoChong::createWithTiledMap(map);
	maoChong->statusChangeTo(HeroStatus::PA);
	addHero(maoChong);
	
	return true;
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

	// 设置转动的轴
	CCTMXObjectGroup* objGroup = map->objectGroupNamed("roundObjects");
	int length = objGroup->getObjects()->count();
	char str[100];
	for (int i = 0; i < length; i++)
	{
		sprintf(str, "round_%i", i);
		CCDictionary* heroStartPointDic = objGroup->objectNamed(str);
		float x = heroStartPointDic->valueForKey("x")->floatValue();
		float y = heroStartPointDic->valueForKey("y")->floatValue();
		
		CCSprite* roundSprite = CCSprite::create("map/round.png");
		CCSize size = roundSprite->getContentSize();
		//roundSprite->setPosition(ccp(x + size.width / 2, y + size.height / 2));
		roundSprite->setPosition(ccp(x, y));

		CCActionInterval* rotate = CCRotateBy::create(2, 360.0f);
		roundSprite->runAction(CCRepeatForever::create(rotate));

		map->addChild(roundSprite, 1);

		Rope* rope = new Rope();
		rope->setPosition(ccp(x, y));
		rope->rollAction();
		map->addChild(rope, 0);
	}
}


