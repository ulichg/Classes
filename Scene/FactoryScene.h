#pragma once
#include "cocos2d.h"
#include "BaseScene.h"
#include "Rope.h"

class FactoryScene :
	public BaseScene
{
public:
	CREATE_FUNC(FactoryScene);

	virtual bool init();
	static CCScene* scene();

	//���õ�ͼ�ϵ���Ϣ������ ��
	void setMapThings(CCTMXTiledMap* map);

	// �ѽ�ɫ������������,�ȷ��ã������Ƿ���������
	bool bindHeroToRope(Rope* rope);
	// ��ʼ��hero
	void initHero(CCTMXTiledMap* map);

	void findRope();

	/* ����˿����*/
	void doSiPa();
	/* ���ë����˿�󣬿ɷ��ص����ӣ�����NULL�������޷��ҵ����ʵġ�*/
	Rope* getSiTouchRope();
	/* �ص����� */
	void backToRope(float dt);
	Rope* getTargetRope();
	void setPa(float dt);

	/* ��ײ���֮�� */
	void update(float dt);
	/* ����������� */
	void setRoundAndRope(CCTMXTiledMap* map);
	/* ���õƹ� */
	void setLight(CCTMXTiledMap* map);
	/* ���ý�� */
	void setCoin(CCTMXTiledMap* map);
	/* ��ʾë����˺�Ч��*/
	void showDie();
	void initMap();
	void addMap(CCTMXTiledMap* map);
	~FactoryScene();

private:
	Rope* targetRope;
};

