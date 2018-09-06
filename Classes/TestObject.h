#ifndef __TestObject__
#define __TestObject__

#include "cocos2d.h"

USING_NS_CC;

class TestObject : public cocos2d::Sprite
{
public: virtual bool init();
private:
	//====================================================

	bool prsA;
	bool prsD;
	bool prsAD;
	
	bool prsW;
	bool prsS;
	bool prsWS;

	//====================================================
	void initListener();
	void initValue();
	void debugLabel();
	void callEveryFrame(float f);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
public:
	//====================================================
	
	Sprite * box;


	//====================================================
	CREATE_FUNC(TestObject);
};

#endif //__TestObject__