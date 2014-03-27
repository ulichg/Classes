#include "BaseScene.h"

#define MAP_TAG 10000
#define HERO_TAG 10001
#define CONTROLLER_TAG 10002

bool BaseScene::init(){
	setMap(NULL);
	addHero(NULL);
	return true;
}

CCScene* BaseScene::scene(){
	CCScene* mScene = CCScene::create();
	BaseScene* mLayer = BaseScene::create();
	mScene->addChild(mLayer);

	return mScene;
}

void BaseScene::setMap(CCTMXTiledMap* map){
	if (!map){
		return;
	}
	if (this->getChildByTag(MAP_TAG)){
		this->removeChildByTag(MAP_TAG);
	}
	this->map = map;
	this->addChild(this->map, -1, MAP_TAG);
}

void BaseScene::addHero(Hero* hero){
	if (!hero){
		return;
	}
	if (this->getChildByTag(HERO_TAG)){
		this->removeChildByTag(HERO_TAG);
	}

	this->hero = hero;
	this->addChild(hero, 10, HERO_TAG);
}

void BaseScene::bindControllerToHero(Controller* controller)
{
	if (!controller){
		return;
	}
	if (!this->getChildByTag(CONTROLLER_TAG)){
		this->removeChildByTag(CONTROLLER_TAG);
	}

	this->controller = controller;
	this->hero->setController(controller);
	this->addChild(controller, 0, CONTROLLER_TAG);
}