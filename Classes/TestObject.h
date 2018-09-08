#ifndef __TestObject__
#define __TestObject__

#include "cocos2d.h"

USING_NS_CC;

class TestObject : public cocos2d::Sprite
{
public: virtual bool init(int _type);
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
	
	static TestObject* TestObject::create(int _type)
	{
		TestObject* obj = new (std::nothrow) TestObject;
		if (obj && obj->init(_type))
		{
			obj->autorelease();
			return obj;
		}
		CC_SAFE_DELETE(obj);
		return nullptr;
	}

};

#endif //__TestObject__