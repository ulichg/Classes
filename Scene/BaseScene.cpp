#include "BaseScene.h"
#include "Data/GlobalVar.h"

bool BaseScene::init(){
	setMap(NULL);
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