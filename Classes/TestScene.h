#ifndef __TestScene__
#define __TestScene__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

USING_NS_CC;

#define PTM_RATIO 72

class TestObject;

class TestScene : public cocos2d::Scene
{
public: static Scene* createScene();
		virtual bool init();
	//====================================================

	Layer* bgLayer;
	Layer* actLayer;

	Label* lblMemory;

	TestObject* box;

	//====================================================
	void initListener();
	void initValue();
	void initBackground();
	void debugLabel();
	void displayMemory();
	//====================================================
	void callEveryFrame(float f);
	//====================================================
	bool onTouchBegan(Touch* touch,	Event* event);
	void onTouchMoved(Touch* touch,	Event* event);
	void onTouchEnded(Touch* touch,	Event* event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//====================================================
	
	Size winSize;
	Texture2D* texture;
	b2World* _world;

	// For debugging
	GLESDebugDraw* m_debugDraw;
	cocos2d::CustomCommand _customCmd;

	bool createBox2dWorld(bool debug);
	void setBox2dWorld();
	~TestScene();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
		uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

	b2Vec2 startPoint;
	b2Vec2 endPoint;
	b2Body* myBall;
	bool bBallTouch;

	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);
	b2Body* getBodyAtTab(Point p);

	//====================================================
	CREATE_FUNC(TestScene);
};

#endif // __TestScene__
