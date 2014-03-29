#include "BaseScene.h"
#include "Data/GlobalVar.h"
#include "Person/MaoChong.h"

bool BaseScene::init(){
	this->ropeArray = CCArray::create();
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