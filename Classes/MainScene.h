#ifndef __MainScene__
#define __MainScene__

#include "cocos2d.h"

USING_NS_CC;

class PlayerCharacter;
class PopPause;

class MainScene : public cocos2d::Scene
{
public: static cocos2d::Scene* createScene();
		virtual bool init();

private:

	// 변수 ==============================================

	Layer* actLayer;
	Layer* bgLayer;

	//=======================================

	Label* lblMemory;
	Label* lblPosX;
	Label* lblPosY;

	//=======================================

	PlayerCharacter* Noel;
	Texture2D* bltcache;
	Texture2D* bltfirecache;
	std::vector<Sprite*> v;

	Sprite* bgSprite[2];
	Sprite* bltfire;

	//=======================================

	bool bPaused;

	//=======================================

public:

	// 함수 ==============================================

	void initListener();
	void initValue();
	void initBackground();
	void debugLabel();
	void displayMemory();

	//====================================================

	void callEveryFrame(float f);

	//====================================================

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//====================================================

	void addLabelTimer(cocos2d::Node* pParent, int nTime, const cocos2d::Vec2& pos, const cocos2d::Vec2& anc);
	void updateLabel(cocos2d::Label* pLabel);

	double getDistance(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2, int _magni);

	void moveToSecondScene(Ref* pSender);
	void moveToStartScene(Ref* pSender);

	//====================================================

	void doPop(Ref* pSender);
	void notiAction(Object* obj);
	void resumeDelay();
	void resumeAction();

	//====================================================
	
	void createBullet();
	
	//====================================================

	CREATE_FUNC(MainScene);
};

#endif // __MainScene_SCENE_H__
