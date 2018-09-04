#ifndef __TestObject__
#define __TestObject__

#include "cocos2d.h"

USING_NS_CC;

class TestObject : public cocos2d::Node
{
public: virtual bool init();
private:
	//====================================================

	Sprite* box;

	bool prsA;
	bool prsD;
	bool prsAD;

	//====================================================
	void initListener();
	void initValue();
	void debugLabel();
	void callEveryFrame(float f);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
public:
	//====================================================
	


	//====================================================
	CREATE_FUNC(TestObject);
};

#endif //__TestObject__